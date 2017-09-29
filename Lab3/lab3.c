#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>

#define INPUT  0
#define OUTPUT 1

#define goE        0
#define flashOnE   1
#define flashOffE  2
#define goN        3
#define flashOnN   4
#define flashOffN  5
#define waitButton 6
#define NVIC_ST_CTRL_R 0xE000E010
#define NVIC_ST_RELOAD_R 0xE000E014
#define NVIC_ST_CURRENT_R 0xE000E018

uint32_t counter = 0;

typedef struct State
{
	uint32_t out[6];
	uint32_t time;
	uint32_t next[4];
} State;

State FSM[7] = {
	{{1, 0, 0, 0, 0, 1}, 100, {goE, goE, flashOnE, flashOnE}},
	{{1, 0, 0, 0, 1, 0}, 200, {flashOffE, goN, flashOffE, goN}},
	{{1, 0, 0, 0, 0, 0}, 200, {flashOnE, flashOnE, flashOnE, flashOnE}},
	{{0, 0, 1, 1, 0, 0}, 1000, {goN, flashOnN, goN, flashOnN}},
	{{0, 1, 0, 1, 0, 0}, 500, {flashOffN, waitButton, flashOffN, waitButton}},
	{{0, 0, 0, 1, 0, 0}, 500, {flashOnN, flashOnN, flashOnN, flashOnN}},
	{{1, 0, 0, 0, 0, 1}, 30000, {goE, goE, goE, goE}},
};

void clockWrite(int time){
	if (time == 20)
	{
		digitalWrite(40, 0);
	}
	else if (time >= 10 && time < 20)
	{
		digitalWrite(40, 0);
	}
	else if (time < 10)
	{
		digitalWrite(40, 1);
	}

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
int main()
{
	if(wiringPiSetupPhys() == -1){
		exit(1);
	}
	int currState;
	int externalButtonValue;
	uint32_t inputs = 0;
	
	// Initialize ports and timer
	pinMode(16, INPUT);  //Button
	pinMode(11, OUTPUT); //Red
	pinMode(13, OUTPUT); //Blue
	pinMode(15, OUTPUT); //Green
	pinMode(29, OUTPUT); //Red
	pinMode(31, OUTPUT); //Blue
	pinMode(33, OUTPUT); //Green
	
	pinMode(35, OUTPUT);	//Top left
	pinMode(37, OUTPUT);	//Top
	pinMode(38, OUTPUT);	//Top right
	pinMode(32, OUTPUT);	//Bottom right
	pinMode(22, OUTPUT);	//Bottom
	pinMode(7, OUTPUT);		//Bottom left
	pinMode(36, OUTPUT);	//Middle left
	pinMode(18, OUTPUT);	//Middle right
	
	digitalWrite(11, 0);
	digitalWrite(13, 0);
	digitalWrite(15, 0);
	digitalWrite(29, 0);
	digitalWrite(31, 0);
	digitalWrite(33, 0);

	digitalWrite(35, 0);
	digitalWrite(37, 0);
	digitalWrite(38, 0);
	digitalWrite(32, 0);
	digitalWrite(22, 0);
	digitalWrite(7, 0);
	digitalWrite(36, 0);
	digitalWrite(18, 0);

	delay(1000);
	currState = goE;
	while (1)
	{
		printf("\n\nPin11: %d\n", FSM[currState].out[0]);
		printf("Pin13: %d\n", FSM[currState].out[1]);
		printf("Pin15: %d\n", FSM[currState].out[2]);
		printf("Pin29: %d\n", FSM[currState].out[3]);
		printf("Pin31: %d\n", FSM[currState].out[4]);
		printf("Pin33: %d\n", FSM[currState].out[5]);
		digitalWrite(11, FSM[currState].out[0]);
		digitalWrite(13, FSM[currState].out[1]);
		digitalWrite(15, FSM[currState].out[2]);
		digitalWrite(29, FSM[currState].out[3]);
		digitalWrite(31, FSM[currState].out[4]);
		digitalWrite(33, FSM[currState].out[5]);

		if (currState == goN)
		{
			clockWrite(20 - counter);
			counter++;
		}
		if (currState == flashOnN)
		{
			clockWrite(10 - counter);
			counter++;
		}

		delay(FSM[currState].time);
		
		if(currState == flashOnN && counter == 10)
		{
			digitalWrite(35, 0);
			digitalWrite(37, 0);
			digitalWrite(38, 0);
			digitalWrite(32, 0);
			digitalWrite(22, 0);
			digitalWrite(7, 0);
			digitalWrite(36, 0);
			digitalWrite(18, 0);			
		}
		if (currState == flashOnE)
		{
			counter++;
		}
		printf("counter: %d\n", counter);

		inputs = 0;
		externalButtonValue = digitalRead(16);
		printf("Button: %d\n", externalButtonValue);
		if (externalButtonValue)
		{
			inputs += 2;
		}
		if (counter == 10)
		{
			inputs += 1;
			counter = 0;
		}

		printf("inputs: %d\n", inputs);
		currState = FSM[currState].next[inputs];
	}
}