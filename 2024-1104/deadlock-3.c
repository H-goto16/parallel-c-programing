#include <pthread.h>
#include <stdio.h>

struct {
  int balance;
  pthread_mutex_t mutex;
} account_A, account_B;

void send_1000_A_to_B(void) {
  while (1) {
    if (account_A.balance >= 1000) {
      account_A.balance -= 1000;
      account_B.balance += 1000;
      printf("JPY 1000 send from A to B. (A:%d B:%d)\n", account_A.balance,
             account_B.balance);
    }
  }
}

void send_1000_B_to_A(void) {
  while (1) {
    if (account_B.balance >= 1000) {
      account_B.balance -= 1000;
      account_A.balance += 1000;
      printf("JPY 1000 send from B to A. (A:%d B:%d)\n", account_A.balance,
             account_B.balance);
    }
  }
}

int main(void) {
  pthread_t pth_A_to_B, pth_B_to_A;

  pthread_mutex_init(&account_A.mutex, NULL);
  pthread_mutex_init(&account_B.mutex, NULL);

  account_A.balance = 10000;
  account_B.balance = 5000;

  pthread_create(&pth_A_to_B, NULL, (void *)send_1000_A_to_B, NULL);
  pthread_create(&pth_B_to_A, NULL, (void *)send_1000_B_to_A, NULL);

  pthread_join(pth_A_to_B, NULL);
  pthread_join(pth_B_to_A, NULL);

  pthread_mutex_destroy(&account_A.mutex);
  pthread_mutex_destroy(&account_B.mutex);

  return 0;
}
