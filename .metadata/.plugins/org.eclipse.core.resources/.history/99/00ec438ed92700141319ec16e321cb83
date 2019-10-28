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

/*
 * Embedded Artists AB.
 *
 * This file has been modified by Embedded Artists AB for the AOA Demo
 */

/** \file
 *
 *  Main source file for the AndroidAccessoryHost demo. This file contains the main tasks
 *  of the demo and is responsible for the initial application hardware configuration.
 */

#include "AndroidAccessoryHost.h"

#include "lpc_types.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"

#include "board.h"
#include "canpt.h"

#include "rgb.h"
#include "btn.h"

/******************************************************************************
 * Forward declarations
 *****************************************************************************/

static void nodeAttached(uint8_t reqId);
static void nodeDetached(uint8_t reqId);
static void valueUpdate(uint8_t reqId, uint8_t periphId, uint8_t* buf,
    uint8_t len);
static void subStarted(uint8_t reqId, uint8_t subId);
static void handleDeviceConnected(uint8_t attachedCoreNum);
uint32_t getMsTicks(void);

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/


/*
 * Message indexes for messages sent to the device
 */
#define CMD_NODE_ADD    (0)
#define CMD_NODE_REMOVE (1)
#define CMD_NODE_VALUE  (2)

/*
 * Message indexes for messages sent from the device
 */
#define CMD_SET_VALUE   (10)
#define CMD_CONNECT     (98)
#define CMD_DISCONNECT  (99)

#define MAX_NUM_SUBSCRIPTIONS  (50)

typedef struct
{
  uint8_t reqId;
  uint8_t subId;
} subscription_t;


/******************************************************************************
 * Local variables
 *****************************************************************************/


static uint8_t connected = 0;
static uint8_t doDisconnect = 0;
static uint32_t scheduleDisconnect = 0;


static uint8_t sbuf[250];

static canpt_callb_t callbacks = {
    nodeAttached,
    nodeDetached,
    valueUpdate,
    subStarted
};

static subscription_t subs[MAX_NUM_SUBSCRIPTIONS];

static uint8_t attachedCoreNum = -1;

/******************************************************************************
 * Local functions
 *****************************************************************************/

/******************************************************************************
 *
 * Description:
 *    Send a command/message to the attached Android device
 *
 * Params:
 *    [in] cmd - command
 *    [in] data - message data
 *    [in] len - length of data
 *
 *****************************************************************************/
static void sendCommand(uint8_t corenum, uint8_t cmd, uint8_t* data, uint8_t len)
{
  if (USB_HostState[corenum] != HOST_STATE_Configured)
    return;

  /* Select the data OUT pipe */
  Pipe_SelectPipe(corenum, ANDROID_DATA_OUT_PIPE);
  Pipe_Unfreeze();

  if (Pipe_IsReadWriteAllowed(corenum)) {
    Pipe_Write_8(corenum, cmd);
    Pipe_Write_Stream_LE(corenum, data, len, NULL);
    Pipe_ClearOUT(corenum);
  }

  Pipe_Freeze();

}

/******************************************************************************
 *
 * Description:
 *    Set peripheral value for a specific node
 *
 * Params:
 *    [in] nodeId - Node ID
 *    [in] devId - peripheral ID
 *    [in] d0 - data byte 0
 *    [in] d1 - data byte 1
 *
 *****************************************************************************/
static void setNodeValue(uint8_t nodeId, uint8_t devId, uint8_t d0, uint8_t d1)
{

  switch (devId) {
  case CANPT_MSG_DEV_RGB:
    console_sendString((uint8_t*)"setNodeValue: RGB\r\n");
    if (d1) {
      // on
      canpt_setRgb(nodeId, d0, 1);
    }
    else {
      // off
      canpt_setRgb(nodeId, d0, 0);
    }
    break;

  case CANPT_MSG_DEV_LED:
    console_sendString((uint8_t*)"setNodeValue: LED\r\n");
    canpt_setLed(nodeId, d1);
    break;
  }

}

/******************************************************************************
 *
 * Description:
 *    Send node attached message to Android device
 *
 * Params:
 *    [in] reqId - Node ID
 *    [in] caps - buffer with node capability IDs
 *    [in] numCaps - number of capabilities
 *
 *****************************************************************************/
static void sendNodeAttached(uint8_t corenum, uint8_t reqId, uint8_t* caps, uint8_t numCaps)
{
  uint8_t data[14];

  int i = 0;

  if (numCaps > 12) {
    numCaps = 12;
  }

  data[0] = reqId;
  data[1] = numCaps;

  for (i = 0; i < numCaps; i++) {
    data[2+i] = caps[i];
  }

  sendCommand(corenum, CMD_NODE_ADD, data, 2+numCaps);

}

