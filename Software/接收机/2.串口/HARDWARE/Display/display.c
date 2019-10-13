#include "display.h"
#include "oled.h"
#include "key.h"
#include "stdbool.h"

extern int Motor1,Motor2,Motor5;
extern signed short int Pitch,Roll,Yaw;
extern bool light_flag;
extern u8 key_v;
extern u8 rec_data;
u8 display_page=0;
//enum key_up
//{
//	key_up_1=1,key_up_2,key_up_3,key_up_4
//};
u8 up_dowm=1;
u8 left_right=1;

extern bool start_flag;//true 1  false 0
extern bool mode_flag,recvice_flag;
extern bool stop_flag;
extern bool motor_flag;

void Page1(void)
{
//	OLED_Clear();

	
	OLED_ShowString1(50,0,"Giao");
	
	OLED_ShowCHinese1(30,2,0);
	OLED_ShowCHinese1(46,2,1);
	OLED_ShowCHinese1(63,2,2);
	OLED_ShowCHinese1(80,2,3);
	
	OLED_ShowCHinese1(15,4,4);
	OLED_ShowCHinese1(35,4,5);
	OLED_ShowCHinese1(80,4,6);
	OLED_ShowCHinese1(100,4,7);
	
	OLED_ShowCHinese1(15,6,8);
	OLED_ShowCHinese1(35,6,9);
	OLED_ShowCHinese1(80,6,10);
	OLED_ShowCHinese1(100,6,11);
	

}

void Page2(void)
{	
	
 	 OLED_ShowCHinese1(0,0,13);
 	 OLED_ShowCHinese1(16,0,14);
 	 OLED_ShowCHinese1(32,0,15);
 	 OLED_ShowCHinese1(48,0,16);
 	 OLED_ShowCHinese1(64,0,17);
 	 OLED_ShowCHinese1(80,0,18);
 	 OLED_ShowCHinese1(96,0,19);
 	 OLED_ShowCHinese1(112,0,20);
	
	 OLED_ShowString1(10,2,"Light->");
	 OLED_ShowString1(10,4,"Motor->");
	 OLED_ShowString1(10,6,"Speed->");
	 Dis_Num(6,12,Motor5,3);
		if(light_flag==true)
			OLED_ShowString1(90,2,"on ");
		else OLED_ShowString1(90,2,"off");
	if(motor_flag==true)
				OLED_ShowString1(90,4,"on ");
		else OLED_ShowString1(90,4,"off");
}



void display()
{
	
	key_v=KEY_Scan(0);
	if(key_v==KEY_MID_PRES||rec_data=='c') 
	{
		display_page+=1;
		OLED_Clear();	
	}
	display_page=display_page>5?0:display_page;
	
	if(key_v==KEY_UP_PRES) up_dowm+=1;
	up_dowm=up_dowm>4?1:up_dowm;
	
	if(key_v==KEY_DOWM_PRES) up_dowm-=1;
	up_dowm=up_dowm<1?4:up_dowm;
	
	
	
	switch(display_page)
	{
		case 1:	
		{
			OLED_Clear();	
			Page1();
			break;
		}
		case 2:
		{
		  OLED_Clear();
			Page2();
			
			switch(up_dowm)
			{
				case 1:
				{
//					OLED_ShowString1(0,0,"*");
					break;
				}
				case 2:
				{
					OLED_ShowString1(0,0,"*");
					break;
				}
			}
			break;
		}
		case 4:
		{
		  OLED_Clear();
			break;
		}
		default:  break;
	}
}




