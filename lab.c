#include "TM4C123GH6PM.h"
#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include <math.h>

#define PORTF_DATA  (*((volatile unsigned long *)0x40025038))

void Delay(unsigned long counter);
void initUART(void);
void UARTTransmitter(unsigned char data);
void printstring(char *str);


void test(void);

void keypad_Init(void);
char keypad_takekey(void);

char mesage[12];

unsigned int ncols = 0;
unsigned int nrows = 0;                                                                    
unsigned const char symbol[4][3] = {{'1', '2', '3'},
                                   { '4', '5', '6'},
                                   { '7', '8', '9'},
                                   { '*', '0', '#'}};

char keyvalue;
																	 
int main(void)
{
	initUART();      
	keypad_Init();
	
	while(1) // main loop
	{
//		keyvalue=keypad_takekey(); // keypadden alinan degeri keyvalue icine atar 
//		Delay(1000); // 10 ms bekle
//		sprintf(mesage,"\r\n Keypadden algilanan deger : %c ",keyvalue); // ekrana yazilacak olan stringi paket/framepwork haline geitirir
//		printstring(mesage); // ekrana paket haline getirilmis olan message degiskenini yazar
		int k=0;
		
		char birinciSayiChar[4]={0};
		char ikinciSayiChar[4]={0};
		
	  uint16_t birinciSayiInt = 0;
		uint16_t ikinciSayiInt = 0;
		
		uint32_t ortalama = 0;
		
		printstring("\r\n                              Uyari ! ");
		printstring("\r\n ================================================================");
		printstring("\r\n === Sayi giris islemininizi yaptiktan sonra # tusuna basin ! ===");
		printstring("\r\n ================================================================");
		printstring("\r\n Lutfen birinci sayiyi giriniz : ");
		
		while(1) // kullanicinin girdigi sayiyi alma
		{
			keyvalue=keypad_takekey();
			Delay(1000);
			if(keyvalue!='#')
			{
				birinciSayiChar[k]=keyvalue;
				UARTTransmitter(keyvalue);
			}
			else
				break;
			k++;
		}
		k=0;
		printstring("\r\n Lutfen ikinci sayiyi giriniz : ");
		
		while(1) // kullanicinin girdigi sayiyi alma
		{
			keyvalue=keypad_takekey();
			Delay(1000);
			if(keyvalue!='#')
			{
				ikinciSayiChar[k]=keyvalue;
				UARTTransmitter(keyvalue);
			}
			else
				break;
			k++;
		}
		
		birinciSayiInt=atoi(birinciSayiChar);
		ikinciSayiInt=atoi(ikinciSayiChar);
		
		ortalama=(birinciSayiInt+ikinciSayiInt)/2;
		
		sprintf(mesage,"\r\n \r\n Ortalama : %d \r\n \r\n \r\n",ortalama);
		printstring(mesage);
	}
}

void initUART(void)
{
	  SYSCTL->RCGCUART |= 0x20; // to enable clock of UART5
    SYSCTL->RCGCGPIO |= 0x10; // to enable clock to PORTE for PE4(Rx) and PE5(Tx)
    Delay(1);
    
    UART5->CTL = 0;           // to disable UART5 module      
    UART5->IBRD = 104;        // 9600 baudrate (integrer part = 104) [9600=16MHz / 16 x baud divisior]
    UART5->FBRD = 11;       	// float part = 11
    UART5->CC = 0;            // 0x00 select system clock
    UART5->LCRH = 0x60;       // 8 bit data length - no parity bit , no FIFO
    UART5->CTL = 0x301;       // to enable UART5 module (to set tx and rx)

    // GPIO Config. To Set Uart peripheral
    GPIOE->DEN = 0x30;        
    GPIOE->AFSEL = 0x30;   
    GPIOE->AMSEL = 0;    
    GPIOE->PCTL = 0x00110000;     
}
void UARTTransmitter(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); // wait tx buffer
    UART5->DR = data;    
}

void printstring(char *str)
{
  while(*str)
	{
		UARTTransmitter(*(str++));
	}
}
void Delay(unsigned long counter) 
{
	unsigned long i = 0;
	for(i=0; i< counter*1000; i++);	
}

void keypad_Init(void)
{
  SYSCTL->RCGCGPIO |= 0x0C;            
  while ((SYSCTL->RCGCGPIO&0x0C)==0);  // to active GPIOC & GPIOD clock
	GPIOD->LOCK = 0x4C4F434B;   		     
  GPIOC->CR  |= 0xE0;             		 
  GPIOD->CR  |= 0x0F;                  
  GPIOC->DIR |= 0xE0;                  
  GPIOD->DIR |= 0x00;                  
  GPIOD->PDR |= 0x0F;                  
  GPIOC->DEN |= 0xE0; // to enable GPIOC Port                  
  GPIOD->DEN |= 0x0F; // to enable GPIOD Port                 
}

char keypad_takekey(void) // keypadden deger okur
{
	while(1)
	{
		int i=0;
		int j=0;
 
		for(i=0;i<3;i++)                        
		{
			GPIOC->DATA = (1 << (i+5));
			Delay(2);
			for(j=0;j<4;j++)                     
			{
				if((GPIOD->DATA & 0x0F) & (1 << j))
				{
					return symbol[j][i];
				}
			}
		}
	}
}

