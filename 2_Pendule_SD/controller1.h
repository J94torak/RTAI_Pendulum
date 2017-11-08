#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
//#include <rtai_fifos.h>
#include "3718.h"
#include "3712.h"
//Arcom21
#define POSITION0 9.424
#define POSITION90 -7.465
#define ORIGIN 1.7446
#define ANGLE_15 -4.378
#define ANGLE15 3.35
#define ANGLE0 -0.48
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control1(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande1(float position, float angle);
float conversionVoltToAngle1(float angle);
float conversionVoltToPosition1(float position);
float commandeVoltage1(float angle, float position);




#endif
