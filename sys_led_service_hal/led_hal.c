/*************************************************************************
	> File Name: led_hal.c
	> Author: hanp
	> Mail: 18336073183@163.com 
	> Created Time: 2017年07月31日 星期一 15时00分30秒
 ************************************************************************/

#include<stdio.h>
#include <hardware/hardware.h>
#include <hardware/led_hal.h>

#include <cutils/log.h>
#include <utils/Log.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <math.h>
#include "led.h"

#define  LOG_TAG   "LedHal"

/* 1. 定义一个名字为HMI的hw_device_t类型的结构体 */

/* 2. 实现一个open函数，并根据传入的name返回一个自定义的设备结构体 （led_device_t） */

/* 3. 根据传入name的定义一个自定义的设备结构体 -- led_device_t, 这个结构体的第一个成员是hw_device_t结构体 */

static int fd;

static void led_open(led_device_t * dev)
{
	fd = open("/dev/led", O_RDWR);
	ALOGI("hal method led_open ...");
	if (fd < 0)
	{
		ALOGI("hal method led_open open /dev/led err ...");
		return ;	
	}

}

static int led_close(struct hw_device_t * dev)
{
	ALOGI("hal method led_close ...");
	close(fd);

	return 0;
}

static void led_ctrl(led_device_t * dev, int which, int status)
{
	ALOGI("hal method led_ctrl ...");
	switch (status)
	{
	case 1:
		ioctl(fd, LED_ON, which);
		break;
	case 0:
		ioctl(fd, LED_OFF, which);
		break;
	default:
		ALOGI("hal method led_ctrl invaled argument ...");
		break;
	}
}

static led_device_t led_device = {
	.common = {
		.tag   = HARDWARE_DEVICE_TAG,
		.close = led_close,
	},

	.led_open = led_open,
	.led_ctrl = led_ctrl,
};


static int led_device_open(const hw_module_t* module, const char* id, hw_device_t** device)
{
	*device = &led_device;      //通过参数，传回led_device_t结构体

	return 0;
}

static struct hw_module_methods_t led_module_methods = {
	.open = led_device_open,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {   //#define    HAL_MODULE_INFO_SYM   HMI
	.tag = HARDWARE_MODULE_TAG,
	.id = "led",
	.methods = &led_module_methods,
};
