#include "assert.h"
#include "pthread.h"

void* thread_run() {
    return 0;
}

int main() {

    int tid = pthread_self();
    assert(tid > 0);
    assert(tid == pthread_self());
    printf("pthread_self returned tid %d\n", tid);

    pthread_exit(0);
    assert(0);
    return 0;
}
