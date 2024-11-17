#ifndef __MOTOR_H
#define __MOTOR_H

/**
 * @brief  初始化直流电机(PWMA引脚接PA2，AIN1和AIN2接PA4和PA5)
 */
void Motor_Init(void);
/**
 * @brief  设置直流电机转速
 * @param Speed 转速(-100~100)
 */
void Motor_SetSpeed(int8_t Speed);

#endif
