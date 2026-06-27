#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *task(void *arg) {
    printf("Thread con dang chay...\n");
    sleep(1);
    printf("Thread con ket thuc.\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    int detachstate;

    pthread_attr_init(&attr);

    // Doi thuoc tinh thanh DETACHED
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Kiem tra lai gia tri vua dat
    pthread_attr_getdetachstate(&attr, &detachstate);
    printf("Detach state hien tai: %s\n",
        detachstate == PTHREAD_CREATE_DETACHED ? "DETACHED" : "JOINABLE");

    pthread_create(&tid, &attr, task, NULL);

    // Vi thread la DETACHED nen pthread_join se bao loi (EINVAL)
    int ret = pthread_join(tid, NULL);
    if (ret != 0) {
        printf("pthread_join loi (code %d) vi thread la DETACHED, khong the join!\n", ret);
    }

    sleep(2); // cho thread con chay xong roi moi thoat main
    pthread_attr_destroy(&attr);
    return 0;
}
