#include "RotaryEncoder.h"

#include "Utilities.h"

void RotaryEncoder_init(struct RotaryEncoder * encoder)
{
    encoder->count = 0;
}

void RotaryEncoder_inputA_falling_event(struct RotaryEncoder * encoder)
{
    int state = gpio_pin_get(encoder->inputB.port, encoder->inputB.pin);
    if (state == 1)
    {
        encoder->count++;
    }
    else if (state == 0)
    {
        encoder->count--;
    }
    else
    {
        // Error occurred
    }
    
}


enum EncoderState RotaryEncoder_poll_state(struct RotaryEncoder * encoder)
{
    // TODO: Some debouncing required to clean the signal.
    enum EncoderState result = EncoderState_NoChange;
    
    uint32_t last_count = encoder->last_count;
    uint32_t current_count = encoder->count;
    
    uint32_t diff = current_count - last_count;

    if (diff == 0)
    {
        // No action.
    }
    else if (diff > (UINT32_MAX / 2))
    {
        // Assume negative direction
        result = EncoderState_Decreased;

        encoder->last_count = encoder->count;
    }
    else
    {
        // Assume positive direction
        result = EncoderState_Increased;

        encoder->last_count = encoder->count;
    }

    return result;
}