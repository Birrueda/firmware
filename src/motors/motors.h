#ifndef SRC_MOTORS_MOTORS_H
#define SRC_MOTORS_MOTORS_H

typedef enum MotorsDirection
{
    MotorsDirection_STOP,
    MotorsDirection_FORWARD,
    MotorsDirection_BACKWARD,
    MotorsDirection_CLOCKWISE,
    MotorsDirection_COUNTERCLOCKWISE
} MotorsDirection_t;

int MotorsInit(void);
void MotorsSetDirection(MotorsDirection_t direction);

#endif /* SRC_MOTORS_MOTORS_H */
