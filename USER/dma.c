#include "dma.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN;


void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{ //data from memory to peripheral device
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
     DMA_DeInit(DMA_CHx);
     DMA1_MEM_LEN=cndtr;
     DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
     DMA_InitStructure.DMA_MemoryBaseAddr = cmar;
     
     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
     
     DMA_InitStructure.DMA_BufferSize = cndtr;

     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

     DMA_InitStructure.DMA_Mode =  DMA_Mode_Normal;
     DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
                    //中等优先级

     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
                            //关断内存到内存的传送
     DMA_Init(DMA_CHx, &DMA_InitStructure);
}

void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
    DMA_Cmd(DMA_CHx, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel4, DMA1_MEM_LEN);
    //DMA1 Channel 4: transform data to serial port  
    DMA_Cmd(DMA_CHx, ENABLE);  
}





