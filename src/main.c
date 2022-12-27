#include <zephyr/kernel.h>
#include "heartbeat/heartbeat.h"
#include "motors/motors.h"

#define STACK_BLOCK_SIZE 1024
#define STACK_BLOCKS(b) (STACK_BLOCK_SIZE * b)

#define NO_POINTER NULL
#define LOW_PRIORITY (K_LOWEST_THREAD_PRIO - 1)
#define NO_OPTIONS 0
#define NO_DELAY 0

void MotorsTest(void)
{
    MotorsInit();
    while (1)
    {
        MotorsSetDirection(MotorsDirection_STOP);
        MotorsSetDuty(MotorSide_ALL, 0);
        k_msleep(1000);
        MotorsSetDirection(MotorsDirection_FORWARD);
        MotorsSetDuty(MotorSide_ALL, 31);
        k_msleep(1000);
        MotorsSetDirection(MotorsDirection_BACKWARD);
        MotorsSetDuty(MotorSide_ALL, 63);
        k_msleep(1000);
        MotorsSetDirection(MotorsDirection_CLOCKWISE);
        MotorsSetDuty(MotorSide_ALL, 127);
        k_msleep(1000);
        MotorsSetDirection(MotorsDirection_COUNTERCLOCKWISE);
        MotorsSetDuty(MotorSide_ALL, 255);
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(heartbeat_thread,
                STACK_BLOCKS(1),
                heartbeat,
                NO_POINTER,
                NO_POINTER,
                NO_POINTER,
                LOW_PRIORITY,
                NO_OPTIONS,
                NO_DELAY);

K_THREAD_DEFINE(motors_thread,
                STACK_BLOCKS(1),
                MotorsTest,
                NO_POINTER,
                NO_POINTER,
                NO_POINTER,
                LOW_PRIORITY,
                NO_OPTIONS,
                NO_DELAY);
