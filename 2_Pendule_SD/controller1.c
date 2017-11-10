#include "controller1.h"

MODULE_LICENSE("GPL");

float x1;
float x2;
float x3;
float x4;

float position0;
float position90;
float angle_15;
float angle15;


float pasPosition;
float pasAngle;
float origin;
float angle0;



void init_control1(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0){

 	x1=0;
 	x2=0;
 	x3=0;
 	x4=0;
    origin=porigin;
    angle0=pangle0;
	position0=pposition0;
	position90=pposition90;
	angle_15=pangle_15;
	angle15=pangle15;
	pasPosition=(position0-position90)/POSITION_WIDTH;   //Volt/cm
    pasAngle= (angle15-angle_15)/ANGLE_WIDTH;          //volt/degre
    
}



float commande1(float angle, float position){
    int co=0;
	float x1k;
	float x2k;
	float x3k;
	float x4k;
	float commande;

	
	x1k=x1;
	x2k=x2;
	x3k=x3;
	x4k=x4;

    x1 =0.7143*x1k+0.0245*x2k-0.0007*x3k+0.0086*x4k+0.2815*angle-0.0250*position;
    x2 =0.0239*x1k+0.8608*x2k+0.01065*x3k+0.0012*x4k-0.01993*angle+0.1396*position;
    x3 =0.9139*x1k-0.3042*x2k+1.1306*x3k+0.2351*x4k-0.11488*angle+0.4000*position;
    x4 =-2.4475*x1k-0.0016*x2k-0.1546*x3k+0.72218*x4k+1.6173*angle-0.1150*position;
	
	commande= (-80.3092*x1-9.6237*x2-14.1215*x3-23.6260*x4);
    printk("Hello\n");
    commande=commande*0.8;
    printk("Hello\n");
    co=(int)(commande*10.0);
    printk("Hello2\n");
    printk("co=%d\n",co);
    if(co>98){
            commande=9.8;
    }
    else if(co<-98){
        commande=-9.8;
    }
	/*x1 = +0.6300*x1k +0.0261*x2k -0.0012*x3k +0.0082*x4k + 0.2703*angle - 0.0271*position;
	x2 = +0.0355*x1k +0.7967*x2k +0.0110*x3k +0.0015*x4k - 0.0303*angle + 0.2041*position;
	x3 = +1.2632*x1k -0.5989*x2k +1.1944*x3k +0.3042*x4k - 0.2209*angle + 0.7570*position;
	x4 = -2.6117*x1k -0.0831*x2k -0.2302*x3k +0.6403*x4k + 1.4933*angle - 0.1040*position;*/

	/*x1=0.7143*x1k+0.0245*x2k-0.0008*x3k+0.0086*x4k+0.2815*angle-0.0251*position;
	x2=0.0239*x1k+0.8609*x2k+0.0107*x3k+0.0012*x4k-0.0199*angle+0.1396*position;
	x3=0.9140*x1k-0.3043*x2k+1.1306*x3k+0.2351*x4k-0.1149*angle+0.4000*position;
	x4=-2.4476*x1k+0.0016*x2k-0.1546*x3k+0.7222*x4k+1.6173*angle-0.1150*position;*/
	
	//commande= (-80.3092*x1-9.6237*x2-14.1215*x3-23.6260*x4);
	//commande= (-104.7570*x1 -15.8810*x2 -20.5358*x3 -30.5773*x4);	

    //printk("Angle=%d\n",(int)(angle*1000.0));
   // printk("Position=%d\n",(int)(position*1000.0));
  return commande;
   

}


float conversionVoltToAngle1(float angle){
		float angle_converti=0;
		angle_converti= (angle-angle0)/pasAngle*3.14/180.0;	
		//printk("angle_converti = %d radians\n",(int)(angle_converti*1000));
		angle_converti=(((float)((int)(angle_converti*100)))/100.0);
		return angle_converti;
}

float conversionVoltToPosition1(float position){
	
	float position_converti=0;
	position_converti = (position-origin)/pasPosition/100.0;
	//printk("position_converti = %d mm\n",(int)(position_converti*1000));
	//position_converti=(((float)((int)(position_converti*100)))/100.0);
	return position_converti;
}

float commandeVoltage1(float angle, float position){
return commande1(conversionVoltToAngle1(angle),conversionVoltToPosition1(position));
}


static int init_controller1(void) {
/*int angle_fd;  
int position_fd;
int commande_fd;
angle_fd=rtf_create(0,100);  	
position_fd=rtf_create(1,100);  
commande_fd=rtf_create(2,100);   
    if(angle_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }
            if(position_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }
            if(commande_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }*/
  init_control1(POSITION0, POSITION90,ORIGIN, ANGLE_15,ANGLE15,ANGLE0);
  return 0;
}



static void exit_controller1(void) {

}

module_init(init_controller1);
module_exit(exit_controller1);

EXPORT_SYMBOL(commande1);
EXPORT_SYMBOL(conversionVoltToAngle1);
EXPORT_SYMBOL(conversionVoltToPosition1);
EXPORT_SYMBOL(commandeVoltage1);

