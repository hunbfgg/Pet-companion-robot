#include "bigiot.h"
#include "common.h"
#include "text.h"

char receive_data[100];

#define Ganyin1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��Ӧģ��1
#define Ganyin2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��Ӧģ��2
u8 cishu=0;

void bigiot_set()
{
	while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���   u3_printf("%s\r\n",cmd);	//��������
	
	while(atk_8266_send_cmd("AT+CWMODE_CUR=1","OK",20));     //��Ϊ�ͻ���ģʽ
	
	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"CMCC-biR5\",\"ywrg3nbu\"","OK",20));  //����WIFI
//	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"OPPO R15\",\"12345678\"","OK",20));  //����WIFI
	Show_Str(40,55,200,16,"WIFI���ӳɹ�",16,0);
	while(atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"www.bigiot.net\",8181","OK",20));  //TCP����www.bigiot.net
	
	delay_ms (1000);
	Show_Str(40,55,200,16," TCP���ӳɹ�",16,0);
	while(atk_8266_send_cmd("AT+CIPMODE=1","OK",20));  //��͸��ģʽ
	
	delay_ms (1000);
	
	while(atk_8266_send_cmd("AT+CIPSEND",">",20));  //��ʼ��������
	Show_Str(40,55,200,16,"��ʼ��������",16,0);
	delay_ms (1000);
	
	u3_printf("%s\n","{\"M\":\"checkin\",\"ID\":\"16782\",\"K\":\"e93349644\"}");   //�豸��¼
	delay_ms (1000);
	while(1)
	{
		u3_printf("%s\n","{\"M\":\"update\",\"ID\":\"16782\",\"V\":{\"15033\":\"1\"}}");   //ÿ��50s���ڷ�������,������������
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




