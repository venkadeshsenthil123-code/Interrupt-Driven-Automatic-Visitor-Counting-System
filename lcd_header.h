#include<lpc21xx.h>
#include "delay.h"
#define LCD_D 0XF<<27
#define RS    1<<18
#define E     1<<19

void lcd_init(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_str( char *s);
void lcd_integer(int num);


void lcd_init(void)
{
	IODIR1=LCD_D|RS|E;
	lcd_command(0X01);
	lcd_command(0X02);
	lcd_command(0X0c);
	lcd_command(0X28);
	lcd_command(0X80);
}
void lcd_command(unsigned char CMD)
{
	IOCLR1=LCD_D;
	IOSET1=(CMD&0XF0)<<23;
	IOCLR1=RS;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=(CMD&0X0F)<<27;
	IOCLR1=RS;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;
}
void lcd_data(unsigned char dataByte)
{
	IOCLR1=LCD_D;
	IOSET1=(dataByte&0XF0)<<23;
	IOSET1=RS;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=(dataByte&0X0F)<<27;
	IOSET1=RS;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;
}

void lcd_str( char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}

void lcd_integer(int num)
{
	unsigned char arr[5];
	signed char i=0;
	if(num==0)
	{
		lcd_data('0');
	}
	else
	{
		if(num<0)
		{
			lcd_data('-');
			num=-num;
		}
		while(num>0)
		{
			arr[i++]=num%10;
			num=num/10;
		}
		for(--i;i>=0;--i)
			lcd_data(arr[i]+48);
	}
}




