#include "TM4C123.h"                    // Device header
#include "PLL.h"
//#include "TM4C123GH6PM.h"
#include<stdio.h>
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_SYSPRI3_R          (*((volatile unsigned long *)0xE000ED20))
#define PORTF_DATA_R             (*((volatile unsigned long *)0x400253FC))

	 unsigned long count=0;
   void SysTick_Handler(void);
   void SYSTICK_INIT(unsigned long period);
void WaitForInterrupt(void);
void EnableInterrupts(void);

void SYSTICK_INIT(unsigned long period){
  NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R=period-1;
	NVIC_ST_CURRENT_R = 0;                 // Any write to current clears it
  //NVIC_SYSPRI3_R = (NVIC_SYSPRI3_R & 0x00FFFFFF) | 0x20000000; // Set priority 1
	NVIC_ST_CTRL_R=0x07;
}

void SysTick_Handler(void){
    GPIOF->DATA^=0x04;
	   count++;
}
 int main(){
 SYSCTL->RCGCGPIO|=0x20;
	GPIOF->DEN|=0x04;
	 GPIOF->DIR|=0x04;
	 GPIOF->AFSEL&=~0x04;
	 GPIOF->PCTL=0x00;
	 GPIOF->AMSEL&=~0x04;
	 SYSTICK_INIT(16000000);
	 EnableInterrupts();
	 GPIOF->DATA=0;
	 //PLL_Init();
	 while(1){
		 WaitForInterrupt();
	 } 
 }
 
 void EnableInterrupts(void){
    __asm ("    CPSIE  I\n");
}

void WaitForInterrupt(void){
    __asm ("    WFI\n");
}