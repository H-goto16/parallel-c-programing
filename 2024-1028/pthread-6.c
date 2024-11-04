#include <stdio.h>
#include <pthread.h>

#define N 2000000000

#define N_THREAD 4

double sum = 0.0;
pthread_mutex_t mutex_sum;

void worker(void *arg) {
        int id = *(int *)arg;
        int start = id * (N / N_THREAD);
        int end = (id + 1) * (N / N_THREAD);
        double sum_local = 0.0;

        for (int i = start; i < end; i++) {
                sum_local += 1.0 / (i + 1);
        }

        pthread_mutex_lock(&mutex_sum);
        sum += sum_local;
        pthread_mutex_unlock(&mutex_sum);
}

int main(void) {
        pthread_t child[N_THREAD];
        int id[N_THREAD];

        if (N % N_THREAD != 0) {
                printf("データ数がスレッド数で割り切れません\n");
                return 1;
        }

        pthread_mutex_init(&mutex_sum, NULL);

        for (int i = 0; i < N_THREAD; i++) {
                id[i] = i;
                pthread_create(&child[i], NULL, (void *)worker, (void *)&id[i]);
        }
        for (int i = 0; i < N_THREAD; i++) {
                pthread_join(child[i], NULL);
        }

        pthread_mutex_destroy(&mutex_sum);

        printf("Sum = %f\n", sum);
        return 0;
}
