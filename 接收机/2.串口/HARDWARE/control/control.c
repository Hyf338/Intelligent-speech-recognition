#include "control.h"
#include "sys.h"
#include "timer.h"
#include "stdbool.h"
#include "key.h"
#include "oled.h"

/*
	pitch    short     						ԭʼ����
	Pitch    signed short int     ǿ��ת�����з���16λ
	pitch_L  short int        		�Ͱ�λ
*/

extern u8 receive_data[8];
extern char pitch_L,pitch_H,roll_L,roll_H,yaw_L,yaw_H;
extern signed short int Pitch,Roll,Yaw;
extern int Motor1,Motor2,Motor3,Motor4,Motor5;
extern bool start_flag;
extern bool mode_flag;
extern u8 rec_data;
extern u8 display_page;

bool recvice_flag=false;
bool stop_flag=false;
bool light_flag=false;
bool motor_flag=false;

short test=0;



void data_process(void)
{

	switch(rec_data)
	{
		case 'a'://����
		{
			OLED_Clear();
			
			OLED_ShowString1(0,2,"*");
			OLED_ShowString1(0,2,"*");
			light_flag=true;
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			break;
		}
		case 'b'://�ص�
		{
			OLED_Clear();
			OLED_ShowString1(0,2,"*");
			light_flag=false;
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			break;
		}
		case 'c'://��ҳ
		{
			OLED_Clear();
			display_page+=1;
			break;
		}
		case 'd'://�򿪵��
		{
			OLED_Clear();
			OLED_ShowString1(0,4,"*");
			motor_flag=true;
			break;
		}
		case 'e'://�رյ��
		{
			OLED_Clear();
			OLED_ShowString1(0,4,"*");
			motor_flag=false;
			Motor5=0;
			break;
		}
		case 'f'://����
		{
			OLED_Clear();
			OLED_ShowString1(0,6,"*");
			Motor5+=50;
			break;
		}
		case 'g'://����
		{
			OLED_Clear();
			OLED_ShowString1(0,6,"*");
			Motor5-=50;
			break;
		}
		case 'h': display_page=1;break;//����
		case 'i': display_page=4;break;//�ػ�
		
	}
	rec_data=0;
	
	
	TIM_SetCompare1(TIM1,0);
	TIM_SetCompare2(TIM1,Motor5);	
	TIM_SetCompare3(TIM1,800);
	TIM_SetCompare4(TIM1,Motor5);	
	
}




/*
	����   TIM1 ch1 ch2 ״̬
								+		0		ǰ��
								0		0		ֹͣ
								0		-		����
								
	����		TIM1 ch3 ch4 ״̬
								+		0		ֹͣ
								+	> +		ǰ��/��ԽС���ٶ�Խ��
								0		+		����	
	��ע��ͨ��4�·��Ƕ�ʱ����pwmģʽ��һ��
*/


void Infrared_mode(void)
{
	
	if(Infrared_rightmost==0&&Infrared_leftmost==0&&Infrared_right==0&&Infrared_left==0&&Infrared_mid==0)
	{
		stop_flag=true;
		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM1
		Motor1=200;
		Motor2=0;
		Motor3=800;
		Motor4=200;
	}
	
	else
	{
		stop_flag=false;
		if(Infrared_rightmost==1&&Infrared_leftmost==1&&Infrared_right==1&&Infrared_left==1)
		{
			Motor1=450;
			Motor2=0;
			Motor3=800;
			Motor4=400;
		}
		else if(Infrared_rightmost==1)
		{
			Motor1=500;
			Motor2=0;
			Motor3=0;
			Motor4=550;
		}
		else if(Infrared_leftmost==1)
		{
			Motor1=0;
			Motor2=400;
			Motor3=800;
			Motor4=450;
		}
		else if(Infrared_right==1)
		{
			Motor1=300;
			Motor2=0;
			Motor3=800;
			Motor4=200;
		}
		else if(Infrared_left==1)
		{
			Motor1=200;
			Motor2=0;
			Motor3=800;
			Motor4=350;
		}
		else if(Infrared_leftmost==0&&Infrared_left==0&&Infrared_mid==1&&Infrared_right==0&&Infrared_rightmost==0)
		{
			Motor1=350;
			Motor2=0;
			Motor3=800;
			Motor4=400;
		}
	}
}


void angle_mode(void)
{

	if(Pitch>0)
	{
		Motor1=20*Pitch;
		Motor2=0;
		Motor3=800;
		Motor4=15*Pitch;
	}
	else 
	{
		Motor1=0;
		Motor2=-20*Pitch;
		Motor3=800+15*Pitch;
		Motor4=0;
	}
	if(Roll>0)
	{
		Motor1+=15*Roll;
		Motor2=Motor2;
		
	}
	else
	{
		Motor4-=15*Roll;
	}
}


void run()
{
	if(start_flag == true)
	{
		if(mode_flag==false)
		{
			Infrared_mode();
		}
		if(mode_flag==true)
		{
			angle_mode();
		}
		if(recvice_flag==1)
		{
			mode_flag=false;
		}
	}
	if(start_flag==false)
	{
		Motor1=0;
		Motor2=0;
		Motor3=0;
		Motor4=800;
	}
	TIM_SetCompare1(TIM1,Motor1);
	TIM_SetCompare2(TIM1,Motor2);			 
	TIM_SetCompare3(TIM1,Motor3);		   
	TIM_SetCompare4(TIM1,Motor4);
}

