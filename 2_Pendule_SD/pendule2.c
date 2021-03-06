#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include"3718.h"
#include"3712.h"
#include "controller1.h"
#include "sensor.h"
#include "SJA1000.h"


MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000000    //  1 ms
#define PERIODE_CONTROL  10000000 //10ms
#define PERIODE_CONTROL2 10000000 //10ms
#define N_BOUCLE 10000000
#define NUMERO1 1
#define NUMERO2 2
#define NUMERO3 3
#define NUMERO4 4
#define PRIORITE1 1
#define PRIORITE2 2
#define PRIORITE3 3
#define PRIORITE4 4

#define SYNCHRONE   1 // 1 synchrone 0 asyncrone

#define IRQ 5

/* RT_TASK */

static RT_TASK acquisition;
static RT_TASK control;
static RT_TASK actuator;


u16 angle_pendule1;
u16 position_pendule1;
u16 commande_pendule1;

u16 angle_pendule2;
u16 position_pendule2;
u16 commande_pendule2;


void control_pendule1(long arg){
u16 commande_pendule1l=0;
while(1){
commande_pendule1=(u16) VoltageToValue(commandeVoltage1(valueToVoltagePolar(5, (int)angle_pendule1),valueToVoltagePolar(10,(int)position_pendule1)));
commande_pendule1l=commande_pendule1;
//printk("commande pendule 1 envoyé: %d\n",(int) commande_pendule1l);
send(0x12,2,&commande_pendule1l);
//printk("commande pendule 1 envoyé: %d\n",(int) commande_pendule1);
rt_task_suspend (&control);
}
}

void acquisition_pendule2(long arg){
u16 envoie[2];

while(1){
angle_pendule2 = acquisition_angle();
position_pendule2 = acquisition_position();
envoie[0] = angle_pendule2;
envoie[1] = position_pendule2;

send(0x20,4,&envoie);
//printk("angule pendule 2 envoyé: %d\n",(int)(1000.0*valueToVoltagePolar(5,(int)angle_pendule2)) );
//printk("position pendule 2 envoyé: %d\n",(int)(1000.0*valueToVoltagePolar(10,(int)position_pendule2)) );
	
	




rt_task_wait_period();
}

}


void actuator_pendule2(long arg){

float commande=0.0;
while(1){
commande=valueToVoltagePolar(10,(int) commande_pendule2);
SetDAVol(0,commande);
rt_task_suspend (&actuator);
}

}




void lecture(void){
	
	u16 adress[2];
    int id=0;
    int dlc=0;

	
	receive(&adress, &id,&dlc);
	
	////printk("id=%d\n",id);
	////printk("dlc=%d\n",dlc);
	////printk("valeur recue = %d\n",adress[0]);
	if(id==0x22 && dlc==2){
        commande_pendule2=adress[0];
       // printk("commande adress 0 = %d\n",commande_pendule2);
        rt_task_resume(&actuator);//rtask_resume actuator
		 
    }
   if(id==0x10 && dlc==4){
        angle_pendule1=adress[0];
        // printk("angle recue = %d mv\n",(int)(1000.0*valueToVoltagePolar(5,(int)adress[0])));
        position_pendule1=adress[1];
         //printk("pos recue = %d mv\n",(int)(1000.0*valueToVoltagePolar(10,(int)adress[1])));
        rt_task_resume(&control);//rtask_resume control
		  
    }
	rt_ack_irq(IRQ);/* acquittement de l'interruption */
	

}


static int pendule2_init(void) {

  int ierr_1,ierr_3,ierr_4;
  RTIME now;
	 /*mode interruption*/
	rt_global_cli(); /* desactivation des IT */
	rt_request_global_irq(IRQ,lecture); /*installation du handler */                                           /* sur l'IT num_irq       */
	rt_startup_irq(IRQ); /* activation de la ligne d'interruption */
	rt_global_sti(); /* re-activation des IT */
	
    /* creation tache périodiques*/
  rt_set_oneshot_mode();
  ierr_1 = rt_task_init(&acquisition,acquisition_pendule2,0,STACK_SIZE, PRIORITE2, 0, 0);
  
  
  ierr_3 = rt_task_init(&control,control_pendule1,0,STACK_SIZE, PRIORITE3, 1, 0);
  ierr_4 = rt_task_init(&actuator,actuator_pendule2,0,STACK_SIZE, PRIORITE4, 1, 0);
   

  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();

rt_task_make_periodic(&acquisition, now, nano2count(PERIODE_CONTROL));

 

 
 

 
 
 return(0);
}

static void pendule2_exit(void) {

/*desactive mode interruption*/
	rt_shutdown_irq(IRQ);/* désactivation de l'IT num_irq */
	rt_free_global_irq(IRQ); /* désintallation du handler */


   stop_rt_timer(); 
 rt_task_delete(&acquisition);

 rt_task_delete(&control);
rt_task_delete(&actuator);
}



module_init(pendule2_init);
module_exit(pendule2_exit);

