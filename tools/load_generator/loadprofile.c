#include "loadutils.h"

void full_coverage(int core, unsigned measurement_time) {
  set_affinity(core);
  core_load_profile profile;

  ull sleepphase_start = 0;
  ull sleepphase_step = 500;
  ull sleepphase_max = 25000;
  ull loopreps_start = 5000;
  ull loopreps_step = 5000;
  ull loopreps_max = 200000;

  printf("loopreps\\sleep: ");
  for (ull sleepphase = sleepphase_start; sleepphase <= sleepphase_max;
       sleepphase += sleepphase_step) {
    printf("% 10lld", sleepphase);
  }
  printf("\n");

  for (ull loopreps = loopreps_start; loopreps <= loopreps_max;
       loopreps += loopreps_step) {
    printf("% 16lld", loopreps);
    for (ull sleepphase = sleepphase_start; sleepphase <= sleepphase_max;
         sleepphase += sleepphase_step) {
      get_rel_load_on_core(core, &profile);
      loadgen_timed(measurement_time, loopreps, sleepphase);
      double load = get_rel_load_on_core(core, &profile);
      printf("% 10.4f", load);
      fflush(stdout);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {

  core_load_profile profile;
  int core = 3;
  if (argc > 1)
    core = atoi(argv[1]);

  set_affinity(core);
  printf("Calibrating on core %d...\n", core);
  get_rel_load_on_core(core, &profile);
  microsleep(1000000);
  printf("Startup: %f\n\n", get_rel_load_on_core(core, &profile));

  full_coverage(core, 3);

  return 0;
}
