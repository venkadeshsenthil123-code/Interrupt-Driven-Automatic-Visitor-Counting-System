typedef unsigned int U32;

void delay_seconds(U32 seconds)
{
	T0PR = 15000000-1; 
	T0TCR = 0X01;
	while(T0TC<seconds);
	T0TCR = 0X03;  
	T0TCR = 0x00;
}

void delay_milliseconds(U32 ms)
{
	T0PR = 15000-1; 
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03; 
	T0TCR = 0x00;
}

void delay_microseconds(U32 microseconds)
{
	T0PR = 15-1; 
	T0TCR = 0X01;
	while(T0TC<microseconds);
	T0TCR = 0X03;	
	T0TCR = 0x00;
}
