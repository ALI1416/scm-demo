#ifndef __SERVO_H
#define __SERVO_H

/**
 * @brief  初始化舵机(PWM引脚接PA1)
 */
void Servo_Init(void);
/**
 * @brief  设置舵机角度
 * @param Angle 角度(0~180)
 */
void Servo_SetAngle(uint8_t Angle);

#endif
