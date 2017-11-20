#include "3712.h"

/**
 * \file 3712.c
 * \brief 3712 module
 * \author Jonathan Morell - Luiz Eduardo Di Britto
 * \version 1.0
 * \date 20.11.2017
 *
 * Module to use the 3712 card.
 */

MODULE_LICENSE("GPL");

/**
*Init of 3712 card.
*
*/
int init3712(void){
outb(0x80,PCM3712_OUT);
return 0;
}


/**Allocation of a voltage value to a channel.
*
*The value to allocate is a value between 0 to 4095.
*The value is stored on 2 register of the equivalent of 12 bits.
*(2^12-1=4095)
*\param channel The channel to send the value
*\param value The value to send
*/
void SetDA(unsigned char channel,int value){

/*Transformation to store the value correctly on the 2 bits.
*
*Follow the recommandation from the 3712 datasheet.
*/
int q=value/256;
int r=value%256;
if(channel==0x00){
	outb(r&0xFF,PCM3712_DA0);
	outb(q&0x0F,PCM3712_DA0+1);
	outb(0xFF,PCM3712_SYNC);
}else if(channel==0x01){
	outb(r&0xFF,PCM3712_DA1);
	outb(q&0x0F,PCM3712_DA1+1);
	outb(0xFF,PCM3712_SYNC);
	}
}

/**Send the correct voltage value to the card.
*
*Use the fonction VoltageToValue for the conversion and SetDA to send the value converted
*\param channel The channel to send the value
*\param voltage The voltage to send
*\return Return 0 if no problem occured
*/
int SetDAVol(unsigned char channel,float voltage){

int value=0;
#ifdef DEBUG
printk("Commande input SetDAVol:%d \n",(int) (voltage*1000.0));
#endif
value=VoltageToValue(voltage);
#ifdef DEBUG
printk("Value=%d\n",value);
#endif
SetDA(channel,value);
return 0;
}

/**Transformation to get the equivalent value to a voltage.
*
*Transform a voltage to a value where the maximum-minimum voltage is 10 and -10.
*The maximum minimum voltage follow the card standard voltage that can be provided.
*\param voltage The voltage to transform in value
*\return The value corresponding to the voltage
*
*/
int VoltageToValue(float voltage){

return (int)(voltage/10.0*2048.0+2048.0);
}

/**Init of the module of the card 3712.
*
*/
static int init_3712(void) {
  init3712();
  return 0;
}

/**Exit of the module of the card 3712.
*
*/
static void exit_3712(void) {
}


module_init(init_3712);
module_exit(exit_3712);

EXPORT_SYMBOL(VoltageToValue);
EXPORT_SYMBOL(SetDA);
EXPORT_SYMBOL(SetDAVol);
