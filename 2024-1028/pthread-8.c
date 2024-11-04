#include <stdio.h>
#include <pthread.h>

#define N 2000000000
#define N_THREAD 4

typedef struct {
        int id;
        double sum;
} worker_arg_t;

void worker(void *arg) {
        int id = ((worker_arg_t *)arg)->id;
        int start = id * (N / N_THREAD);
        int end = (id == N_THREAD - 1) ? N : (id + 1) * (N / N_THREAD); 
        double sum = 0.0;

        for (int i = start; i < end; i++) {
                sum += 1.0 / (i + 1);
        }

        ((worker_arg_t *)arg)->sum = sum;
}

int main(void) {
        pthread_t child[N_THREAD];
        worker_arg_t worker_arg[N_THREAD];
        double sum = 0.0;

        for (int i = 0; i < N_THREAD; i++) {
                worker_arg[i].id = i;
                pthread_create(&child[i], NULL, (void *)worker, (void *)&worker_arg[i]);
        }

        for (int i = 0; i < N_THREAD; i++) {
                pthread_join(child[i], NULL);
                sum += worker_arg[i].sum;
        }

        printf("Sum = %f\n", sum);
        return 0;
}

