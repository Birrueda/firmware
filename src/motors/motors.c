#include "motors.h"
#include <zephyr/drivers/gpio.h>

#define IN1_NODE DT_ALIAS(hbridgein1)
#define IN2_NODE DT_ALIAS(hbridgein2)
#define IN3_NODE DT_ALIAS(hbridgein3)
#define IN4_NODE DT_ALIAS(hbridgein4)

typedef struct Motor
{
    const struct gpio_dt_spec inA;
    const struct gpio_dt_spec inB;
} Motor_t;

static Motor_t portMotor = {
    .inA = GPIO_DT_SPEC_GET(IN1_NODE, gpios),
    .inB = GPIO_DT_SPEC_GET(IN2_NODE, gpios)};

static Motor_t starboardMotor = {
    .inA = GPIO_DT_SPEC_GET(IN3_NODE, gpios),
    .inB = GPIO_DT_SPEC_GET(IN4_NODE, gpios)};

static inline void motorsDirectionStop(void)
{
    gpio_pin_set_dt(&portMotor.inA, 0);
    gpio_pin_set_dt(&portMotor.inB, 0);
    gpio_pin_set_dt(&starboardMotor.inA, 0);
    gpio_pin_set_dt(&starboardMotor.inB, 0);
}

static inline void motorsDirectionForward(void)
{
    gpio_pin_set_dt(&portMotor.inA, 1);
    gpio_pin_set_dt(&portMotor.inB, 0);
    gpio_pin_set_dt(&starboardMotor.inA, 1);
    gpio_pin_set_dt(&starboardMotor.inB, 0);
}

static inline void motorsDirectionBackward(void)
{
    gpio_pin_set_dt(&portMotor.inA, 0);
    gpio_pin_set_dt(&portMotor.inB, 1);
    gpio_pin_set_dt(&starboardMotor.inA, 0);
    gpio_pin_set_dt(&starboardMotor.inB, 1);
}

static inline void motorsDirectionClockwise(void)
{
    gpio_pin_set_dt(&portMotor.inA, 1);
    gpio_pin_set_dt(&portMotor.inB, 0);
    gpio_pin_set_dt(&starboardMotor.inA, 0);
    gpio_pin_set_dt(&starboardMotor.inB, 1);
}

static inline void motorsDirectionCounterclockwise(void)
{
    gpio_pin_set_dt(&portMotor.inA, 0);
    gpio_pin_set_dt(&portMotor.inB, 1);
    gpio_pin_set_dt(&starboardMotor.inA, 1);
    gpio_pin_set_dt(&starboardMotor.inB, 0);
}

int MotorsInit(void)
{
    /* clang-format off */
    bool notReady = device_is_ready(portMotor.inA.port)
                 && device_is_ready(portMotor.inB.port)
                 && device_is_ready(starboardMotor.inA.port)
                 && device_is_ready(starboardMotor.inB.port);
    /* clang-format on */
    if (notReady)
    {
        return -1;
    }
    int ret;
    ret = gpio_pin_configure_dt(&portMotor.inA, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&portMotor.inB, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&starboardMotor.inA, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&starboardMotor.inB, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    return 0;
}

void MotorsSetDirection(MotorsDirection_t direction)
{
    switch (direction)
    {
    case MotorsDirection_STOP:
        motorsDirectionStop();
        break;
    case MotorsDirection_FORWARD:
        motorsDirectionForward();
        break;
    case MotorsDirection_BACKWARD:
        motorsDirectionBackward();
        break;
    case MotorsDirection_CLOCKWISE:
        motorsDirectionClockwise();
        break;
    case MotorsDirection_COUNTERCLOCKWISE:
        motorsDirectionCounterclockwise();
        break;
    default:
        motorsDirectionStop();
        break;
    }
}
