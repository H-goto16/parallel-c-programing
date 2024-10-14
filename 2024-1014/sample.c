#include <stdio.h>

#define N 2000000000

int main(void) {
        double sum = 0.0;
        for (int i = 1; i <= N; i++) {
                sum += 1.0 / i;
        }

        printf("Sum = %f\n", sum );

        return 0;
}
