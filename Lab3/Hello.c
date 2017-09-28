#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(void){
	int red = 11;
	int green = 13;
	int blue = 15;

	if(wiringPiSetupPhys() == -1){
		exit(1);
	}

	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	for(;;){
		digitalWrite(red, 1);
		delay(200);
		digitalWrite(red, 0);
		delay(500);
		digitalWrite(green, 1);
		delay(200);
		digitalWrite(green, 0);
		delay(500);
		digitalWrite(blue, 1);
		delay(200);
		digitalWrite(blue, 0);
	}
	
	return 0;
}