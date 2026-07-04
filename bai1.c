#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 34 // 2 số cuối MSSV (24) + 10

int sells = 0;
int products = 0;

sem_t sem_full;   // = products - sells
sem_t sem_empty;  // = N - (products - sells)

void* processA(void* arg) {          // Bán hàng
    while (1) {
        sem_wait(&sem_full);
        sells++;
        printf("[A] sells = %d, products = %d\n", sells, products);
        sem_post(&sem_empty);
        usleep(100000);
    }
    return NULL;
}

void* processB(void* arg) {          // Làm hàng
    while (1) {
        sem_wait(&sem_empty);
        products++;
        printf("[B] sells = %d, products = %d\n", sells, products);
        sem_post(&sem_full);
        usleep(70000);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB;
    sem_init(&sem_full, 0, 0);
    sem_init(&sem_empty, 0, N);

    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    sem_destroy(&sem_full);
    sem_destroy(&sem_empty);
    return 0;
}
