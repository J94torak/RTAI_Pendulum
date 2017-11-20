#ifndef __3718__
#define __3718__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>

/**
 * \file 3718.c
 * \brief 3718 module
 * \author Jonathan Morell - Luiz Eduardo Di Britto
 * \version 1.0
 * \date 20.11.2017
 *
 * Module to use the 3718 card.
 */


#define BASE 0x320
#define R0 BASE
#define R1 BASE  + 1
#define RANGE BASE  + 1
#define MUX BASE + 2
#define W0 BASE  + 3
#define STATUS BASE  + 8
#define CONTROLE BASE  + 9
#define COUNT_EN BASE + 10
#define W1 BASE + 11

#define RANGE_5 0
#define RANGE_0_5 1
#define RANGE_0_05 2
#define RANGE_0_005 3
#define RANGE_0__10 4
#define RANGE_0__1 5 
#define RANGE_0__0_1 6
#define RANGE_0__0_01 7
#define RANGE_10 8
#define RANGE_1 9
#define RANGE_0_1 10
#define RANGE_0_01 11

/**Init of 3712 card.
*\return Return 0 if no problem occured.
*/
int init3718(void);
/**
*Function to set a channel to read.
*\param in_channel The channel to set.
*\return Return 0 if the channel cannot be set.
*/
int SetChanel(unsigned char in_channel);
/**
*Function to set a range to a special channel.
*\param channel The channel to set the range.
*\param range The range to set.
*\return Return -1 if the channel is above 9.
*/
int ADRangeSelect(unsigned char channel,unsigned char range);
/**
*Function to read value from the ADC card.
*\return Value from 0 to 4095 corresponding of the voltage range.
*/
u16 ReadAD(void);
/**
*Function to read the current channel use from the ADC card.
*\return The current channel used
*/
u8 ReadChannel(void);
/**
*Function that transform a value to a polar volage
*\param vRef The polar voltage reference
*\param value The value ton convert
*\return Voltage corresponding to the value
*/
float valueToVoltagePolar(int vRef, int value);
/**
*Function that transform a value to a unipolar volage
*\param vRef The unipolar voltage reference
*\param value The value ton convert
*\return Voltage corresponding to the value
*/
float valueToVoltageUniPolar(int vRef, int value);

#endif
