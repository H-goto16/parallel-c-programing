#include <stdio.h>
#include <pthread.h>

#define N 2000000000

double sum = 0.0;
pthread_mutex_t mutex_sum;

void worker1(void) {
        for (int i = 0; i < N/2; i++) {
                pthread_mutex_lock(&mutex_sum);
                sum += 1.0 / (i + 1);
                pthread_mutex_unlock(&mutex_sum);
        }
}

void worker2(void) {
        for (int i = N/2; i < N; i++) {
                pthread_mutex_lock(&mutex_sum);
                sum += 1.0 / (i + 1);
                pthread_mutex_unlock(&mutex_sum);
        }
}

int main(void) {
        pthread_t child1, child2;

        pthread_mutex_init(&mutex_sum, NULL);

        pthread_create(&child1, NULL, (void *)worker1, NULL);
        pthread_create(&child2, NULL, (void *)worker2, NULL);

        pthread_join(child1, NULL);
        pthread_join(child2, NULL);

        pthread_mutex_destroy(&mutex_sum);

        printf("sum = %f\n", sum);
        return 0;
}
