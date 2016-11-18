#include "signal.h"
#include "sys/syscall.h"

sighandler_t signal(int signum, sighandler_t handler) {
    __syscall(sc_signal, (size_t)signum, (size_t)handler, 0, 0, 0);
}