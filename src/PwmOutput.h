#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

struct PwmOutput {
    const struct device * timer;
    uint32_t channel;
    pwm_flags_t polarity;
};

void PwmOutput_set_freq_and_duty_cycle(const struct PwmOutput * output, uint32_t freq_Hz, uint32_t dutycycle_x10);

#endif // PWM_OUTPUT_H