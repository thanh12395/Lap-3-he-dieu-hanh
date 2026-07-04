#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX 100

int a[MAX];
int n = 0;

sem_t mutex; // semaphore nhị phân dùng như mutex

void* producer(void* arg) {
    while (1) {
        int value = rand() % 1000;

        sem_wait(&mutex);
        if (n < MAX) {
            a[n] = value;
            n++;
            printf("[Producer] Thêm %d, số phần tử: %d\n", value, n);
        }
        sem_post(&mutex);

        usleep(80000);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&mutex);
        if (n > 0) {
            int idx = rand() % n;
            int value = a[idx];
            a[idx] = a[n - 1];
            n--;
            printf("[Consumer] Lấy %d, số phần tử: %d\n", value, n);
        } else {
            printf("Nothing in array a\n");
        }
        sem_post(&mutex);

        usleep(100000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&mutex, 0, 1);

    pthread_t tProd, tCons;
    pthread_create(&tProd, NULL, producer, NULL);
    pthread_create(&tCons, NULL, consumer, NULL);

    pthread_join(tProd, NULL);
    pthread_join(tCons, NULL);

    sem_destroy(&mutex);
    return 0;
}
