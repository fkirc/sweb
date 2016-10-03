#include "pthread.h"
#include "assert.h"
#include "stdio.h"

int main() {

    int tid = pthread_self();
    assert(tid > 0);
    assert(tid == pthread_self());

    printf("pthread_self returned tid %d\n", tid);

    return 0;
}

