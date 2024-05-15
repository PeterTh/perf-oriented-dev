#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>

typedef struct {
	int64_t repeats;
	int64_t iterations;
	int64_t lower, upper;
} thread_args;

void* benchmark_thread(void *args) {
	thread_args *t_args = (thread_args*)args;
	for(int64_t r = 0; r < t_args->repeats; ++r) {
		unsigned seed = 0;
		void **allocations = (void**)calloc(t_args->iterations, sizeof(void*));
		for(int64_t i = 0; i < t_args->iterations; ++i) {
			int64_t to_alloc = rand_r(&seed) % (t_args->upper - t_args->lower) + t_args->lower;
			allocations[i] = malloc(to_alloc);
		}
		for(int64_t i = 0; i < t_args->iterations; ++i) {
			free(allocations[i]);
		}
		free(allocations);
	}
	return NULL;
}

int main(int argc, char** argv) {
	int64_t num_threads = 100;
	if(argc != 6) {
		printf("USAGE: ./malloctest [num_threads] [num_repeats] [num_iterations] [lower] [upper]\n");
		return -1;
	}
	num_threads = atol(argv[1]);
	thread_args t_args;
	t_args.repeats = atol(argv[2]);
	t_args.iterations = atol(argv[3]);
	t_args.lower = atol(argv[4]);
	t_args.upper = atol(argv[5]);

	pthread_t* threads = (pthread_t*)calloc(num_threads, sizeof(pthread_t));
	
	for(int64_t i = 0; i < num_threads; ++i) {
		pthread_create(&threads[i], NULL, benchmark_thread, &t_args);
	}

	for(int64_t i = 0; i < num_threads; ++i) {
		pthread_join(threads[i], NULL);
	}

	free(threads);
}
