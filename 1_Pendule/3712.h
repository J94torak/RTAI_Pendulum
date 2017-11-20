/**
 * \file 3712.h
 * \brief 3712 module
 * \author Jonathan Morell - Luiz Eduardo Di Britto
 * \version 1.0
 * \date 20.11.2017
 *
 * Module to use the 3712 card.
 */

#ifndef __3712__
#define __3712__

#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>

#define BASE_3712 0x300
#define PCM3712_DA0 BASE_3712
#define PCM3712_DA1 (BASE_3712 +2)
#define PCM3712_SYNC (BASE_3712 +4)
#define PCM3712_OUT (BASE_3712 +5)

/**Init of 3712 card.
*\return Return 0 if no problem occured
*/
int init3712(void);
/**Allocation of a voltage value to a channel.
*
*The value to allocate is a value between 0 to 4095.
*The value is stored on 2 register of the equivalent of 12 bits.
*(2^12-1=4095)
*\param channel The channel to send the value
*\param value The value to send
*/
void SetDA(unsigned char channel,int value);
/**Send the correct voltage value to the card.
*
*Use the fonction VoltageToValue for the conversion and SetDA to send the value converted
*\param channel The channel to send the value
*\param voltage The voltage to send
*\return Return 0 if no problem occured
*/
int SetDAVol(unsigned char channel,float voltage);
/**Transformation to get the equivalent value to a voltage.
*
*Transform a voltage to a value where the maximum-minimum voltage is 10 and -10.
*The maximum minimum voltage follow the card standard voltage that can be provided.
*\param voltage The voltage to transform in value
*\return The value corresponding to the voltage
*
*/
int VoltageToValue(float voltage);

#endif









