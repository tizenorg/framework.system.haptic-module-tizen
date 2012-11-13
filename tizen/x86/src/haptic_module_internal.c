/*
 * haptic-module-tizen
 *
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jae-young Hwnag <j-zero.hwang@samsung.com>
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * SAMSUNG ELECTRONICS ("Confidential Information"). You agree and acknowledge
 * that this software is owned by Samsung and you shall not disclose
 * such Confidential Information and shall use it only in accordance with the
 * terms of the license agreement you entered into with SAMSUNG ELECTRONICS.
 * SAMSUNG make no representations or warranties about the suitability
 * of the software, either express or implied, including but not limited
 * to the implied warranties of merchantability, fitness for a particular
 * purpose,
 * by licensee arising out of or releated to this software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <devman.h>

#include <haptic_plugin_intf.h>
#include "haptic_module_log.h"

#ifndef EXTAPI
#define EXTAPI __attribute__ ((visibility("default")))
#endif

#define DEFAULT_MOTOR_COUNT			1
#define DEFAULT_DEVICE_HANDLE		0x01
#define DEFAULT_EFFECT_HANDLE		0x02

int haptic_internal_get_device_count(int *count)
{
	if (count == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*count = DEFAULT_MOTOR_COUNT;
	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_open_device(int device_index, int *device_handle)
{
	if (device_index < HAPTIC_MODULE_DEVICE_0 || device_index > HAPTIC_MODULE_DEVICE_ALL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (device_handle == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*device_handle = DEFAULT_DEVICE_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_close_device(int device_handle)
{
	int status = -1;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	status = device_set_property(DEVTYPE_HAPTIC, HAPTIC_PROP_ENABLE, 0);
	if (status < 0) {
		MODULE_ERROR("device_set_property is failed : %d", status);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_vibrate_monotone(int device_handle, int duration, int feedback, int priority, int *effect_handle)
{
	int status = -1;

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

	status = device_set_property(DEVTYPE_HAPTIC, HAPTIC_PROP_LEVEL, feedback);
	if (status < 0) {
		MODULE_ERROR("device_set_property fail : %d", status);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	status = device_set_property(DEVTYPE_HAPTIC, HAPTIC_PROP_ONESHOT, duration);
	if (status < 0) {
		MODULE_ERROR("device_set_property fail : %d", status);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	*effect_handle = DEFAULT_EFFECT_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_vibrate_file(int device_handle, const char *file_path, int iteration, int feedback, int priority, int  *effect_handle)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_vibrate_buffer(int device_handle, const unsigned char *vibe_buffer, int iteration, int feedback, int priority, int *effect_handle)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_stop_effect(int device_handle, int effect_handle)
{
	int status = -1;

    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (effect_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	status = device_set_property(DEVTYPE_HAPTIC, HAPTIC_PROP_ENABLE, 0);
	if (status < 0) {
		MODULE_ERROR("device_set_property fail : %d", status);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_stop_all_effects(int device_handle)
{
	int status = -1;

	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	status = device_set_property(DEVTYPE_HAPTIC, HAPTIC_PROP_ENABLE, 0);
	if (status < 0) {
		MODULE_ERROR("device_set_property fail : %d", status);
		return HAPTIC_MODULE_OPERATION_FAILED;
	}

	return HAPTIC_MODULE_ERROR_NONE;
}

int haptic_internal_pause_effect(int device_handle, int effect_handle)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_resume_effect(int device_handle, int effect_handle)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_get_effect_state(int device_handle, int effect_handle, int *state)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_create_effect(const unsigned char *vibe_buffer, int max_bufsize, haptic_module_effect_element *elem_arr, int max_element)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_save_effect(const unsigned char *vibe_buffer, int max_bufsize, const char *file_path)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_get_file_duration(int device_handle, const char *file_path, int *file_duration)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_get_buffer_duration(int device_handle, const unsigned char *vibe_buffer, int *buffer_duration)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

int haptic_internal_convert_binary (void)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static haptic_plugin_interface haptic_plugin_tizen;

EXTAPI
const haptic_plugin_interface *get_haptic_plugin_interface()
{
	haptic_plugin_tizen.haptic_internal_get_device_count    = &haptic_internal_get_device_count;
	haptic_plugin_tizen.haptic_internal_open_device         = &haptic_internal_open_device;
	haptic_plugin_tizen.haptic_internal_close_device        = &haptic_internal_close_device;
	haptic_plugin_tizen.haptic_internal_vibrate_monotone    = &haptic_internal_vibrate_monotone;
	haptic_plugin_tizen.haptic_internal_vibrate_file        = &haptic_internal_vibrate_file;
	haptic_plugin_tizen.haptic_internal_vibrate_buffer      = &haptic_internal_vibrate_buffer;
	haptic_plugin_tizen.haptic_internal_stop_effect         = &haptic_internal_stop_effect;
	haptic_plugin_tizen.haptic_internal_stop_all_effects    = &haptic_internal_stop_all_effects;
	haptic_plugin_tizen.haptic_internal_pause_effect        = &haptic_internal_pause_effect;
	haptic_plugin_tizen.haptic_internal_resume_effect       = &haptic_internal_resume_effect;
	haptic_plugin_tizen.haptic_internal_get_effect_state    = &haptic_internal_get_effect_state;
	haptic_plugin_tizen.haptic_internal_create_effect       = &haptic_internal_create_effect;
	haptic_plugin_tizen.haptic_internal_save_effect         = &haptic_internal_save_effect;
	haptic_plugin_tizen.haptic_internal_get_file_duration   = &haptic_internal_get_file_duration;
	haptic_plugin_tizen.haptic_internal_get_buffer_duration = &haptic_internal_get_buffer_duration;
	haptic_plugin_tizen.haptic_internal_convert_binary      = &haptic_internal_convert_binary;

	return &haptic_plugin_tizen;
}
