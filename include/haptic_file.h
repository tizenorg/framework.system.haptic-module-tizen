/*
 *  haptic-module-tizen
 *
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jae-young Hwang <j-zero.hwang@samsung.com>
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

#ifndef __HAPTIC_FILE_H__
#define __HAPTIC_FILE_H__

#define GCC_PACK	__attribute__((packed))

/* little-endian form */
#define mmioHeaderID(ch0,ch1,ch2,ch3)	\
	((unsigned int)(unsigned char)(ch0) | ((unsigned int)(unsigned char)(ch1) << 8) |	\
	((unsigned int)(unsigned char)(ch2) << 16) | ((unsigned int)(unsigned char)(ch3) << 24))

#define HEADER_ID		mmioHeaderID('T','H','F','M')		// 0x4D464854
#define FMT_ID   		mmioHeaderID('f','m','t',' ')		// 0x20746D66
#define DATA_ID  		mmioHeaderID('d','a','t','a')		// 0x61746164

typedef unsigned int ID;	/* a four character code */

typedef struct _FormatChunk {
	ID chunkID;						/* chunk ID */
	int chunkSize;					/* chunk Size */
	unsigned short wChannels;		/* number of channels (Mono = 1, Stereo = 2, etc.) */
	unsigned short wBlockAlign;		/* block size of data (wChannels*1byte) */
	unsigned int dwMagnitude;		/* max magnitude */
	unsigned int dwDuration;		/* duration */
} GCC_PACK FormatChunk;

typedef struct _DataChunk {
	ID chunkID;
	int chunkSize;
	unsigned char pData[];
} GCC_PACK DataChunk;

typedef struct _HapticFile {
	ID chunkID;			/* chunk ID */
	int chunkSize;		/* chunk Size */
	FormatChunk fmt;	/* Format chunk */
	DataChunk data;		/* Data chunk */
} GCC_PACK HapticFile;

typedef struct _HapticElement {
	int stime;
	int duration;
} HapticElement;

int GetHapticLevelMax(int *max);
int SetHapticEnable(int value);
int SetHapticLevel(int value);
int SetHapticOneshot(int value);

int InitializeHapticBuffer(unsigned char *vibe_buffer, int max_bufsize);
int InsertHapticElement(unsigned char *vibe_buffer, int max_bufsize, HapticElement *element);
int GetHapticBufferSize(const unsigned char *vibe_buffer, int *size);
int GetHapticBufferDuration(const unsigned char *vibe_buffer, int *duration);
int PlayHapticBuffer(const unsigned char *vibe_buffer, int iteration, int *effect_handle);
int OpenHapticDevice(void);
int CloseHapticDevice(void);

#endif // __HAPTIC_FIEL_H__
