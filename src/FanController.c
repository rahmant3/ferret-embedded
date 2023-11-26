#include "FanController.h"

#define FAN_PWM_FREQ_HZ (25000)
#define FAN_SPEED_INCREMENTS (20)

void FanController_init(struct FanController * fan)
{
    fan->duty_cycle = 0;
    GpioPin_set_output_state(&fan->power_enable, false);
    PwmOutput_set_freq_and_duty_cycle(&fan->output, FAN_PWM_FREQ_HZ, 0);
}

void FanController_increase_speed(struct FanController * fan)
{
    if ((fan->duty_cycle + FAN_SPEED_INCREMENTS) <= 100)
    {
        GpioPin_set_output_state(&fan->power_enable, true);

        fan->duty_cycle += FAN_SPEED_INCREMENTS;
        PwmOutput_set_freq_and_duty_cycle(&fan->output, FAN_PWM_FREQ_HZ, (fan->duty_cycle * 10));
    }
}

void FanController_decrease_speed(struct FanController * fan)
{
    if (fan->duty_cycle >= FAN_SPEED_INCREMENTS)
    {
        fan->duty_cycle -= FAN_SPEED_INCREMENTS;
        PwmOutput_set_freq_and_duty_cycle(&fan->output, FAN_PWM_FREQ_HZ, (fan->duty_cycle * 10));

        if (fan->duty_cycle == 0)
        {
            GpioPin_set_output_state(&fan->power_enable, false);
        }
    }
}

uint32_t FanController_get_speed(struct FanController * fan)
{
    return fan->duty_cycle;
}