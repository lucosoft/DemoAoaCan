/*****************************************************************************************************//**
*
* @file		GPIO.h
* @brief	Módulo para manejo de Entradas y Salidas de Propósito General (GPIO: General Purpose IO).
* 			Este módulo es un complemento al desarrollado por NXP como librería y que esta incluido en
* 			este proyecto (lpc17xx_gpio.c y lpc17xx_gpio.h)
* @version	1.00
* @date		26/09/2013
* @author	Daniel J. López Amado (DJLA)
*
*
*********************************************************************************************************
*** REVISION HISTORY
*
********************************************************************************************************/


/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "My_Types.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/
// Definición de Puertos
#define PORT_0		 0
#define PORT_1		 1
#define PORT_2		 2
#define PORT_3		 3
#define PORT_4		 4

// Definición de Pines
#define PIN_0		 0
#define PIN_1		 1
#define PIN_2		 2
#define PIN_3		 3
#define PIN_4		 4
#define PIN_5		 5
#define PIN_6		 6
#define PIN_7		 7
#define PIN_8		 8
#define PIN_9		 9
#define PIN_10		10
#define PIN_11		11
#define PIN_12		12
#define PIN_13		13
#define PIN_14		14
#define PIN_15		15
#define PIN_16		16
#define PIN_17		17
#define PIN_18		18
#define PIN_19		19
#define PIN_20		20
#define PIN_21		21
#define PIN_22		22
#define PIN_23		23
#define PIN_24		24
#define PIN_25		25
#define PIN_26		26
#define PIN_27		27
#define PIN_28		28
#define PIN_29		29
#define PIN_30		30
#define PIN_31		31


/********************************************************************************************************
*** MACROS
********************************************************************************************************/
/***************************************************************************//**
 * @fn			GPIO_GETpINsTATE()
 * @brief		Retorna el Estado del Pin pasado como parámetro teniendo en
 *              cuenta su Nivel de Actividad
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		Estado del Pin. Es uno de los tipos definidos en la enumeración DIGITAL_STATE
 ******************************************************************************/
#define GPIO_GETpINsTATE(portNum, pinNum, activity)			((activity == ACTIVE_HIGH) ? \
		                                            		((DIGITAL_STATE)((((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOPIN & (0x01 << pinNum)) >> pinNum)) : \
		                                            		((DIGITAL_STATE)!((((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOPIN & (0x01 << pinNum)) >> pinNum)))

/***************************************************************************//**
 * @fn			GPIO_SETpINsTATE()
 * @brief		Setea el Estado del Pin pasado como parámetro segun se indica:
 *              STATE_ON  && ACTIVE_HIGH ==> Pone un 1 en el Pin
 *              STATE_ON  && ACTIVE_LOW  ==> Pone un 0 en el Pin
 *              STATE_OFF && ACTIVE_HIGH ==> Pone un 0 en el Pin
 *              STATE_OFF && ACTIVE_LOW  ==> Pone un 1 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @param[in]	state	 	Estado del Pin: Valores posibles
 *			                - STATE_OFF
 *          			    - STATE_ON
 * @return		void
 ******************************************************************************/
#define GPIO_SETpINsTATE(portNum, pinNum, activity, state) 	((state == STATE_ON) ? \
		                                                   	GPIO_SETpIN(portNum, pinNum, activity) : \
		                                                   	GPIO_CLRpIN(portNum, pinNum, activity))

/***************************************************************************//**
 * @fn			GPIO_SETpIN()
 * @brief		Pone a STATE_ON el Estado del Pin pasado como parámetro segun se indica:
 *              ACTIVE_HIGH ==> Pone un 1 en el Pin
 *              ACTIVE_LOW  ==> Pone un 0 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		void
 ******************************************************************************/
#define GPIO_SETpIN(portNum, pinNum, activity) 				((activity == ACTIVE_HIGH) ? \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOSET |= (0x01 << pinNum)) : \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOCLR |= (0x01 << pinNum)))

/***************************************************************************//**
 * @fn			GPIO_CLRpIN()
 * @brief		Pone a STATE_OFF el Estado del Pin pasado como parámetro segun se indica:
 *              ACTIVE_HIGH ==> Pone un 0 en el Pin
 *              ACTIVE_LOW  ==> Pone un 1 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		void
 ******************************************************************************/
#define GPIO_CLRpIN(portNum, pinNum, activity) 				((activity == ACTIVE_HIGH) ? \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOCLR |= (0x01 << pinNum)) : \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIOSET |= (0x01 << pinNum)))

/***************************************************************************//**
 * @fn			GPIO_SETpINdIR()
 * @brief		Setea la dirección del Pin pasado como parámetro:
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	dir 		Dirección del Pin: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_DIRECTION
 * @return		void
 ******************************************************************************/
#define GPIO_SETpINdIR(portNum, pinNum, dir) 				(((PIN_DIRECTION)dir == (PIN_DIRECTION)DIR_IN) ? \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIODIR &= ~(0x01 << pinNum)) : \
		                                            		(((LPC_GPIO_TypeDef *)LPC_GPIO_BASE+portNum)->FIODIR |= (0x01 << pinNum)))


/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/
typedef enum {RES_PULL_UP = 0, RES_LAST_STATE = 1, RES_NONE = 2, RES_PULL_DOWN = 3} PIN_RES_MODE;
typedef enum {NOT_OPEN_DRAIN = 0, OPEN_DRAIN = 1} PIN_OD_MODE;
typedef enum {ACTIVE_LOW = 0, ACTIVE_HIGH = 1} PIN_ACTIVITY ;
typedef enum {DAFAULT_FUNC = 0, FIRST_ALT_FUNC = 1, SECOND_ALT_FUNC = 2, THIRD_ALT_FUNC = 3} PIN_FUNCTION;
typedef enum {DIR_IN = 0, DIR_OUT = 1} PIN_DIRECTION;


/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/
void GPIO_InitPinAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_DIRECTION dir, PIN_RES_MODE resMode, PIN_OD_MODE odMode);
void GPIO_InitPinNotAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func, PIN_RES_MODE resMode, PIN_OD_MODE odMode);
void GPIO_SetPinFunc(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func);
void GPIO_SetResistorMode ( uint8_t portNum, uint8_t pinNum, PIN_RES_MODE resMode);
void GPIO_SetOpenDrainMode( uint8_t portNum, uint8_t pinNum, PIN_OD_MODE odMode);


/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif
