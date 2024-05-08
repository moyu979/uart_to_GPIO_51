#include<REG51.h>

#define FUNMASK 0xF0
#define GROUPMASK 0x08
#define PINMASK 0x07 

unsigned char FIRST;
unsigned char SECOND;

unsigned char RET;

sbit sP1[] = {P1^0,P1^1,P1^2,P1^3,P1^4,P1^5,P1^6,P1^7};
sbit sP2[] = {P2^0,P2^1,P2^2,P2^3,P2^4,P2^5,P2^6,P2^7};

void UART_Read_init(){
    EA=1;//总中断开
    ES=1;//串口中断开

    TMOD=0x20;
    SCON=0x50;
    TH1=0xF3;
    TL1=0xF3;
    PCON=0x80;
    TR1=1;
}

void UART_Read(void) interrupt 4 using 1{
    RI=0;
    FIRST=SBUF;
    while(!RI){
        ;
    }
    RI=0;
    SECOND=SBUF;
    
    switch (FIRST & FUNMASK)
    {
    case 0x10:
        getGpio();
        break;
    case 0x20:
        getGpioGroup();
        break;
    case 0x40:
        writeGpio();
        break;
    case 0x50:
        andGpio();
        break;
    case 0x60:
        orGpio();
        break;
    case 0x70:
        xorGpio();
        break;
    case 0x80:
        writeGpioGroup();
        break;
    case 0x90:
        andGpioGroup();
        break;
    case 0xa0:
        orGpioGroup();
        break;
    case 0xb0:
        xorGpioGroup();
        break;
    default:
        break;
    }

    SBUF=RET;
    while(TI==0);
    TI=0;
}

void main(void){
    UART_Read_init();
    while(1){
        ;
    }
}