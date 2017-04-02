#ifndef _DMA_H_ 
#define _DMA_H_

#include "../STM32F10x_FWLib/inc/stm32f10x_dma.h"
#include "system_stm32f10x.h"

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);


#endif 




