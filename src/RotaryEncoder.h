#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "GpioPin.h"

struct RotaryEncoder
{
    struct GpioPin inputA;
    struct GpioPin inputB;

    volatile uint32_t count;
    uint32_t last_count;
};

enum EncoderState
{
    EncoderState_NoChange,
    EncoderState_Increased,
    EncoderState_Decreased
};

void RotaryEncoder_init(struct RotaryEncoder * encoder);
void RotaryEncoder_get_count(struct RotaryEncoder * encoder);
void RotaryEncoder_inputA_falling_event(struct RotaryEncoder * encoder);

enum EncoderState RotaryEncoder_poll_state(struct RotaryEncoder * encoder);


#endif 