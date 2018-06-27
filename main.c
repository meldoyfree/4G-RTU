/******************************************************************************
* 这是STM32的RTC模块演示程序
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "RTC_Time.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTCClockOutput_Enable  /* RTC Clock/64 is output on tamper pin(PC.13) */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
time_t current_time;
struct tm time_now;

vu32 TimeDisplay;

/* Private function prototypes -----------------------------------------------*/
extern void Init_Device(void);
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
    time_t test_time_t;

    Init_Device();
    while(1)
    {
        if(TimeDisplay)
        {
            current_time = Time_GetUnixTime();
            time_now = Time_GetCalendarTime();

            USART_SendData(USART1, 0x0c);
            while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);

            printf("\r\nUNIX时间：%d", current_time);
            printf("\t当前时间：%d-%d-%d %d %02d:%02d:%02d\t", time_now.tm_year, \
                   time_now.tm_mon+1, time_now.tm_mday, time_now.tm_wday+1,\
                   time_now.tm_hour, time_now.tm_min, time_now.tm_sec);
            TimeDisplay = 0;
        }
        //测试项：按键按下后设置时间
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0)
		{
			time_now.tm_year = 2008;
			time_now.tm_mon = 11;
			time_now.tm_mday = 17;
			time_now.tm_hour = 19;
			time_now.tm_min = 8;
			time_now.tm_sec = 31;

			Time_SetCalendarTime(time_now);
		}
    }
    
}
