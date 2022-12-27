/**
 * @file motors.h
 * @author Gonzalo Nahuel Vaca (vacagonzalo@gmail.com)
 * @brief H-bridge controller interface
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SRC_MOTORS_MOTORS_H
#define SRC_MOTORS_MOTORS_H

/**
 * @brief The posible combinations for 2 motors
 *
 */
typedef enum MotorsDirection
{
    MotorsDirection_STOP,
    MotorsDirection_FORWARD,
    MotorsDirection_BACKWARD,
    MotorsDirection_CLOCKWISE,
    MotorsDirection_COUNTERCLOCKWISE
} MotorsDirection_t;

/**
 * @brief It start and verify the peripherals for H-bridge control
 *
 * @return int 0 if success
 */
int MotorsInit(void);

/**
 * @brief It will change the vehicle's direction
 *
 * @param[in] direction desired direction for the vehicle
 */
void MotorsSetDirection(MotorsDirection_t direction);

#endif /* SRC_MOTORS_MOTORS_H */
