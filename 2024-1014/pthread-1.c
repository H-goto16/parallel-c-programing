#include <stdio.h>
#include <pthread.h>

#define N 2000000000

double sum = 0.0;

void worker(void) {
        for (int i = 0; i < N; i++) {
                sum += 1.0 / (i + 1);
        }
}

int main(void) {
        pthread_t child;
        pthread_create(&child, NULL, (void *)worker, NULL);
        pthread_join(child, NULL);

        printf("Sum = %f\n", sum);
        return 0;
}
