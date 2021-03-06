
#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include"3718.h"
#include"3712.h"
#include "controller.h"
#include "sensor.h"


MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000    //  1 ms
#define PERIODE_CONTROL 10000000 //10ms
#define N_BOUCLE 10000000
#define NUMERO 1
#define PRIORITE 1






/* RT_TASK */
static RT_TASK tache_pendule;


void pendule(long arg){

float commande=0;
float commande2=0;
float angleV=0;
float positionV=0;
int co=0;

	
	while(1){
		
		angleV   = acquisition_angle();
		positionV = acquisition_position();
		printk("positionV=%dmv\n",(int)(positionV*1000.0)); 
		printk("angleV=%dmv\n",(int)(angleV*1000.0)); 
		commande  = commandeVoltage(angleV,positionV);
        commande=4.0*commande;
        printk("Hello");
        co=(int)(commande*1000.0);
        printk("Hello2");
        if(co>9950){
            commande=9.95;
        }
        else if(co<-9950){
            commande=-9.95;
        }
		//printk("Commande = %dmv\n", (int)(commande*1000.0));
		SetDAVol(0, commande);       //arcom22 2.5*commande);//arcom12 0.75*commande);//arcom21 4*commande);
		rt_task_wait_period();
		
	}

}

static int pendule_init(void) {

  int ierr;
  RTIME now;


    /* creation tache périodiques*/
  
  rt_set_oneshot_mode();
    
   ierr = rt_task_init(&tache_pendule,pendule,0,STACK_SIZE, PRIORITE, 1, 0);  
  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
  rt_task_make_periodic(&tache_pendule, now, nano2count(PERIODE_CONTROL));
 

 
 
 return(0);
}

static void pendule_exit(void) {
 stop_rt_timer(); 
 rt_task_delete(&tache_pendule);

}



module_init(pendule_init);
module_exit(pendule_exit);
