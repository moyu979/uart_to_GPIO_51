#include"reg51.h"

#define FUNMASK 0xF0
#define PINMASK 0x0F
#define PINNUMBER 0x07
#define GROUPMASK 0x08

unsigned char FIRST;
unsigned char SECOND;

unsigned char RET;

int start;

unsigned char position[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
void UART_Read_init(){
	SCON=0x50;
	TI=1;

    EA=1;//总中断开
    ES=1;//串口中断开

    TMOD=0x20;
    
    TH1=0xFA;
    TL1=0xFA;
    TR1=1;
}

void UART_Read(void) interrupt 4 using 1{
    if(RI==1){
        if(start){
            FIRST=SBUF;
            RI=0;
            start=0;
        }else{
            SECOND=SBUF;
            RI=0;
            RET=0x00;
            start=1;
            switch (FIRST & FUNMASK){
                //查看某个GPIO引脚的值
                case 0x10:
                    if(FIRST&GROUPMASK){
                        RET=P2^(FIRST&PINNUMBER)==1?'h':'l';
                    }else{
                        RET=P1^(FIRST&PINNUMBER)==1?'h':'l';
                    }
                    break;
                //查看某组GPIO的值
                case 0x20:
                    if(FIRST&GROUPMASK){
                        RET=P2;
                    }else{
                        RET=P1;
                    }
                    break;
                //写入某组GPIO
                case 0x80:
                    if(FIRST & GROUPMASK){
                        P2=SECOND;
                    }else{
                        P1=SECOND;
                    }
                    break;
                //写入某个GPIO
                case 0x40:
                    if(FIRST&GROUPMASK){
                        //置0
						if(SECOND==0){
                            P2=P2&(!position[FIRST&PINNUMBER]);
                        }
                        //置1
                        else{
                            P2=P2|position[FIRST&PINNUMBER];
                        }
                    }else{
                        //置0
						if(SECOND==0){
                            P1=P1&(!position[FIRST&PINNUMBER]);
                        }
                        //置1
                        else{
                            P1=P1|position[FIRST&PINNUMBER];
                        }
                    }
                    break;
                //将某个GPIO与数据进行与操作
                case 0x50:
                    if(FIRST&GROUPMASK){
                        //与0
                        if(SECOND==0){
                            P2=P2&(!position[FIRST&PINNUMBER]);
                        }
                        //与1
                        else{
                            P2=P2|position[FIRST&PINNUMBER];
                        }
                    }else{
                        //与0
                        if(SECOND==0){
                            P1=P1&(!position[FIRST&PINNUMBER]);
                        }
                        //与1
                        else{
                            P1=P1|position[FIRST&PINNUMBER];
                        }
                    }
                    break;
                //将某个GPIO与数据进行或操作
                case 0x60:
                    if(FIRST&GROUPMASK){
                        //或0
                        if(SECOND==0){
                            ;//或0不变就行
                        }
                        //或1
                        else{
                            P2=P2|position[FIRST&PINNUMBER];//或1相当于置1
                        }
                        
                    }else{
                        //或0
                        if(SECOND==0){
                            ;//或0不变就行
                        }
                        //或1
                        else{
                            P1=P1|position[FIRST&PINNUMBER];//或1相当于置1
                        }
                    }
                    break;
                //将某个GPIO与数据进行异或操作
                //0 xor 0=0
                //1 xor 0=1
                //因此其他位直接异或0
                //如果本位也异或0，不变，异或1，直接搞
                case 0x70:
                    if(FIRST&GROUPMASK){
                        if(SECOND==0){
                            ;
                        }else{
                            P2=P2^position[FIRST&PINNUMBER];
                        }
                    }else{
                        if(SECOND==0){
                            ;
                        }else{
                            P1=P1^position[FIRST&PINNUMBER];
                        }
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
                TI=0;
        }
    }
}

    //switch (FIRST & FUNMASK)
    //{
    //
    
    
    
    

void main(void){
    UART_Read_init();
    start=1;
    while(1){
        ;
    }
}