/******************************************************************************
 *
 * Description:
 *    Send node detached message to Android device
 *
 * Params:
 *    [in] reqId - Node ID
 *
 *****************************************************************************/
static void sendNodeDetached(uint8_t corenum, uint8_t reqId)
{
  sendCommand(corenum, CMD_NODE_REMOVE, &reqId, 1);
}

/******************************************************************************
 *
 * Description:
 *    Handle that a Node has attached to this gateway.
 *
 * Params:
 *    [in] reqId - Node ID
 *
 *****************************************************************************/
static void handleNodeAttached(uint8_t corenum, uint8_t reqId)
{
  uint8_t buf[12];
  uint8_t data[2];
  uint8_t numCaps;

  error_t err = ERR_OK;
  int i = 0;

  err = canpt_getNodeCaps(reqId, buf, 12, &numCaps);

  if (err == ERR_OK && numCaps > 0 && numCaps <= 12) {

    /*
     * Start subscriptions on value changes
     */
    for (i = 0; i < numCaps; i++) {
      switch (buf[i]) {
      case CANPT_MSG_DEV_TEMP:

        canpt_getTemperature(reqId);

        // subscribe to 0.5 degrees changes
        data[0] = 0;
        data[1] = 50;
        canpt_subscribe(reqId, buf[i], CANPT_MSG_SUB_DIF, data, 2);
        break;
      case CANPT_MSG_DEV_LIGHT:

        canpt_getLight(reqId);

        // subscribe to changes of 10 units
        data[0] = 0;
        data[1] = 10;
        canpt_subscribe(reqId, buf[i], CANPT_MSG_SUB_DIF, data, 2);

        break;
      case CANPT_MSG_DEV_BTN:

        canpt_getButton(reqId);

        // subscribe to all changes (on/off)
        data[0] = 0;
        canpt_subscribe(reqId, buf[i], CANPT_MSG_SUB_DIF, data, 1);

        break;
      }
    }

    // notify Android device
    sendNodeAttached(corenum, reqId, buf, numCaps);
  }

}

/******************************************************************************
 *
 * Description:
 *    Handle that a Node has detached from this gateway.
 *
 * Params:
 *    [in] reqId - Node ID
 *
 *****************************************************************************/
static void handleNodeDetached(uint8_t corenum, uint8_t reqId)
{
  int i = 0;

  // clear any active subscriptions
  for (i = 0; i < MAX_NUM_SUBSCRIPTIONS; i++) {
    if (subs[i].reqId != 0) {
      subs[i].reqId = 0;
      subs[i].subId = 0;
    }
  }

  sendNodeDetached(corenum, reqId);
}

/******************************************************************************
 *
 * Description:
 *    Node attached callback
 *
 * Params:
 *    [in] reqId - Node ID
 *
 *****************************************************************************/
static void nodeAttached(uint8_t reqId)
{
  console_sendString((uint8_t*)"nodeAttached\r\n");
  if (!connected) {
    return;
  }


  handleNodeAttached(attachedCoreNum, reqId);

}

/******************************************************************************
 *
 * Description:
 *    Node detached callback
 *
 * Params:
 *    [in] reqId - Node ID
 *
 *****************************************************************************/
static void nodeDetached(uint8_t reqId)
{
  console_sendString((uint8_t*)"nodeDetached\r\n");
  if (!connected) {
    return;
  }

  handleNodeDetached(attachedCoreNum, reqId);
}

/******************************************************************************
 *
 * Description:
 *    Value changed/updated callback
 *
 * Params:
 *    [in] reqId - Node ID
 *    [in] periphId - peripheral/capability ID
 *    [in] buf - buffer containing the value
 *    [in] len - length of buffer
 *
 *****************************************************************************/
static void valueUpdate(uint8_t reqId, uint8_t periphId, uint8_t* buf,
    uint8_t len)
{
  uint8_t data[4];

  if (!connected) {
    return;
  }


  data[0] = reqId;
  data[1] = periphId;

  // always sending 2 data bytes for value
  if (len < 2) {
    data[2] = 0;
    data[3] = buf[0];
  }
  else {
    data[2] = buf[0];
    data[3] = buf[1];
  }

  sendCommand(attachedCoreNum, CMD_NODE_VALUE, data, 4);
}

/******************************************************************************
 *
 * Description:
 *    Subscription started callback
 *
 * Params:
 *    [in] reqId - Node ID
 *    [in] subId - subscription ID
 *
 *****************************************************************************/
static void subStarted(uint8_t reqId, uint8_t subId)
{
  int i = 0;

  for (i = 0; i < MAX_NUM_SUBSCRIPTIONS; i++) {
    if (subs[i].reqId == 0) {
      subs[i].reqId = reqId;
      subs[i].subId = subId;
      break;
    }
  }
}

