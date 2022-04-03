#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
void Lcd_cmd(char c)
{
	PORTD=c&0xf0;
	PORTD&=~0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	_delay_ms(5);
	PORTD&=~0x04;
	_delay_ms(5);

	PORTD=c<<4;          //d4 se d7
	PORTD&=~0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	_delay_ms(5);
	PORTD&=~0x04;
	_delay_ms(5);

}
void Lcd_data(char d)
{
	PORTD=d&0xf0;
	PORTD|=0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	_delay_ms(5);
	PORTD&=~0x04;
	_delay_ms(5);

	PORTD=d<<4;
	PORTD|=0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	_delay_ms(5);
	PORTD&=~0x04;
	_delay_ms(5);


}
void Lcd_initial()
{
	Lcd_cmd(0x02);
	Lcd_cmd(0x28);
	Lcd_cmd(0x0c);
	Lcd_cmd(0x06);
	Lcd_cmd(0x01);
	Lcd_cmd(0x80);
}
void Lcd_string(char*ptr)
{
	while (*ptr!='\0')
	{
		Lcd_data(*ptr++);
	}
}


char i2c_read()
{
	char d;
	TWCR=0xc4;
	while((TWCR&(0x80))==0)
	d=TWDR;
	return(d);
}
void i2c_address()
{
	char d;
	TWCR=0xC4;
	while((TWCR&(0x80))==0);
	d=TWDR;
}
int main(void)
{
	int i;
	DDRD=0xff;
	char data;
	Lcd_initial();
	TWAR=0x20;
	TWCR=0x04;
	Lcd_data('s');
	_delay_ms(1000);
	while(1)
	{
		i2c_address();
		Lcd_data('s');
		_delay_ms(25);
		Lcd_cmd(0x01);
		
		for(i=0; i<20; i++)
		{
			data=i2c_read();
			Lcd_data(data);
		}
		_delay_ms(2000);
	}
}

