/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>

#include "RotaryEncoder.h"
#include "PwmOutput.h"

static struct RotaryEncoder encoder_1;
static GpioInterruptSettings encoder_1_interrupt_settings;

static struct RotaryEncoder encoder_2;
static GpioInterruptSettings encoder_2_interrupt_settings;

static struct PwmOutput fan_output;

static void encoder_1_interrupt(
	const struct device *port,
	struct gpio_callback *cb,
	gpio_port_pins_t pins)
{
	if ((pins & BIT(10)) != 0)
	{
		RotaryEncoder_inputA_falling_event(&encoder_1);
	}
}

static void encoder_2_interrupt(
	const struct device *port,
	struct gpio_callback *cb,
	gpio_port_pins_t pins)
{
	if ((pins & BIT(12)) != 0)
	{
		RotaryEncoder_inputA_falling_event(&encoder_2);
	}
}

int main(void)
{
	printk("Rotary Encoder Test\n");
	encoder_1.inputA.port = device_get_binding("gpio@842800"); //gpio1
	encoder_1.inputA.pin = 10;

	encoder_1.inputB.port = device_get_binding("gpio@842800"); //gpio1
	encoder_1.inputB.pin = 11;

	GpioPin_setup_as_input(&encoder_1.inputA);
	GpioPin_setup_as_input(&encoder_1.inputB);
	GpioPin_setup_interrupt(&encoder_1.inputA, false, &encoder_1_interrupt_settings, encoder_1_interrupt);
	
	
	encoder_2.inputA.port = device_get_binding("gpio@842800"); //gpio1
	encoder_2.inputA.pin = 12;

	encoder_2.inputB.port = device_get_binding("gpio@842800"); //gpio1
	encoder_2.inputB.pin = 13;

	GpioPin_setup_as_input(&encoder_2.inputA);
	GpioPin_setup_as_input(&encoder_2.inputB);
	GpioPin_setup_interrupt(&encoder_2.inputA, false, &encoder_2_interrupt_settings, encoder_2_interrupt);

    // Configure PWM output on PWM0, Channel 0 (by default P1.06)
	fan_output.timer = device_get_binding("pwm@21000");
	fan_output.channel = 0;
	fan_output.polarity = PWM_POLARITY_NORMAL;

	PwmOutput_set_freq_and_duty_cycle(&fan_output, 25000, 100);
	
	while (1) {

		k_sleep(K_SECONDS(4U));
	}
	
	#if 0
	const struct device * dev = device_get_binding("gpio@842800");
	if (dev == NULL)
	{
		printk("Could not get device.");
	}

	// configure the LED pin as output
	gpio_pin_configure(dev, 10, GPIO_OUTPUT);
	gpio_pin_set(dev, 10, 1);
	while (1) {

		k_sleep(K_SECONDS(4U));
	}
	#endif
	return 0;
}

#if 0
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)

int main(void)
{
	uint32_t max_period;
	uint32_t period;
	uint8_t dir = 0U;
	int ret;

	printk("PWM-based blinky\n");

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return 0;
	}

	/*
	 * In case the default MAX_PERIOD value cannot be set for
	 * some PWM hardware, decrease its value until it can.
	 *
	 * Keep its value at least MIN_PERIOD * 4 to make sure
	 * the sample changes frequency at least once.
	 */
	printk("Calibrating for channel %d...\n", pwm_led0.channel);
	max_period = MAX_PERIOD;
	while (pwm_set_dt(&pwm_led0, max_period, max_period / 2U)) {
		max_period /= 2U;
		if (max_period < (4U * MIN_PERIOD)) {
			printk("Error: PWM device "
			       "does not support a period at least %lu\n",
			       4U * MIN_PERIOD);
			return 0;
		}
	}

	printk("Done calibrating; maximum/minimum periods %u/%lu nsec\n",
	       max_period, MIN_PERIOD);

	period = max_period;
	while (1) {
		ret = pwm_set_dt(&pwm_led0, period, period / 2U);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return 0;
		}

		period = dir ? (period * 2U) : (period / 2U);
		if (period > max_period) {
			period = max_period / 2U;
			dir = 0U;
		} else if (period < MIN_PERIOD) {
			period = MIN_PERIOD * 2U;
			dir = 1U;
		}

		k_sleep(K_SECONDS(4U));
	}
	return 0;
}

#endif
