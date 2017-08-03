/*************************************************************************
  > File Name: com_android_server_LedService.cpp
  > Author: hanp
  > Mail: 18336073183@163.com 
  > Created Time: 2017年07月26日 星期三 16时53分51秒
 ************************************************************************/

#include<iostream>
#include "jni.h"
#include "JNIHelp.h"
#include <utils/Log.h>
#include <stdio.h>
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <hardware/led_hal.h>
#include <hardware/hardware.h>

#define    LOG_TAG    "LedService"

namespace android
{

static led_device_t * led_dev;

JNIEXPORT void JNICALL ledOpen(JNIEnv * env, jclass cls)
{
	jint err;
	hw_device_t * device;
	hw_module_t * module;
	

	ALOGI("JNI native method led_open ...");

	/* 1. get modules hw_get_module */
	/* 2. call module->methods->open method get a hw_device_t structure */
	/* 3. call led_open */
	err = hw_get_module("led", (hw_module_t const**)&module);
	if (err == 0) {
		err = module->methods->open(module, NULL, &device);
		if (err == 0) {
			led_dev = (led_device_t*)device;
			led_dev->led_open(led_dev);
		}
		else {
			ALOGI("JNI native get module err ...");
		}
	}

	return;
}

JNIEXPORT void JNICALL ledClose(JNIEnv * env, jclass cls)
{
	ALOGI("JNI native method led_close ...");
}


/* status 0 -- off   1 -- on */
JNIEXPORT void JNICALL ledCtrl(JNIEnv * env, jclass cls, jint which, jint status)
{
	ALOGI("JNI native method led_ctrl ...");

	led_dev->led_ctrl(led_dev, which, status);

	return;
}

const JNINativeMethod methods[] = {
	{"native_ledOpen",  "()V", (void *)ledOpen},
	{"native_ledClose", "()V", (void *)ledClose},
	{"native_ledCtrl",  "(II)V", (void *)ledCtrl},
};

int register_android_server_LedService(JNIEnv *env)
{
	ALOGI("JNI native method register_android_server_LedService ...");
	/* 将本地method注册到LEDService这个服务中*/
	return jniRegisterNativeMethods(env, "com/android/server/LedService", methods, NELEM(methods));
}

};
