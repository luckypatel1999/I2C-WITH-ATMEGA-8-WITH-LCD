/*
 * i2c_tx_atmega16_.c
 *
 * Created: 18-02-2022 10:01:19
 *  Author: DELL
 */
#define F_CPU 3000000UL
#include <avr/io.h>
#include <util/delay.h>

void i2c_init()
{
	TWBR=0xff;
}
void i2c_start()
{
	char d;
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}
void i2c_TX(char ch)
{
	TWDR=ch;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}
void i2c_stop()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
int main(void)
{

	int i;
	char a[20]="LUCKY PATEL";
	char b[20]="ABHISHEK";
	i2c_init();
	_delay_ms(1000);
	while(1)
	{
		i2c_start();
		_delay_ms(20);

		i2c_TX(0x20);
		_delay_ms(20);

		for(i=0; i<20; i++)
		{
			i2c_TX(a[i]);
			_delay_ms(2);
		}
		_delay_ms(20);
		i2c_stop();
		_delay_ms(2000);
		
       i2c_start();
       _delay_ms(20);

       i2c_TX(0x40);
       _delay_ms(20);

       for(i=0; i<20; i++)
       {
	       i2c_TX(b[i]);
	       _delay_ms(2);
       }
       _delay_ms(20);
       i2c_stop();
       _delay_ms(2000);
	}
	
}
