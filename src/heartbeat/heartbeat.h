/**
 * @file heartbeat.h
 * @author Gonzalo Nahuel Vaca (vacagonzalo@gmail.com)
 * @brief Heartbeat interface file
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SRC_HEARTBEAT_HEARTBEAT_H
#define SRC_HEARTBEAT_HEARTBEAT_H

/**
 * @brief Heartbeat thread
 *
 * It will toggle the on-board LED every 1 second
 */
void heartbeat(void);

#endif /* SRC_HEARTBEAT_HEARTBEAT_H */