/******************************************************************************
 *
 * Description:
 *    Handle that an Android device has been connected
 *
 *****************************************************************************/
static void handleDeviceConnected(uint8_t corenum)
{
  int i = 0;
  error_t err = ERR_OK;
  uint8_t nodeIds[10];
  uint8_t numNodes = 0;

  err = canpt_getNodes(nodeIds, 10, &numNodes);

  if (err == ERR_OK && numNodes > 0) {
    for (i = 0; i < numNodes; i++) {
      handleNodeAttached(corenum, nodeIds[i]);
    }
  }

}

/******************************************************************************
 *
 * Description:
 *    Handle that an Android device is no longer attached to this gateway
 *
 *****************************************************************************/
static void handleDeviceDisconnected(void)
{
  int i = 0;

  console_sendString((uint8_t*)"handleDeviceDisconnected\r\n");

  // cancel all subscriptions
  for (i = 0; i < MAX_NUM_SUBSCRIPTIONS; i++) {
    if (subs[i].reqId != 0) {

      canpt_unsubscribe(subs[i].reqId, subs[i].subId);

      subs[i].reqId = 0;
      subs[i].subId = 0;
    }
  }
}

/******************************************************************************
 *
 * Description:
 *
 *
 *****************************************************************************/
static void monitor_task(void)
{

  if (scheduleDisconnect > 0 && scheduleDisconnect < getMsTicks()) {
    scheduleDisconnect = 0;
    handleDeviceDisconnected();
  }

  if (!connected) {
    return;
  }

  if (doDisconnect) {
    doDisconnect = 0;
    sendCommand(attachedCoreNum, CMD_DISCONNECT, 0, 0);
    connected = 0;
    return;
  }

}

/******************************************************************************
 * Public functions
 *****************************************************************************/

/******************************************************************************
 *
 * Description:
 *    Initialize the AOA functionality
 *
 *****************************************************************************/
void androidHost_init(void)
{
  int i = 0;

  canpt_init(&callbacks);

  for (i = 0; i < MAX_NUM_SUBSCRIPTIONS; i++) {
    subs[i].reqId = 0;
  }

}

/******************************************************************************
 *
 * Description:
 *    AOA receive task
 *
 *****************************************************************************/
void androidHost_task(void)
{
  int i = 0;

  monitor_task();

  if (attachedCoreNum == -1) return;

  if (USB_HostState[attachedCoreNum] != HOST_STATE_Configured)
    return;

  /* Select the data IN pipe */
  Pipe_SelectPipe(attachedCoreNum, ANDROID_DATA_IN_PIPE);
  Pipe_Unfreeze();

  /* Check to see if a packet has been received */
  if (Pipe_IsINReceived(attachedCoreNum))
  {
    /* Re-freeze IN pipe after the packet has been received */
    Pipe_Freeze();


    /* Check if data is in the pipe */
    if (Pipe_IsReadWriteAllowed(attachedCoreNum))
    {
      uint8_t numBytes = Pipe_BytesInPipe(attachedCoreNum);

      if (numBytes > 0) {

        uint8_t c = Pipe_Read_8(attachedCoreNum);
        numBytes--;

        switch (c) {

        case CMD_SET_VALUE:

          if (numBytes == 4) {
            setNodeValue(Pipe_Read_8(attachedCoreNum), Pipe_Read_8(attachedCoreNum),
                Pipe_Read_8(attachedCoreNum), Pipe_Read_8(attachedCoreNum));
          }

          break;

        case CMD_CONNECT:
          connected = 1;
          handleDeviceConnected(attachedCoreNum);
          break;
        case CMD_DISCONNECT:
          doDisconnect = 1;
          break;
        default:

          for (i = 0; i < numBytes; i++) {
            c = Pipe_Read_8(attachedCoreNum);
          }
          break;
        }



      }

    }

    /* Clear the pipe after all data in the packet has been read, ready for the next packet */
    Pipe_ClearIN(attachedCoreNum);
  }

  /* Re-freeze IN pipe after use */
  Pipe_Freeze();
}



