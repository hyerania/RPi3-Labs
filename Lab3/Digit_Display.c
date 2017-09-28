#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>

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

	
}