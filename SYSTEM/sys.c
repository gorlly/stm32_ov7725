#include "sys.h"
#include"../STM32F10x_FWLib/inc/misc.h"

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //���� NVIC �жϷ��� 2:2 λ��ռ//���ȼ��� 2 λ��Ӧ���ȼ�
}



