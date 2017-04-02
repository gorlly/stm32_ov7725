

#include "stm32f10x.h"  //新版库函数头文件引用
#include "../core/core_cm3.h"

//#include "stm32f10x_conf.h"
#include "../system/delay.h"
#include "../system/usart.h"
#include "../system/sys.h"
#include "./bsp_ov7725.h"
#include "./dma.h"

//#define BUFF_SIZE 200;


#define SEND_BUF_SIZE 19202

extern uint8_t Ov7725_vsync;
extern OV7725_MODE_PARAM cam_mode;

const u8 TEXT_TO_SEND[]={"STM32 Serial Port DMA test!\r\n"};



u8 SendBuff[SEND_BUF_SIZE] = {0xaa,0x03};// 帧头，用于区分数据
 
void read_camara_fifo(void) //--------读取图像程序-——----—//
{
    u16 color;
    u16 YUV_U;
    u16 row,col;  
	uint32_t cnt = 2;

        FIFO_PREPARE;   //开始复位读指针
		for(col=0;col<120;col++){			//coloum: width   120 / 240
			for(row=0;row<160;row++){ 	  //row : length  160     / 320 						
                
                OV7725_RCK_L;	
				color=OV7725_DATA;	//读数据
				OV7725_RCK_H;

                OV7725_RCK_L;	
				YUV_U=OV7725_DATA;	//读数据
				OV7725_RCK_H;
					
			    SendBuff[cnt++]  = (u8)color;		
							  						  	
		    }

	    }	

}	   

int main(void)
{
//    u8 i=0;
    delay_init();
    NVIC_Configuration();
    uart_init(115200);

    OV7725_GPIO_Config();        //外部中断初始化
    OV7725_Init();
	/*根据摄像头参数组配置模式*/

//	OV7725_Special_Effect(cam_mode.effect);

	/*光照模式*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*饱和度*/
	OV7725_Color_Saturation(cam_mode.saturation); 
	/*光照度*/
	OV7725_Brightness(cam_mode.brightness); 
	/*对比度*/
	OV7725_Contrast(cam_mode.contrast); 
	/*特殊效果*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*设置图像采样及模式大小*/
	OV7725_Window_Set(cam_mode.cam_sx,
				      cam_mode.cam_sy,
					  cam_mode.cam_width,
					  cam_mode.cam_height,
					  cam_mode.QVGA_VGA);

    OV7725_CS=0;
    MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff, SEND_BUF_SIZE);
    Ov7725_vsync = 0;        //帧同步信号标志
    delay_ms(5000);
    while (1){	
        delay_ms(1000);
        printf("AT+0x0123");

        if(Ov7725_vsync == 2){
            read_camara_fifo();
            Ov7725_vsync = 0;
            delay_ms(500);
            USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//使能串口1的DMA发送
            MYDMA_Enable(DMA1_Channel4); //开始一次 DMA 传输！
            while(1){
                if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET){ 
                    //判断传输完成
                    DMA_ClearFlag(DMA1_FLAG_TC4); //清除通道 4 传输完成标志
                    break;
                } 
            } 
  
        }
    }
}



/*************************************** END OF FILE *************************************/
