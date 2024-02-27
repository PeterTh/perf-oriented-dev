#include "loadutils.h"

#define MAXCORES 4096
#define MAXLINE 1024 * 16

typedef struct system_load_profile_ {
  core_load_profile cores[MAXCORES];
} system_load_profile;

void capture_system_load(system_load_profile *external_profile) {
  system_load_profile current_profile;

  printf("time:% 16lld ms / load: ", time_ms());

  FILE *file = fopen("/proc/stat", "r");
  // skip first line
  skipline(file);
  // read relevant lines
  char scanBuffer[255];
  ull num_cores = get_num_cpus();
  for (ull core = 0; core < num_cores; ++core) {
    sprintf(scanBuffer, "cpu%llu %%llu %%llu %%llu %%llu", core);
    if (fscanf(file, scanBuffer, &current_profile.cores[core].total_user,
               &current_profile.cores[core].total_user_low,
               &current_profile.cores[core].total_system,
               &current_profile.cores[core].total_idle) != 4) {
      printf("Error parsing /proc/stat.\n");
      exit(-1);
    }
    skipline(file); // skip rest of line

    // overflow "handling"
    ull user = 0, user_low = 0, system = 0, idle = 0;

    if (current_profile.cores[core].total_user <
            external_profile->cores[core].total_user ||
        external_profile->cores[core].total_user == 0)
      user = current_profile.cores[core].total_user;
    else
      user = current_profile.cores[core].total_user -
             external_profile->cores[core].total_user;

    if (current_profile.cores[core].total_user_low <
            external_profile->cores[core].total_user_low ||
        external_profile->cores[core].total_user_low == 0)
      user_low = current_profile.cores[core].total_user_low;
    else
      user_low = current_profile.cores[core].total_user_low -
                 external_profile->cores[core].total_user_low;

    if (current_profile.cores[core].total_system <
            external_profile->cores[core].total_system ||
        external_profile->cores[core].total_system == 0)
      system = current_profile.cores[core].total_system;
    else
      system = current_profile.cores[core].total_system -
               external_profile->cores[core].total_system;

    if (current_profile.cores[core].total_idle <
            external_profile->cores[core].total_idle ||
        external_profile->cores[core].total_idle == 0)
      idle = current_profile.cores[core].total_idle;
    else
      idle = current_profile.cores[core].total_idle -
             external_profile->cores[core].total_idle;

    // calculate load
    double load;
    double cur_nonidle = user + user_low + system;
    double cur_idle = idle;
    if (cur_idle <= 0.0)
      load = 1.0;
    else
      load = cur_nonidle / (cur_nonidle + cur_idle);
    printf("% 8.4f", load);

    // update profile data
    external_profile->cores[core] = current_profile.cores[core];
  }
  fclose(file);

  printf("\n");
  fflush(stdout);
}

#include <signal.h>

static bool run = true;
void handler(int param) {
  (void)(param);
  run = false;
}

int main(int argc, char **argv) {
  signal(SIGINT, handler);
  signal(SIGTERM, handler);

  int core = 3;
  if (argc > 1)
    core = atoi(argv[1]);
  set_affinity(core);

  system_load_profile profile;
  while (run) {
    ull t = time_ms();
    capture_system_load(&profile);
    // sleep remaining time to 1 second
    ull tn = time_ms();
    if ((t + 1000) > tn)
      microsleep((t + 1000 - tn) * 1000);
  }

  return 0;
}
