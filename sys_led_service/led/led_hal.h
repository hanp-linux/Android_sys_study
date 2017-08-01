/*************************************************************************
	> File Name: led_hal.h
	> Author: hanp
	> Mail: 18336073183@163.com 
	> Created Time: 2017年07月31日 星期一 15时34分18秒
 ************************************************************************/

#ifndef _HARDWARE_LED_HAL_H
#define _HARDWARE_LED_HAL_H

#include <hardware/hardware.h>

__BEGIN_DECLS


struct led_device_t {
	struct hw_device_t common;

	void (* led_open)(struct led_device_t * dev);
	void (* led_ctrl)(struct led_device_t * dev, int which, int status);
};


__END_DECLS

#endif  // _HARDWARE_LED_HAL_H

