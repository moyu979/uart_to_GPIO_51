#include"reg52.h"

#define FUNMASK 0xF0
#define PINMASK 0x0F
#define PINNUMBER 0x07
#define GROUPMASK 0x08

unsigned char FIRST;
unsigned char SECOND;

unsigned char RET;

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
    
    RET=0x00;
    switch (FIRST & FUNMASK)
    {
    //查看某个GPIO引脚的值
    case 0x10:
        if(FIRST&GROUPMASK){
            RET=P2^(FIRST&PINNUMBER);
        }else{
            RET=P1^(FIRST&PINNUMBER);
        }
        break;
    //查看某组GPIO的值
    case 0x20:
        if(FIRST & GROUPMASK){
            RET=P2;
        }else{
            RET=P1;
        }
        break;
    //写入某个GPIO
    // case 0x40:
    //     if(FIRST&GROUPMASK){
    //         P2^(FIRST&PINNUMBER)=SECOND?1:0;
    //     }else{
    //         P1^(FIRST&PINNUMBER)=SECOND?1:0;
    //     }
    //     break;
    // //将某个GPIO与数据进行与操作
    // case 0x50:
    //     if(FIRST&GROUPMASK){
    //         P2^(FIRST&PINNUMBER)=(P2^(FIRST&PINNUMBER))&(SECOND?1:0);
    //     }else{
    //         P1^(FIRST&PINNUMBER)=(P1^(FIRST&PINNUMBER))&(SECOND?1:0);
    //     }
    //     break;
    // //将某个GPIO与数据进行或操作
    // case 0x60:
    //     if(FIRST&GROUPMASK){
    //         P2^(FIRST&PINNUMBER)=(P2^(FIRST&PINNUMBER))|(SECOND?1:0);
    //     }else{
    //         P1^(FIRST&PINNUMBER)=(P1^(FIRST&PINNUMBER))|(SECOND?1:0);
    //     }
    //     break;
    // //将某个GPIO与数据进行异或操作
    // case 0x70:
    //     if(FIRST&GROUPMASK){
    //         P2^(FIRST&PINNUMBER)=(P2^(FIRST&PINNUMBER))^(SECOND?1:0);
    //     }else{
    //         P1^(FIRST&PINNUMBER)=(P1^(FIRST&PINNUMBER))^(SECOND?1:0);
    //     }
    //     break;
    //写入某组GPIO
    case 0x80:
        if(FIRST & GROUPMASK){
            P2=SECOND;
        }else{
            P1=SECOND;
        }
        break;
    //将某组GPIO与数据进行与操作
    case 0x90:
        if(FIRST & GROUPMASK){
            P2=P2&SECOND;
        }else{
            P1=P1&SECOND;
        }
        break;
    //将某组GPIO与数据进行或操作
    case 0xa0:
        if(FIRST & GROUPMASK){
            P2=P2|SECOND;
        }else{
            P1=P1|SECOND;
        }
        break;
    //将某组GPIO与数据进行异或操作
    case 0xb0:
        if(FIRST & GROUPMASK){
            P2=P2^SECOND;
        }else{
            P1=P1^SECOND;
        }
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