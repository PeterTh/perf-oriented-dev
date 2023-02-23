#pragma once

#define _GNU_SOURCE 1
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

typedef unsigned long long ull;

typedef struct _load_characteristic {
	unsigned samples;
	ull *loopreps;
	ull *sleeptimes;
} load_characteristic;

ull mc3_characteristic_loopreps[] = 
	{      0, 15000, 25000, 35000, 50000, 72000,  98000, 160000, 187000, 200000, 800000};
ull mc3_characteristic_sleeptimes[] = 
	{ 100000, 16000, 14000, 12500, 12000, 11000,   9000,   5900,   3000,    600,      0};
const load_characteristic mc3_characteristic = 
	{ 11, mc3_characteristic_loopreps, mc3_characteristic_sleeptimes };


void set_affinity(int core) {
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	if(!pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) == 0) {
		printf("Error setting thread affinity.\n");
		exit(-1);
	}
}

ull time_ms() {
	struct timeval tv;
	ull time;
	gettimeofday(&tv, 0);
	time = tv.tv_sec * 1000 + tv.tv_usec/1000;
	return time;
}

void skipline(FILE *file) {
	static char tmp[1024*32];
	char *skipped;
	skipped = fgets(tmp, sizeof(tmp), file); // skip rest of line
	skipped += 1; // suppress "unused" warning	
}

typedef struct core_load_profile_ {
	unsigned long total_user, total_user_low, total_system, total_idle;
} core_load_profile;

double get_rel_load_on_core(unsigned core, core_load_profile* profile) {
	ull user = 0, user_low = 0, system = 0, idle = 0;
	double ret = 0.0;
	
	ull total_user, total_user_low, total_system, total_idle;
	FILE* file = fopen("/proc/stat", "r");
	// skip lines
	for(unsigned i=0; i<=core; ++i) skipline(file);
	// read relevant line
	char scanBuffer[255];
	sprintf(scanBuffer, "cpu%u %%llu %%llu %%llu %%llu", core);
	if(fscanf(file, scanBuffer, &total_user, &total_user_low, &total_system, &total_idle) != 4) {
		printf("Error parsing /proc/stat.\n");
		exit(-1);
	}
	fclose(file);
	
	// overflow "handling"
	if(total_user < profile->total_user || profile->total_user == 0) user = total_user;
	else user = total_user - profile->total_user;
	if(total_user_low < profile->total_user_low || profile->total_user_low == 0) user_low = total_user_low;
	else user_low = total_user_low - profile->total_user_low;
	if(total_system < profile->total_system || profile->total_system == 0) system = total_system;
	else system = total_system - profile->total_system;
	if(total_idle < profile->total_idle || profile->total_idle == 0) idle = total_idle;
	else idle = total_idle - profile->total_idle;

	// calculate return value
	double cur_nonidle = user + user_low + system;
	double cur_idle = idle;
	if(cur_idle <= 0.0) ret = 1.0;
	else ret = cur_nonidle / (cur_nonidle + cur_idle);

	// update profile data
	profile->total_user = total_user;
	profile->total_user_low = total_user_low;
	profile->total_system = total_system;
	profile->total_idle = total_idle;

	return ret;
}

ull get_num_cpus() {
	ull ret = 1;
#ifdef _SC_NPROCESSORS_ONLN
	// Linux
	ret = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
	// Irix
	ret = sysconf(_SC_NPROC_ONLN);
#elif defined(MPC_GETNUMSPUS)
	// HPUX
	ret = mpctl(MPC_GETNUMSPUS, NULL, NULL);
#endif
	if(ret<1) ret = 1;
	return ret;
}

void microsleep(ull period) {
	struct timespec wait, remaining;
	wait.tv_sec = period/1000000;
	wait.tv_nsec = (period%1000000)*1000;
	while(nanosleep(&wait, &remaining) != 0) {
		wait = remaining;
	}
}

volatile long long __importantInt, __importantA = 12, __importantB = 98;
volatile double __importantDouble, __importantAf = 4.56, __importantBf = 0.78;
#pragma omp threadprivate(__importantInt, __importantA, __importantB, __importantDouble, __importantAf, __importantBf)

void loadgen(ull repetitions, ull inner_repetitions, ull sleepyhead) {
	for(ull i = 0; i<repetitions; ++i) {
		for(ull j = 0; j<inner_repetitions; ++j) {
			__importantDouble += __importantAf * __importantBf;
			__importantDouble -= __importantBf;
			if(__importantInt<0) printf("loadgen insanity int\n");
			__importantInt += __importantA;
			__importantInt = (__importantInt%__importantB) * __importantA / __importantB;
			__importantDouble = cos(tan(sin(__importantBf)));
			__importantDouble += __importantAf + __importantInt;
			if(__importantDouble<0) printf("loadgen insanity double\n");
		}
		if(sleepyhead > 0) microsleep(sleepyhead);
	}
}

void loadgen_timed(unsigned seconds, ull inner_repetitions, ull sleepyhead) {
	ull ragnarok;
	ragnarok = time_ms() + seconds * 1000;
	while(time_ms() < ragnarok) {
		loadgen(1, inner_repetitions, sleepyhead);
	}
}


void generate_load_timed(unsigned seconds, double amount, const load_characteristic* lc) {
	double sampling_point = (lc->samples-1)*amount;
	int int_sample1 = (int)sampling_point;
	int int_sample2 = (int)sampling_point+1;
	if(int_sample2 >= (int)lc->samples) int_sample2 = lc->samples-1;
	double dec_part = sampling_point - int_sample1;
	double weight1 = 1.0-dec_part, weight2 = dec_part;
	ull loopreps = weight1*lc->loopreps[int_sample1] + weight2*lc->loopreps[int_sample2];
	ull sleeptime = weight1*lc->sleeptimes[int_sample1] + weight2*lc->sleeptimes[int_sample2];
	loadgen_timed(seconds, loopreps, sleeptime);
}
