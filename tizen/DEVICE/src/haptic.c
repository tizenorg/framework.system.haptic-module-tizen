/*
 * haptic-module-tizen
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>
#include <device-node.h>

#include <haptic-plugin-intf.h>
#include "haptic_module_log.h"
#include "file.h"

#ifndef EXTAPI
#define EXTAPI __attribute__ ((visibility("default")))
#endif

#define DEFAULT_EFFECT_HANDLE	0xFFFF
#define DEFAULT_MOTOR_COUNT		1

/* START of Static Function Section */
static int convert_feedback_level(int feedback)
{
	static int max = -1;
	int ret;

	if (max == -1) {
		ret = device_get_property(DEVICE_TYPE_VIBRATOR,
				PROP_VIBRATOR_LEVEL_MAX, &max);
		if (ret < 0)
			return ret;
	}

	return feedback * max / HAPTIC_MODULE_FEEDBACK_MAX;
}

static void *_create_handle(void)
{
	static int i = 0;
	return ((getpid()<<16)|(time(NULL)+(i++)));
}
/* END of Static Function Section */

static int _get_device_count(int *count)
{
	if (count == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*count = DEFAULT_MOTOR_COUNT;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _open_device(int device_index, int *device_handle)
{
	int status;

	if (device_index < HAPTIC_MODULE_DEVICE_0 || device_index > HAPTIC_MODULE_DEVICE_ALL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (device_handle == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*device_handle = _create_handle();
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _close_device(int device_handle)
{
	int status;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _vibrate_monotone(int device_handle, int duration, int feedback, int priority, int *effect_handle)
{
	int level, ret;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (duration < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (feedback < HAPTIC_MODULE_FEEDBACK_MIN || feedback > HAPTIC_MODULE_FEEDBACK_MAX)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (priority < HAPTIC_MODULE_PRIORITY_MIN || priority > HAPTIC_MODULE_PRIORITY_HIGH)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (effect_handle == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (feedback == HAPTIC_MODULE_FEEDBACK_MIN)
		return HAPTIC_MODULE_ERROR_NONE;

	level = convert_feedback_level(feedback);
	if (level < 0) {
		MODULE_ERROR("fail to convert haptic level : %d", ret);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	ret = device_set_property(DEVICE_TYPE_VIBRATOR,
			PROP_VIBRATOR_LEVEL, level);
	if (ret < 0) {
		MODULE_ERROR("fail to set haptic level : %d", ret);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	ret = device_set_property(DEVICE_TYPE_VIBRATOR,
			PROP_VIBRATOR_ONESHOT, duration);
	if (ret < 0) {
		MODULE_ERROR("fail to set oneshot : %d", ret);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	*effect_handle = DEFAULT_EFFECT_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _vibrate_buffer(int device_handle, const unsigned char *vibe_buffer, int iteration, int feedback, int priority, int *effect_handle)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static int _stop_device(int device_handle)
{
	int ret;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	ret = device_set_property(DEVICE_TYPE_VIBRATOR,
			PROP_VIBRATOR_ENABLE, 0);
	if (ret < 0) {
		MODULE_ERROR("fail to stop haptic device : %d", ret);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _get_device_state(int device_handle, int *state)
{
	int ret;
	int cur_state;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (state == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	ret = device_get_property(DEVICE_TYPE_VIBRATOR,
			PROP_VIBRATOR_ENABLE, &cur_state);
	if (ret < 0) {
		MODULE_ERROR("fail to get haptic enble value : %d", ret);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	*state = (cur_state == 0 ?
			HAPTIC_MODULE_STATE_STOP : HAPTIC_MODULE_STATE_PLAYING);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _create_effect(unsigned char *vibe_buffer, int max_bufsize, haptic_module_effect_element *elem_arr, int max_elemcnt)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static int _get_buffer_duration(int device_handle, const unsigned char *vibe_buffer, int *buffer_duration)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static int _convert_binary(void)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static const struct haptic_plugin_ops haptic_plugin_tizen = {
	.get_device_count		= _get_device_count,
	.open_device			= _open_device,
	.close_device			= _close_device,
	.vibrate_monotone		= _vibrate_monotone,
	.vibrate_buffer			= _vibrate_buffer,
	.stop_device			= _stop_device,
	.get_device_state		= _get_device_state,
	.create_effect			= _create_effect,
	.get_buffer_duration	= _get_buffer_duration,
	.convert_binary			= _convert_binary,
};

EXTAPI
const struct haptic_plugin_ops *get_haptic_plugin_interface(void)
{
	return &haptic_plugin_tizen;
}
