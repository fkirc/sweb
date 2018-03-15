#include "nonstd.h"
#include "sys/syscall.h"
#include "../../../common/include/kernel/syscall-definitions.h"
#include "stdlib.h"
#include "pthread.h"

int createprocess(const char* path, int sleep)
{
  return __syscall(sc_createprocess, (long) path, sleep, 0x00, 0x00, 0x00);
}

extern int main();

void pthread_create_wrapper(void *(*start_routine)(void*), void *arg) {

  // TODO: Pass address of this wrapper function in pthread_create

  void* ret_value = start_routine(arg);
  pthread_exit(ret_value);
}

void _start()
{
  exit(main());
}
