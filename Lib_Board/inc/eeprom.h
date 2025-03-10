/*****************************************************************************
 *
 *   Copyright(C) 2011, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * Embedded Artists AB assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. Embedded Artists AB
 * reserves the right to make changes in the software without
 * notification. Embedded Artists AB also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 *****************************************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H

uint8_t eeprom_test (void);
void eeprom_init (void);
int16_t eeprom_read(uint8_t* buf, uint16_t offset, uint16_t len);
int16_t eeprom_write(uint8_t* buf, uint16_t offset, uint16_t len);
uint32_t eeprom_readEui48(uint8_t* buf);


#endif /* end __EEPROM_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
