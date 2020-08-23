#include "bigiot.h"
#include "common.h"
#include "text.h"

char receive_data[100];

#define Ganyin1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//感应模块1
#define Ganyin2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//感应模块2
u8 cishu=0;

void bigiot_set()
{
	while(atk_8266_send_cmd("ATE0","OK",20));//关闭回显   u3_printf("%s\r\n",cmd);	//发送命令
	
	while(atk_8266_send_cmd("AT+CWMODE_CUR=1","OK",20));     //设为客户端模式
	
	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"CMCC-biR5\",\"ywrg3nbu\"","OK",20));  //连接WIFI
//	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"OPPO R15\",\"12345678\"","OK",20));  //连接WIFI
	Show_Str(40,55,200,16,"WIFI连接成功",16,0);
	while(atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"www.bigiot.net\",8181","OK",20));  //TCP连接www.bigiot.net
	
	delay_ms (1000);
	Show_Str(40,55,200,16," TCP连接成功",16,0);
	while(atk_8266_send_cmd("AT+CIPMODE=1","OK",20));  //打开透传模式
	
	delay_ms (1000);
	
	while(atk_8266_send_cmd("AT+CIPSEND",">",20));  //开始传输数据
	Show_Str(40,55,200,16,"开始传输数据",16,0);
	delay_ms (1000);
	
	u3_printf("%s\n","{\"M\":\"checkin\",\"ID\":\"16782\",\"K\":\"e93349644\"}");   //设备登录
	delay_ms (1000);
	while(1)
	{
		u3_printf("%s\n","{\"M\":\"update\",\"ID\":\"16782\",\"V\":{\"15033\":\"1\"}}");   //每隔50s以内发送数据,类似于心跳包
		if(strstr((const char*)receive_data ,(const char*)"play"))
		{
			printf("wrert\r\n");
			 GPIO_SetBits(GPIOE,GPIO_Pin_3);	
		 GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
				delay_ms (1000);
				delay_ms (1000);
				delay_ms (1000);
				delay_ms (1000);
				GPIO_ResetBits(GPIOE,GPIO_Pin_3);	
		 GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
				
		}
		else
		{
			printf("wreuiit\r\n");
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);	
		 GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
		}

		LED0=0;
		delay_ms (1000);
		LED0=1;
		delay_ms (1000);
		
		
	}
}




