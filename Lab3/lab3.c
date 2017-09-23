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

uint32_t flashCount = 0;

typedef struct State
{
	uint32_t out;
	uint32_t time;
	uint32_t next[4];
} State;

State FSM[7] = {
	{0b100001, 100, {goE, goE, flashOnE, flashOnE}},
	{0b100010, 200, {flashOffE, goN, flashOffE, goN}},
	{0b100000, 200, {flashOnE, flashOnE, flashOnE, flashOnE}},
	{0b001100, 10000, {flashOnN, flashOnN, flashOnN, flashOnN}},
	{0b010100, 500, {flashOffN, waitButton, flashOffN, waitButton}},
	{0b000100, 500, {flashOnN, flashOnN, flashOnN, flashOnN}},
	{0b100001, 30000, {goE, goE, goE, goE}},
};

int main()
{
	if(wiringPiSetup() == -1){
		exit(1);
	}
	int currState;
	int externalButtonValue;
	uint32_t inputs = 0;
	
	// Initialize ports and timer
	pinMode(3, INPUT);
	pinMode(11, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(29, OUTPUT);
	pinMode(31, OUTPUT);
	pinMode(33, OUTPUT);
	
	currState = goE;
	digitalWrite(11, ((FSM[currState].out & 32) / 32));
	digitalWrite(13, ((FSM[currState].out & 16) / 16));
	digitalWrite(15, ((FSM[currState].out & 8) / 8));
	digitalWrite(29, ((FSM[currState].out & 4) / 4));
	digitalWrite(31, ((FSM[currState].out & 2) / 2));
	digitalWrite(33, ((FSM[currState].out & 1) / 1));
	printf("Pin11: %d\n", ((FSM[currState].out & 32) / 32));
	printf("Pin13: %d\n", ((FSM[currState].out & 16) / 16));
	printf("Pin15: %d\n", ((FSM[currState].out & 8) / 8));
	printf("Pin29: %d\n", ((FSM[currState].out & 4) / 4));
	printf("Pin31: %d\n", ((FSM[currState].out & 2) / 2));
	printf("Pin33: %d\n", ((FSM[currState].out & 1) / 1));
	printf("Hello2\n");
	while (1)
	{
		//delay(FSM[currState].time);
		
	// 	if (currState == flashOffE || currState == flashOffN)
	// 	{
	// 		flashCount++;
	// 	}
		
	// 	externalButtonValue = digitalRead(3);
	// 	if (externalButtonValue)
	// 	{
	// 		inputs += 1;
	// 	}
	// 	if (flashCount == 10)
	// 	{
	// 		inputs += 2;
	// 		flashCount = 0;
	// 	}
		
	// 	if (currState != FSM[currState].next[inputs])
	// 	{
	// 		digitalWrite(11, ((FSM[currState].out & 32) / 32));
	// 		digitalWrite(13, ((FSM[currState].out & 16) / 16));
	// 		digitalWrite(15, ((FSM[currState].out & 8) / 8));
	// 		digitalWrite(29, ((FSM[currState].out & 4) / 4));
	// 		digitalWrite(31, ((FSM[currState].out & 2) / 2));
	// 		digitalWrite(33, ((FSM[currState].out & 1) / 1));
	// 	}
	// 	currState = FSM[currState].next[inputs];
	}
}