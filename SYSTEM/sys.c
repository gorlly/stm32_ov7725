#include "sys.h"
#include"../STM32F10x_FWLib/inc/misc.h"

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //设置 NVIC 中断分组 2:2 位抢占//优先级， 2 位响应优先级
}



