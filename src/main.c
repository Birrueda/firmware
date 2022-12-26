#include <zephyr/kernel.h>
#include "heartbeat/heartbeat.h"

#define STACK_BLOCK_SIZE 1024
#define STACK_BLOCKS(b) (STACK_BLOCK_SIZE * b)

#define NO_POINTER NULL
#define LOW_PRIORITY (K_LOWEST_THREAD_PRIO - 1)
#define NO_OPTIONS 0
#define NO_DELAY 0

K_THREAD_DEFINE(heartbeat_thread,
                STACK_BLOCKS(1),
                heartbeat,
                NO_POINTER,
                NO_POINTER,
                NO_POINTER,
                LOW_PRIORITY,
                NO_OPTIONS,
                NO_DELAY);
