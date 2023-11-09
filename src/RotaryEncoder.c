#include "RotaryEncoder.h"

#include "Utilities.h"

static void RotaryEncoder_pin_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

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