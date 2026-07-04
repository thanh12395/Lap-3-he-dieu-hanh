#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX 100

int a[MAX];
int n = 0;

void* producer(void* arg) {
    while (1) {
        int value = rand() % 1000;
        if (n < MAX) {
            a[n] = value;
            n++;
            printf("[Producer] Thêm %d, số phần tử: %d\n", value, n);
        }
        usleep(1000); // chạy nhanh để dễ thấy đụng độ
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        if (n > 0) {
            int idx = rand() % n;
            int value = a[idx];
            a[idx] = a[n - 1];
            n--;
            printf("[Consumer] Lấy %d, số phần tử: %d\n", value, n);
        } else {
            printf("Nothing in array a\n");
        }
        usleep(1000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tProd, tCons;
    pthread_create(&tProd, NULL, producer, NULL);
    pthread_create(&tCons, NULL, consumer, NULL);
    pthread_join(tProd, NULL);
    pthread_join(tCons, NULL);
    return 0;
}