/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(const uint8_t corenum)
{
	//	console_sendString((uint8_t*)"Device Attached.\r\n");
	sprintf((char*)sbuf, "Device Attached %d\r\n", corenum);
	console_sendString(sbuf);
	attachedCoreNum = corenum;
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(const uint8_t corenum)
{
  //  console_sendString((uint8_t*)"\r\nDevice Unattached.\r\n");
  sprintf((char*)sbuf, "\r\nDevice Unattached %d\r\n", corenum);
  console_sendString(sbuf);
  connected = 0;

  //handleDeviceDisconnected();
  scheduleDisconnect = getMsTicks() + 1000;
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(const uint8_t corenum)
{
  //  console_sendString((uint8_t*)"Getting Device Data.\r\n");
  sprintf((char*)sbuf, "Getting Device Data %d\r\n", corenum);
  console_sendString(sbuf);

  /* Get and process the configuration descriptor data */
  uint8_t ErrorCode = ProcessDeviceDescriptor(corenum);

  bool RequiresModeSwitch = (ErrorCode == NonAccessoryModeAndroidDevice);

  /* Error out if the device is not an Android device or an error occurred */
  if ((ErrorCode != AccessoryModeAndroidDevice) && (ErrorCode != NonAccessoryModeAndroidDevice))
  {
    if (ErrorCode == ControlError)
      console_sendString((uint8_t*)"Control Error (Get Device).\r\n");
    else
      console_sendString((uint8_t*)"Invalid Device.\r\n");

    sprintf((char*)sbuf, " -- Error Code: %d\r\n", ErrorCode);
    console_sendString(sbuf);
    return;
  }

  sprintf((char*)sbuf, "Android Device Detected - %sAccessory mode.\r\n", (RequiresModeSwitch ? "Non-" : ""));
  console_sendString(sbuf);

  /* Check if a valid Android device was attached, but it is not current in Accessory mode */
  if (RequiresModeSwitch)
  {
    uint16_t AndroidProtocol;

    /* Fetch the version of the Android Accessory Protocol supported by the device */
    if ((ErrorCode = Android_GetAccessoryProtocol(corenum, &AndroidProtocol)) != HOST_SENDCONTROL_Successful)
    {

      sprintf((char*)sbuf, "Control Error (Get Protocol).\r\n"
          " -- Error Code: %d\r\n"
          ,ErrorCode);
      console_sendString(sbuf);
      return;
    }

    /* Validate the returned protocol version */
    if (AndroidProtocol == 0 || AndroidProtocol >  ANDROID_PROTOCOL_Accessory)
    {

      sprintf((char*)sbuf, "Unsupported AOA protocol version: %d\r\n" ,AndroidProtocol);
      console_sendString(sbuf);
      return;
    }

    /* Send the device strings and start the Android Accessory Mode */

    // Bug: The first call to _SendString seem to generate
    //      bad data. At least it isn't received correctly
    //      on the Android device.
    //
    // Workaround: calling twice for Manufacturer
    Android_SendString(corenum, ANDROID_STRING_Manufacturer, "Embedded Artists AB");

    Android_SendString(corenum, ANDROID_STRING_Manufacturer, "Embedded Artists AB");
    Android_SendString(corenum, ANDROID_STRING_Model,        "AOA Board - Nodes");
    Android_SendString(corenum, ANDROID_STRING_Description,  "Demo - AOA Nodes");
    Android_SendString(corenum, ANDROID_STRING_Version,      "1.0");
    Android_SendString(corenum, ANDROID_STRING_URI,          "http://www.embeddedartists.com/_aoa/Demo_AOA_Nodes.apk");
    Android_SendString(corenum, ANDROID_STRING_Serial,       "N/A");


    Android_StartAccessoryMode(corenum);
    return;
  }

  console_sendString((uint8_t*)"Getting Config Data.\r\n");

  /* Get and process the configuration descriptor data */
  if ((ErrorCode = ProcessConfigurationDescriptor(corenum)) != SuccessfulConfigRead)
  {
    if (ErrorCode == ControlError)
      console_sendString((uint8_t*)"Control Error (Get Configuration).\r\n");
    else
      console_sendString((uint8_t*)"Invalid Device.\r\n");

    sprintf((char*)sbuf, " -- Error Code: %d\r\n", ErrorCode);
    console_sendString(sbuf);

    return;
  }

  /* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
  if ((ErrorCode = USB_Host_SetDeviceConfiguration(corenum, 1)) != HOST_SENDCONTROL_Successful)
  {

    sprintf((char*)sbuf, "Control Error (Set Configuration).\r\n"
        " -- Error Code: %d\r\n", ErrorCode);
    console_sendString(sbuf);
    return;
  }

  console_sendString((uint8_t*)"Accessory Mode Android Enumerated.\r\n");
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t corenum, const uint8_t ErrorCode)
{
  USB_Disable();

  sprintf((char*)sbuf, "Host Mode Error\r\n"
      " -- Error Code %d\r\n", ErrorCode);
  console_sendString(sbuf);

  for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t corenum,
    const uint8_t ErrorCode,
    const uint8_t SubErrorCode)
{
  sprintf((char*)sbuf, "Dev Enum Error\r\n"
      " -- Error Code %d\r\n"
      " -- Sub Error Code %d\r\n"
      " -- In State %d\r\n", ErrorCode, SubErrorCode, USB_HostState);
  console_sendString(sbuf);

}

