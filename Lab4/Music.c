#include <wiringPi.h>
#include <stdio.h>
#define outputPin 7
#define C4 261
#define period 1000 //1 second

void tone (){
	long half_cycle = ( long )( 1000000 /C4);
	long duration = ( long )((period* 1000 )/(half_cycle* 2 ));
	for ( int i = 0 ; i < duration; i++){
		digitalWrite(outputPin, HIGH);
		delayMicroseconds(half_cycle);
		digitalWrite(outputPin, LOW);
		delayMicroseconds(half_cycle);
	}
}

void run (){
	tone();
	digitalWrite(outputPin, LOW);
	delay(20);
}

int main (){
	if (wiringPiSetupPhys() == -1 ){
	return 1;
}

	pinMode(outputPin, OUTPUT);
	while (1){
		run();
	}
}