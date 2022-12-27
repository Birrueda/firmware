/**
 * @file motors.c
 * @author Gonzalo Nahuel Vaca (vacagonzalo@gmail.com)
 * @brief H-bridge controller implementation
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "motors.h"
#include <zephyr/drivers/gpio.h>

#define IN1_NODE DT_ALIAS(hbridgein1)
#define IN2_NODE DT_ALIAS(hbridgein2)
#define IN3_NODE DT_ALIAS(hbridgein3)
#define IN4_NODE DT_ALIAS(hbridgein4)

static const struct gpio_dt_spec in1_led = GPIO_DT_SPEC_GET(IN1_NODE, gpios);
static const struct gpio_dt_spec in2_led = GPIO_DT_SPEC_GET(IN2_NODE, gpios);
static const struct gpio_dt_spec in3_led = GPIO_DT_SPEC_GET(IN3_NODE, gpios);
static const struct gpio_dt_spec in4_led = GPIO_DT_SPEC_GET(IN4_NODE, gpios);

static inline void motorsDirectionStop(void)
{
    gpio_pin_set_dt(&in1_led, 0);
    gpio_pin_set_dt(&in2_led, 0);
    gpio_pin_set_dt(&in3_led, 0);
    gpio_pin_set_dt(&in4_led, 0);
}

static inline void motorsDirectionForward(void)
{
    gpio_pin_set_dt(&in1_led, 1);
    gpio_pin_set_dt(&in2_led, 0);
    gpio_pin_set_dt(&in3_led, 1);
    gpio_pin_set_dt(&in4_led, 0);
}

static inline void motorsDirectionBackward(void)
{
    gpio_pin_set_dt(&in1_led, 0);
    gpio_pin_set_dt(&in2_led, 1);
    gpio_pin_set_dt(&in3_led, 0);
    gpio_pin_set_dt(&in4_led, 1);
}

static inline void motorsDirectionClockwise(void)
{
    gpio_pin_set_dt(&in1_led, 1);
    gpio_pin_set_dt(&in2_led, 0);
    gpio_pin_set_dt(&in3_led, 0);
    gpio_pin_set_dt(&in4_led, 1);
}

static inline void motorsDirectionCounterclockwise(void)
{
    gpio_pin_set_dt(&in1_led, 0);
    gpio_pin_set_dt(&in2_led, 1);
    gpio_pin_set_dt(&in3_led, 1);
    gpio_pin_set_dt(&in4_led, 0);
}

int MotorsInit(void)
{
    int ret;
    /* clang-format off */
    bool ready = device_is_ready(in1_led.port)
              && device_is_ready(in2_led.port)
              && device_is_ready(in3_led.port)
              && device_is_ready(in4_led.port);
    /* clang-format on */
    if (!ready)
    {
        return -1;
    }

    ret = gpio_pin_configure_dt(&in1_led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&in2_led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&in3_led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0)
    {
        return -1;
    }
    ret = gpio_pin_configure_dt(&in4_led, GPIO_OUTPUT_INACTIVE);
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
