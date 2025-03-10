/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Android Accessory Mode utility functions, for the configuration of an attached
 *  Android device into Android Accessory Mode ready for general communication.
 */
 
#include "AndroidAccessoryCommands.h" 

uint8_t Android_GetAccessoryProtocol(uint8_t corenum, uint16_t* const Protocol)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_DEVICE),
		.bRequest      = ANDROID_Req_GetAccessoryProtocol,
		.wValue        = 0,
		.wIndex        = 0,
		.wLength       = sizeof(uint16_t),
	};

	Pipe_SelectPipe(corenum, PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(corenum, Protocol);
}

uint8_t Android_SendString(uint8_t corenum,
		const uint8_t StringIndex,
		char* String)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_VENDOR | REQREC_DEVICE),
		.bRequest      = ANDROID_Req_SendString,
		.wValue        = 0,
		.wIndex        = StringIndex,
		.wLength       = (strlen(String) + 1),
	};

	Pipe_SelectPipe(corenum, PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(corenum, String);
}

uint8_t Android_StartAccessoryMode(uint8_t corenum)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_VENDOR | REQREC_DEVICE),
		.bRequest      = ANDROID_Req_StartAccessoryMode,
		.wValue        = 0,
		.wIndex        = 0,
		.wLength       = 0,
	};

	Pipe_SelectPipe(corenum, PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(corenum, NULL);
}
