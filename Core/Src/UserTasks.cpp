/**
 * @file UserTasks.cpp
 * @author Will (phliuab@connect.ust.hk)
 * @brief File storing all user tasks
 * @version 0.1
 * @date 2020-09-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "FreeRTOS.h"
#include "main.h"
#include "task.h"
#include "MG996R.hpp"
StaticTask_t xBlinkTaskTCB;
StackType_t uxBlinkTaskStack[64];
void blinky(void *param)
{
    while (true)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        vTaskDelay(200);
    }
}

StaticTask_t xServoTaskTCB;
StackType_t uxServoTaskStack[128];
void servoTask(void *param)
{
    using namespace Drivers::MG996R;

    init();

    while(true)
    {
        for (uint8_t angle = 30; angle < 120; ++angle)
        {
            setTargetAngle(angle);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }

        for (uint8_t angle = 120; angle > 30; --angle)
        {
            setTargetAngle(angle);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
}

extern "C"
{
    void startUserTasks()
    {
        xTaskCreateStatic(
            blinky, "blink", 64, NULL, 0, uxBlinkTaskStack, &xBlinkTaskTCB);
        xTaskCreateStatic(
            servoTask, "servoTask", 128, NULL, 0, uxServoTaskStack, &xServoTaskTCB);
    }
}