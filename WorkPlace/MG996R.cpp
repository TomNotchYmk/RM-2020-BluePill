#include "MG996R.hpp"
#include "tim.h"

#if USE_MG996R
namespace Drivers
{
namespace MG996R
{
void init()
{
    // Write you code here
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
void setTargetAngle(uint8_t input)
{
    // Write you code here
    //input threshold
    float angle = input < 0 ? 0.0f : input > 180 ? 180.0f : (float)input;

    //calculate the percentage of angle/180 degree
    float percentage = angle/180.0f;

    //tranlate it into pulse
    uint32_t pulse = 100 + (uint32_t)(100.0f * percentage);

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
}

// other helper functions you need

}  // namespace MG996R
}  // namespace Drivers
#endif