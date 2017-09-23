#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
	int pin = 13;
	if (wiringPiSetup() == -1) {
		exit (1);
	}
	pinMode(pin, OUTPUT);
	int i;
	for ( i=0; i<10; i++ ) {
		digitalWrite(pin, 1);
		delay(200);
		digitalWrite(pin, 0);
		delay(200);
	}
	return 0;
}