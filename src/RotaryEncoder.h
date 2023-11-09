#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "GpioPin.h"

struct RotaryEncoder
{
    struct GpioPin inputA;
    struct GpioPin inputB;

    uint32_t count;
};

void RotaryEncoder_init(struct RotaryEncoder * encoder);
void RotaryEncoder_get_count(struct RotaryEncoder * encoder);
void RotaryEncoder_inputA_falling_event(struct RotaryEncoder * encoder);

#endif 