#include <stdio.h>
#include <pthread.h>

#define N 2000000000

double sum1 = 0.0;
double sum2 = 0.0;

void worker1(void) {
        for (int i = 0; i < N / 2; i++) {
                sum1 += 1.0 / (i + 1);
        } 
}

void worker2(void) {
        for (int i = N / 2; i < N; i++) {
                sum2 += 1.0 / (i + 1);
        }
}

int main(void) {
        double sum = 0.0;
        pthread_t child1, child2;
        pthread_create(&child1, NULL, (void *)worker1, NULL);
        pthread_create(&child2, NULL, (void *)worker2, NULL);
        pthread_join(child1, NULL);
        pthread_join(child2, NULL);

        sum = sum1 + sum2;
        printf("Sum = %f\n", sum);
        return 0;
}
