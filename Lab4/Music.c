#include <wiringPi.h>
#include <stdio.h>
#define outputPin 7
// #define period 1000 //1 second
#define a 440
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391

void tone (unsigned int frequency, unsigned int period){ //Frequency = note, period = duration
	long half_cycle = (long)(1000000/frequency);
	long duration = (long)((period*1000 )/(half_cycle*2));
	for (int i = 0 ; i < duration; i++){
		digitalWrite(outputPin, HIGH);
		delayMicroseconds(half_cycle);
		digitalWrite(outputPin, LOW);
		delayMicroseconds(half_cycle);
	}

	digitalWrite(outputPin, LOW);
	delay(20);
}

void run (){
	tone(g, 750);
	tone(a, 250);
	tone(g, 500);
	tone(f, 500);
	tone(e, 500);
	tone(f, 500);
	tone(g, 1000);
	tone(d, 500);
	tone(e, 500);
	tone(f, 1000);
	tone(e, 500);
	tone(f, 500);
	tone(g, 1000);
	tone(g, 750);
	tone(a, 250);
	tone(g, 500);
	tone(f, 500);
	tone(e, 500);
	tone(f, 500);
	tone(g, 1000);
	tone(d,1000);
	tone(g,1000);
	tone(e,1000);
	tone(c,1000);

	delay(500);
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