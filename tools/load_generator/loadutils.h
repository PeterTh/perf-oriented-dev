#pragma once

#define _GNU_SOURCE 1
#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef unsigned long long ull;

typedef struct _load_characteristic {
  unsigned samples;
  const ull *loopreps;
  const ull *sleeptimes;
} load_characteristic;

static const ull mc3_characteristic_loopreps[] = {0,      15000,  25000, 35000,
                                                  50000,  72000,  98000, 160000,
                                                  187000, 200000, 800000};
static const ull mc3_characteristic_sleeptimes[] = {
    100000, 16000, 14000, 12500, 12000, 11000, 9000, 5900, 3000, 600, 0};
static const load_characteristic mc3_characteristic = {
    11, mc3_characteristic_loopreps, mc3_characteristic_sleeptimes};

typedef struct core_load_profile_ {
  unsigned long total_user, total_user_low, total_system, total_idle;
} core_load_profile;

ull get_num_cpus(void);

void set_affinity(int core);

ull time_ms(void);

void skipline(FILE *file);

void microsleep(ull period);

double get_rel_load_on_core(unsigned core, core_load_profile *profile);

void loadgen(ull repetitions, ull inner_repetitions, ull sleepyhead);

void loadgen_timed(unsigned seconds, ull inner_repetitions, ull sleepyhead);

void generate_load_timed(unsigned seconds, double amount,
                         const load_characteristic *lc);
