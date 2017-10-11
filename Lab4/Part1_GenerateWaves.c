#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>

void SquareWave(){
	// 0.1 MHz
	while(1){
		digitalWrite(Pin, 1);
		delayMicroseconds(5);
		digitalWrite(Pin, 0);
		delayMicroseconds(5);
	}
	// 200 MHz
	// while(1){
	// 	digitalWrite(Pin, 1);
	// 	delayMicroseconds(0.0025);
	// 	digitalWrite(Pin, 0);
	// 	delayMicroseconds(0.0025);
	// }
	// 600 MHz
	// while(1){
	// 	digitalWrite(Pin, 1);
	// 	delayMicroseconds(0.000833);
	// 	digitalWrite(Pin, 0);
	// 	delayMicroseconds(0.000833);
	// }
	// 800 MHz
	// while(1){
	// 	digitalWrite(Pin, 1);
	// 	delayMicroseconds(0.000625);
	// 	digitalWrite(Pin, 0);
	// 	delayMicroseconds(0.000625);
	// }
}

// void TriangularWave(){

// }

int main(){
	if(wiringPiSetupPhys() == -1){
		exit(1);
	}
	SquareWave();
	
}