/* AUTOMATIC VISITOR COUNTING OPERATING SYSTEM */

#include <lpc21xx.h>
#include "lcd_header.h"

#define EINT0   (1 << 0)
#define EINT1   (1 << 29)
#define LED     (1 << 10)
#define BUZZER  (1 << 11)
#define SWITCH  17

volatile unsigned int lcd_count = 0, total_entry = 0, total_exit = 0;
volatile unsigned int flag1 = 0, flag2 = 0;

void entry_person(void) __irq // FOR ENTRY
{
	IOCLR0 = LED;
	flag1 = 1;
	EXTINT = 0x01;
	VICVectAddr = 0;
}

void exit_person(void) __irq // FOR EXIT
{
	flag2 = 1;
	EXTINT = 0x02;
	VICVectAddr = 0;
}

void update_display(void) // DISPLAY FUNCTION
{
	lcd_command(0x01); 
	if (lcd_count == 0)
       	{
		lcd_command(0x84);
		lcd_str("NO VISITOR");
		IOSET0 = LED;
	}
       	else 
	{
		lcd_command(0x80);
		lcd_str(lcd_count == 1 ? "VISITOR:" : "VISITORS:");
		lcd_command(lcd_count == 1 ? 0x89 : 0x8A);
		lcd_integer(lcd_count);
                IOCLR0 = LED;
	}
}

void trigger_buzzer(void) // FOR BUZZER
{
	IOCLR0 = BUZZER;
	delay_seconds(1);
	IOSET0 = BUZZER;
	delay_seconds(1);
}

int main() 
{
	PINSEL0 |= EINT1;
	PINSEL1 |= EINT0;
	IODIR0 = LED | BUZZER;
	lcd_init();

	VICIntSelect = 0;
	VICVectCntl0 = (1 << 5) | 14;
	VICVectAddr0 = (unsigned long)entry_person;

	VICVectCntl1 = (1 << 5) | 15;
	VICVectAddr1 = (unsigned long)exit_person;
	
	EXTMODE = 0x00;
	EXTPOLAR = 0x00;

	lcd_command(0x81);  lcd_str("AUTOMATIC VISITOR");
	lcd_command(0xC2);  lcd_str("COUNTING SYSTEM");
	delay_seconds(2);

	EXTINT = 0x03;
	IOSET0 = BUZZER | LED; 
	VICIntEnable = (1 << 14) | (1 << 15);    

	update_display(); 

	while (1) {
		if (flag1) //ENTRY
		{  
			lcd_count++;
			total_entry++;
			update_display();
			trigger_buzzer();
			flag1 = 0;
		} 
		else if (flag2) //EXIT
		{ 
			if (lcd_count > 0) 
				lcd_count--;
			total_exit++;
			update_display();
			trigger_buzzer();
			flag2 = 0;
		} 
		else if (((IOPIN1 >> SWITCH) & 1) == 0)
		{ 
			delay_milliseconds(500); // Debounce
			lcd_command(0x01);
			lcd_command(0x82);  lcd_str("TOTAL ENTERED:");
			lcd_command(0x91);  lcd_integer(total_entry);
			lcd_command(0xC2);  lcd_str("TOTAL EXITED:");
			lcd_command(0xD1);  lcd_integer(total_exit);


			while(((IOPIN1 >> SWITCH) & 1) == 0);
			update_display();
		}
	}
}
