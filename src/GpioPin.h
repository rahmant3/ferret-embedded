#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

struct GpioPin {
    const struct device * port;
    gpio_pin_t pin;
    bool active_low;
};

typedef struct gpio_callback GpioInterruptSettings;
typedef gpio_callback_handler_t GpioInterruptCallback;

void GpioPin_setup_as_input(const struct GpioPin * pin);
void GpioPin_setup_interrupt(const struct GpioPin * pin, bool rising_edge, GpioInterruptSettings * settings, GpioInterruptCallback callback);

void GpioPin_setup_as_output(const struct GpioPin * pin);
void GpioPin_set_output_state(const struct GpioPin * pin, bool enabled);

#endif // GPIO_PIN_H