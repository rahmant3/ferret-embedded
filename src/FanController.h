#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include "GpioPin.h"
#include "PwmOutput.h"

struct FanController {
    struct PwmOutput output;
    struct GpioPin power_enable;
    
    uint32_t duty_cycle;
};

void FanController_init(struct FanController * fan);

void FanController_increase_speed(struct FanController * fan);
void FanController_decrease_speed(struct FanController * fan);

void FanController_set_speed(struct FanController * fan);
uint32_t FanController_get_speed(struct FanController * fan);

#endif // FAN_CONTROLLER_H