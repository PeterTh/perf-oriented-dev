#include "loadutils.h"

int main(int argc, char **argv) {

  core_load_profile profile;
  int core = 3;
  if (argc > 1)
    core = atoi(argv[1]);

  set_affinity(core);
  printf("Testing on core %d...\n", core);
  get_rel_load_on_core(core, &profile);
  microsleep(1000000);
  printf("Startup: %f\n\n", get_rel_load_on_core(core, &profile));

  for (int i = 0; i <= 100; i += 5) {
    get_rel_load_on_core(core, &profile);
    double targetload = i / 100.0;
    generate_load_timed(2, targetload, &mc3_characteristic);
    printf("Tried to generate: % 8.2f load, generated % 8.2f.\n", targetload,
           get_rel_load_on_core(core, &profile));
  }

  return 0;
}
