/**
 * @file heartbeat.c
 * @author Gonzalo Nahuel Vaca (vacagonzalo@google.com)
 * @brief Heartbeat implementation file
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "heartbeat.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000
#define LED0_NODE DT_ALIAS(heartbeatled)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void heartbeat(void)
{
    int ret;

    if (!device_is_ready(led.port))
    {
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return;
    }

    while (1)
    {
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0)
        {
            return;
        }
        k_msleep(SLEEP_TIME_MS);
    }
}
