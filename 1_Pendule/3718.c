#include "3718.h"

/**
 * \file 3718.c
 * \brief 3718 module
 * \author Jonathan Morell - Luiz Eduardo Di Britto
 * \version 1.0
 * \date 20.11.2017
 *
 * Module to use the 3718 card.
 */

MODULE_LICENSE("GPL");

/**Init of 3712 card.
*\return Return 0 if no problem occured.
*/
int init3718(void){
outb(0x00,CONTROLE); 
outb(0x01,COUNT_EN);
return 0;
}

/**
*Function to set a channel to read.
*\param in_channel The channel to set.
*\return Return 0 if the channel cannot be set.
*/
int SetChanel(unsigned char in_channel){
unsigned char v_channel=(in_channel<<4)+in_channel;
if(in_channel>9) return -1;
outb(v_channel,MUX);
return (int)(ReadChannel()==(u8)in_channel);
}


/**
*Function to set a range to a special channel.
*\param channel The channel to set the range.
*\param range The range to set.
*\return Return -1 if the channel is above 9.
*/
int ADRangeSelect(unsigned char channel,unsigned char range){
unsigned char v_channelBefore=inb(MUX);
if(channel>9) return -1;
SetChanel(channel);
outb(range,RANGE);
SetChanel(v_channelBefore&0x0F);
return 0;
}

/**
*Function to read value from the ADC card.
*\return Value from 0 to 4095 corresponding of the voltage range.
*/
u16 ReadAD(void){
u16 value;
while((inb(STATUS)&0x80)!=0x00);
outb(0xFF,R0);
while((inb(STATUS)&0x90)!=0x10);
value=(u16)((inb(R0)>>4)|(inb(R1)<<4));
outb(0x00,STATUS);
return value;
}

/**
*Function to read the current channel use from the ADC card.
*\return The current channel used
*/
u8 ReadChannel(void){
while((inb(STATUS)&0x80)!=0x00);
outb(0xFF,R0);
while((inb(STATUS)&0x90)!=0x10);
return (u8)(inb(R0)&(0x0F));
}

/**
*Function that transform a value to a polar volage
*\param vRef The polar voltage reference
*\param value The value ton convert
*\return Voltage corresponding to the value
*/
float valueToVoltagePolar(int vRef, int value){

return ((float)vRef)*(((float)value)-2048.0)/2048.0;
}

/**
*Function that transform a value to a unipolar volage
*\param vRef The unipolar voltage reference
*\param value The value ton convert
*\return Voltage corresponding to the value
*/
float valueToVoltageUniPolar(int vRef, int value){

return ((float)vRef)*2.0*((float)value)/4096.0;
}

/** Init the module of the 3718 card
*
*/
static int init_3718(void) {

init3718();
return 0;
}

/** Exit the module of the 3718 card
*
*/
static void exit_3718(void) {
}
module_init(init_3718);
module_exit(exit_3718);

EXPORT_SYMBOL(SetChanel);
EXPORT_SYMBOL(ADRangeSelect);
EXPORT_SYMBOL(ReadAD);
EXPORT_SYMBOL(ReadChannel);
EXPORT_SYMBOL(valueToVoltagePolar);
EXPORT_SYMBOL(valueToVoltageUniPolar);
