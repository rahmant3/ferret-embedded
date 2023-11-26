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
#include "FanController.h"

static struct RotaryEncoder encoder_1;
static GpioInterruptSettings encoder_1_interrupt_settings;

static struct RotaryEncoder encoder_2;
static GpioInterruptSettings encoder_2_interrupt_settings;

static struct FanController fan;

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
	fan.output.timer = device_get_binding("pwm@21000");
	fan.output.channel = 0;
	fan.output.polarity = PWM_POLARITY_NORMAL;

	fan.power_enable.port = device_get_binding("gpio@842800"); //gpio1
	fan.power_enable.pin = 5;
	fan.power_enable.active_low = false; //true;

	GpioPin_setup_as_output(&fan.power_enable);

	FanController_init(&fan);
	
	while (1) 
	{
		enum EncoderState encoder_1_state = RotaryEncoder_poll_state(&encoder_1);
		if (encoder_1_state == EncoderState_Increased)
		{
			FanController_increase_speed(&fan);
		}
		else if (encoder_1_state == EncoderState_Decreased)
		{
			FanController_decrease_speed(&fan);
		}
		else
		{
			// No change.
		}

		k_sleep(K_MSEC(500));
	}
}