#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>

void rightDigit(int time){
	if (time % 10 == 9)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 0);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 8)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 1);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 7)
	{
		digitalWrite(35, 0);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 0);
		digitalWrite(18, 0);
	}
	else if (time % 10 == 6)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 1);
		digitalWrite(38, 0);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 1);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 5)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 1);
		digitalWrite(38, 0);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 0);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 4)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 0);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 3)
	{
		digitalWrite(35, 0);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 0);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 2)
	{
		digitalWrite(35, 0);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 0);
		digitalWrite(22, 1);
		digitalWrite(7, 1);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
	}
	else if (time % 10 == 1)
	{
		digitalWrite(35, 0);
		digitalWrite(37, 0);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 0);
		digitalWrite(18, 0);
	}
	else if (time % 10 == 0)
	{
		digitalWrite(35, 1);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 1);
		digitalWrite(7, 1);
		digitalWrite(36, 0);
		digitalWrite(18, 0);
	}
}

void clockWrite(int time)
{
	if (time >= 10 && time < 20)
	{
		digitalWrite(40, 1);
		digitalWrite(12, 0);
		delay(1);
		rightDigit(time);
		delay(1);
		digitalWrite(12, 1);
		digitalWrite(40, 0);
		
		//Number 1
		digitalWrite(35, 0);
		digitalWrite(37, 0);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 0);
		digitalWrite(18, 0);
		delay(0.5);
	}
	else if (time < 10)
	{
		digitalWrite(40, 1);
		digitalWrite(12, 0);
		rightDigit(time);
	}
}



int main(){
	if(wiringPiSetupPhys() == -1){
		exit(1);
	}

	pinMode(35, OUTPUT);	//Top left
	pinMode(37, OUTPUT);	//Top
	pinMode(38, OUTPUT);	//Top right
	pinMode(32, OUTPUT);	//Bottom right
	pinMode(22, OUTPUT);	//Bottom
	pinMode(7, OUTPUT);		//Bottom left
	pinMode(36, OUTPUT);	//Middle left
	pinMode(18, OUTPUT);	//Middle right

	pinMode(40, OUTPUT);	//Ground for Left Digit
	pinMode(12, OUTPUT);	//Ground for Right Digit

	while(1){
		digitalWrite(12, 1);
		digitalWrite(40, 0);

		//Number 2
		digitalWrite(35, 0);
		digitalWrite(37, 1);
		digitalWrite(38, 1);
		digitalWrite(32, 0);
		digitalWrite(22, 1);
		digitalWrite(7, 1);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
		delay(5);

		digitalWrite(40, 1);
		digitalWrite(12, 0);

		//Number 4
		digitalWrite(35, 1);
		digitalWrite(37, 0);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 1);
		digitalWrite(18, 1);
		delay(5);
	}
}