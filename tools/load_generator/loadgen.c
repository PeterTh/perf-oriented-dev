#include "loadutils.h"

#include <omp.h>
#include <signal.h>
#include <string.h>

typedef struct _load_profile {
  ull cores;
  ull length;
  double **values;
} load_profile;

void load_load_profile(const char *filename, load_profile *prof) {
  FILE *in = fopen(filename, "r");

  // check if file successfully opened
  if (in == NULL) {
    printf("Error opening file: %s\n", filename);
    exit(-1);
  }

  // read sizes
  int ret = fscanf(in, "cores: %llu", &prof->cores);
  (void)(ret); // suppress warning in release builds
  assert(ret == 1 && "Error reading load profile.");
  skipline(in);
  ret = fscanf(in, "length: %llu", &prof->length);
  assert(ret == 1 && "Error reading load profile.");
  skipline(in);

  // allocate memory for values
  prof->values = (double **)calloc(sizeof(double *), prof->cores);
  for (ull core = 0; core < prof->cores; ++core) {
    prof->values[core] = (double *)calloc(sizeof(double), prof->length);
  }

  // read in values
  for (ull line = 0; line < prof->length; ++line) {
    ret = fscanf(in, "time: %*u ms / load:");
    assert(ret == 0 && "Error reading load profile.");
    for (ull core = 0; core < prof->cores; ++core) {
      ret = fscanf(in, " %lf", &prof->values[core][line]);
      assert(ret == 1 && "Error reading load profile.");
    }
    skipline(in);
  }

  fclose(in);
}

void delete_load_profile(load_profile *prof) {
  for (ull core = 0; core < prof->cores; ++core) {
    free(prof->values[core]);
  }
  free(prof->values);
}

static bool run = true;
void handler(int param) {
  (void)(param);
  run = false;
}

int main(int argc, char **argv) {
  signal(SIGINT, handler);
  signal(SIGTERM, handler);

  if (argc != 3) {
    printf("Usage: loadgen [machine] [profile]\n");
    exit(-1);
  }

  load_characteristic characteristic;
  if (strcmp(argv[1], "mc3") == 0)
    characteristic = mc3_characteristic;
  else {
    printf("Unknown machine: %s\n", argv[1]);
    exit(-2);
  }

  load_profile profile;
  load_load_profile(argv[2], &profile);

#pragma omp parallel
  {
    ull core = omp_get_thread_num();
    set_affinity(core);

    ull core_index = core % profile.cores;
    ull pos_index = 0;
    while (run) {
      // #pragma omp barrier
      generate_load_timed(1, profile.values[core_index][pos_index],
                          &characteristic);
      pos_index++;
      if (pos_index >= profile.length)
        pos_index = 0;
    }
  }

  delete_load_profile(&profile);
  exit(0);
}
