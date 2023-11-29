#ifndef MIST_CONTROLLER_H
#define MIST_CONTROLLER_H

#include "GpioPin.h"

struct MistController {
    struct GpioPin power_enable;
    uint32_t duty_cycle;

    volatile uint32_t last_ticks;
};

void MistController_init(struct MistController * mist);

void MistController_increase_speed(struct MistController * mist);
void MistController_decrease_speed(struct MistController * mist);

void MistController_iterate(struct MistController * mist, uint32_t now_ticks);

#endif // MIST_CONTROLLER_H