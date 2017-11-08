#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>

#define POSITION0 8.84
#define POSITION90 -7.95
#define ORIGIN 0.114
#define ANGLE_15 -3.58
#define ANGLE15 3.58
#define ANGLE0 0.0
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande(float position, float angle);
float conversionVoltToAngle(float angle);
float conversionVoltToPosition(float position);
float commandeVoltage(float angle, float position);

#endif
