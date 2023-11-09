#ifndef UTILITIES_H
#define UTILITIES_H


#include <zephyr/sys/printk.h>

#define ERROR_OCCURRED(err) if(err != 0) { printk("RotaryEncoder error occurred"); while(1); }

#endif // UTILITIES_H