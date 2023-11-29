#include <string.h> // For memset

#include "MistController.h"

#define MIST_CONTROL_PERIOD_ms      (2000u)
#define MIST_SPEED_INCREMENTS       (50u)

void MistController_init(struct MistController * mist)
{
    mist->duty_cycle = 0;
    mist->last_ticks = 0;
    GpioPin_set_output_state(&mist->power_enable, false);
}

void MistController_increase_speed(struct MistController * mist)
{
    if ((mist->duty_cycle + MIST_SPEED_INCREMENTS) <= 100)
    {
        mist->duty_cycle += MIST_SPEED_INCREMENTS;
    }
}

void MistController_decrease_speed(struct MistController * mist)
{
    if (mist->duty_cycle >= MIST_SPEED_INCREMENTS)
    {
        mist->duty_cycle -= MIST_SPEED_INCREMENTS;
    }
}

void MistController_iterate(struct MistController * mist, uint32_t now_ticks)
{
    if (mist->duty_cycle == 0)
    {
        GpioPin_set_output_state(&mist->power_enable, false);
    }
    else if (mist->duty_cycle == 100)
    {
        GpioPin_set_output_state(&mist->power_enable, true);
    }
    else
    {
        uint32_t elapsed_ticks_ms = now_ticks - mist->last_ticks;
        if (elapsed_ticks_ms >= MIST_CONTROL_PERIOD_ms)
        {
            // Time to reset the timer
            mist->last_ticks = now_ticks;
            GpioPin_set_output_state(&mist->power_enable, true);
        }
        else if (elapsed_ticks_ms >= (MIST_CONTROL_PERIOD_ms * mist->duty_cycle / 100))
        {
            // In the off period
            GpioPin_set_output_state(&mist->power_enable, false);
        }
        else 
        {
            // In the on period
            GpioPin_set_output_state(&mist->power_enable, true);
        }
    }
}