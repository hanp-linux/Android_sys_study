/*************************************************************************
  > File Name: com_android_server_LedService.cpp
  > Author: hanp
  > Mail: 18336073183@163.com 
  > Created Time: 2017年07月26日 星期三 16时53分51秒
 ************************************************************************/

#include<iostream>
#include "jni.h"
#include <utils/Log.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <hardware_legacy/vibrator.h>
#include "led.h"

#include "JNIHelp.h"


namespace android
{

int fd;

JNIEXPORT void JNICALL led_open(JNIEnv * env, jclass cls)
{
	printf("jni native method led_open!!!!!!!!!\n");
	ALOGI("JNIDemo", "native method led_open ...");

	fd = open("/dev/led", O_RDWR);
	if (fd < 0)
	{
		printf("open /dev/led err\n");
		ALOGI("JNIDemo", "native method led_open open /dev/led err ...");
	}

	return;
}

JNIEXPORT void JNICALL led_close(JNIEnv * env, jclass cls)
{
	printf("jni native method led_close!!!!!!!!!\n");
	ALOGI("JNIDemo", "native method led_close ...");

	close(fd);

	return;
}


/* status 0 -- off   1 -- on */
JNIEXPORT void JNICALL led_ctrl(JNIEnv * env, jclass cls, jint which, jint status)
{
	printf("jin native method led ctrl!!!!!!!!\n");
	ALOGI("native method led_ctrl ...");

	switch (status)
	{
	case 1:
		ioctl(fd, LED_ON, which);
		break;
	case 0:
		ioctl(fd, LED_OFF, which);
		break;
	default:
		ALOGI("native method led_ctrl invaled argument ...");
		break;
	}

	return;
}

const JNINativeMethod methods[] = {
	{"native_ledOpen",  "()V", (void *)led_open},
	{"native_ledClose", "()V", (void *)led_close},
	{"native_ledCtrl",  "(II)V", (void *)led_ctrl},
};

int register_android_server_LedService(JNIEnv *env)
{
	/* 将本地method注册到LEDService这个服务中*/
	return jniRegisterNativeMethods(env, "com/android/server/LedService", methods, NELEM(methods));
}

};
