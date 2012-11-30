/*
 *  haptic-module-tizen
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

#ifndef __HAPTIC_MODULE_LOG_H__
#define __HAPTIC_MODULE_LOG_H__

#define FEATURE_HAPTIC_MODULE_DLOG

#ifdef FEATURE_HAPTIC_MODULE_DLOG
    #define LOG_TAG "HAPTIC_MODULE"
    #include <dlog.h>
    #define MODULE_LOG(fmt, args...)       SLOGD(fmt, ##args)
    #define MODULE_ERROR(fmt, args...)     SLOGE(fmt, ##args)
#else
    #define MODULE_LOG(x, ...)
    #define MODULE_ERROR(x, ...)
#endif

#endif //__HAPTIC_MODULE_LOG_H__
