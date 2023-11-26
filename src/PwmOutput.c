#include "PwmOutput.h"
#include "Utilities.h"

void PwmOutput_set_freq_and_duty_cycle(const struct PwmOutput * output, uint32_t freq_Hz, uint32_t dutycycle_x10)
{
    uint32_t period_ns = 1000000000 / freq_Hz;
    uint32_t ontime_ns = period_ns * dutycycle_x10 / 1000;

    int err = pwm_set(output->timer, output->channel, period_ns, ontime_ns, output->polarity);
    ERROR_OCCURRED(err);
}