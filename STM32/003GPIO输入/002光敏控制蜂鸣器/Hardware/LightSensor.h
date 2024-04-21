#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

/**
 * @brief  初始化光敏传感器 B13
 */
void LightSensor_Init(void);
/**
 * @brief  获取值
 * @retval
 * 1 光线暗
 * 0 光线亮
 */
uint8_t LightSensor_Get(void);

#endif
