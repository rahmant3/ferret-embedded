#include "GpioPin.h"
#include "Utilities.h"

void GpioPin_setup_as_input(const struct GpioPin * pin)
{
	int err = gpio_pin_configure(pin->port, pin->pin, GPIO_INPUT);
    ERROR_OCCURRED(err);
}


void GpioPin_setup_interrupt(
    const struct GpioPin * pin, 
    bool rising_edge, 
    GpioInterruptSettings * settings, 
    GpioInterruptCallback callback
)
{   
    int err = gpio_pin_interrupt_configure(pin->port, pin->pin, GPIO_INT_EDGE_TO_INACTIVE);
    ERROR_OCCURRED(err);

    gpio_init_callback(settings, callback, BIT(pin->pin));
    
    err = gpio_add_callback(pin->port, settings);
    ERROR_OCCURRED(err);
}


void GpioPin_setup_as_output(const struct GpioPin * pin)
{
	int err = gpio_pin_configure(pin->port, pin->pin, GPIO_OUTPUT);
    ERROR_OCCURRED(err);
}

void GpioPin_set_output_state(const struct GpioPin * pin, bool enabled)
{
    if (pin->active_low)
    {
        enabled = !enabled;
    }
    
	int err = gpio_pin_set(pin->port, pin->pin, (enabled) ? 1 : 0);
    ERROR_OCCURRED(err);
}
