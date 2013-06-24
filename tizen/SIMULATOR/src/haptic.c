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

#include <haptic-plugin-intf.h>
#include "haptic_module_log.h"

#ifndef EXTAPI
#define EXTAPI __attribute__ ((visibility("default")))
#endif

#define DEFAULT_MOTOR_COUNT			1
#define DEFAULT_DEVICE_HANDLE		0x01
#define DEFAULT_EFFECT_HANDLE		0x02

static int _get_device_count(int *count)
{
	if (count == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*count = DEFAULT_MOTOR_COUNT;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _open_device(int device_index, int *device_handle)
{
	if (device_index < HAPTIC_MODULE_DEVICE_0 || device_index > HAPTIC_MODULE_DEVICE_ALL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	if (device_handle == NULL)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	*device_handle = DEFAULT_DEVICE_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _close_device(int device_handle)
{
	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _vibrate_monotone(int device_handle, int duration, int feedback, int priority, int *effect_handle)
{
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

	MODULE_LOG("call %s function", __func__);

	*effect_handle = DEFAULT_EFFECT_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _vibrate_file(int device_handle, const char *file_path, int iteration, int feedback, int priority, int  *effect_handle)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (file_path == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (iteration < HAPTIC_MODULE_ITERATION_ONCE || iteration > HAPTIC_MODULE_ITERATION_INFINITE)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (feedback < HAPTIC_MODULE_FEEDBACK_MIN || feedback > HAPTIC_MODULE_FEEDBACK_MAX)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (priority < HAPTIC_MODULE_PRIORITY_MIN || priority > HAPTIC_MODULE_PRIORITY_HIGH)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (feedback == HAPTIC_MODULE_FEEDBACK_MIN)
        return HAPTIC_MODULE_ERROR_NONE;

	MODULE_LOG("call %s function", __func__);

	*effect_handle = DEFAULT_EFFECT_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _vibrate_buffer(int device_handle, const unsigned char *vibe_buffer, int iteration, int feedback, int priority, int *effect_handle)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (vibe_buffer == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (iteration < HAPTIC_MODULE_ITERATION_ONCE || iteration > HAPTIC_MODULE_ITERATION_INFINITE)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (feedback < HAPTIC_MODULE_FEEDBACK_MIN || feedback > HAPTIC_MODULE_FEEDBACK_MAX)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (priority < HAPTIC_MODULE_PRIORITY_MIN || priority > HAPTIC_MODULE_PRIORITY_HIGH)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (feedback == HAPTIC_MODULE_FEEDBACK_MIN)
        return HAPTIC_MODULE_ERROR_NONE;

	MODULE_LOG("call %s function", __func__);

	*effect_handle = DEFAULT_EFFECT_HANDLE;
	return HAPTIC_MODULE_ERROR_NONE;
}

static int _stop_effect(int device_handle, int effect_handle)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _stop_all_effects(int device_handle)
{
	if (device_handle < 0)
		return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _pause_effect(int device_handle, int effect_handle)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _resume_effect(int device_handle, int effect_handle)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _get_effect_state(int device_handle, int effect_handle, int *effect_state)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (effect_state == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _create_effect(const unsigned char *vibe_buffer, int max_bufsize, haptic_module_effect_element *elem_arr, int max_elemcnt)
{
    if (vibe_buffer == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (max_bufsize < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (elem_arr == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (max_elemcnt < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _save_effect(const unsigned char *vibe_buffer, int max_bufsize, const char *file_path)
{
    if (vibe_buffer == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (max_bufsize < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (file_path == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _get_file_duration(int device_handle, const char *file_path, int *file_duration)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (file_path == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (file_duration == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _get_buffer_duration(int device_handle, const unsigned char *vibe_buffer, int *buffer_duration)
{
    if (device_handle < 0)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (vibe_buffer == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

    if (buffer_duration == NULL)
        return HAPTIC_MODULE_INVALID_ARGUMENT;

	MODULE_LOG("call %s function", __func__);

	return HAPTIC_MODULE_ERROR_NONE;
}

static int _convert_binary (void)
{
	MODULE_ERROR("This device is not supported this function(%s)", __func__);
	return HAPTIC_MODULE_NOT_SUPPORTED;
}

static struct haptic_ops haptic_plugin = {
	.get_device_count		= _get_device_count,
	.open_device            = _open_device,
	.close_device           = _close_device,
	.vibrate_monotone       = _vibrate_monotone,
	.vibrate_file           = _vibrate_file,
	.vibrate_buffer         = _vibrate_buffer,
	.stop_effect            = _stop_effect,
	.stop_all_effects       = _stop_all_effects,
	.pause_effect           = _pause_effect,
	.resume_effect          = _resume_effect,
	.get_effect_state       = _get_effect_state,
	.create_effect          = _create_effect,
	.save_effect            = _save_effect,
	.get_file_duration      = _get_file_duration,
	.get_buffer_duration    = _get_buffer_duration,
	.convert_binary         = _convert_binary,
};

EXTAPI
const struct haptic_ops *get_haptic_plugin_interface()
{
	return &haptic_plugin;
}
