#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>
#include <unistd.h>

#define INPUT  0
#define OUTPUT 1

#define goE        0
#define flashOnE   1
#define flashOffE  2
#define goN        3
#define flashOnN   4
#define flashOffN  5
#define waitButton 6

int buttonValue = 0;
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
	printf("Display: %d\n\n", time);
}

int main()
{
	int currState;
	uint32_t inputs = 0;

	sleep(1);
	currState = goE;
	while (1)
	{
		printf("Current state: ");
		if (currState == 0)
		{
			printf("Go east\n");
		}
		else if (currState == 1)
		{
			printf("Flash on east\n");
		}
		else if (currState == 2)
		{
			printf("Flash off east\n");
		}
		else if (currState == 3)
		{
			printf("Go north\n");
		}
		else if (currState == 4)
		{
			printf("Flash on north\n");
		}
		else if (currState == 5)
		{
			printf("Flash off north\n");
		}
		else if (currState == 6)
		{
			printf("Wait for button\n");
		}

		printf("\nTraffic Light Red: %d\n", FSM[currState].out[0]);
		printf("Traffic Light Blue: %d\n", FSM[currState].out[1]);
		printf("Traffic Light Green: %d\n", FSM[currState].out[2]);
		printf("Pedestrian Light Red: %d\n", FSM[currState].out[3]);
		printf("Pedestrian Light Blue: %d\n", FSM[currState].out[4]);
		printf("Pedestrian Light Green: %d\n\n", FSM[currState].out[5]);
		printf("Counter: %d\n\n", counter);

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

		sleep(FSM[currState].time/1000);
		
		if (currState == flashOnE)
		{
			counter++;
		}

		inputs = 0;
		if (currState == goE) // Simulated button press
		{
			buttonValue = 1;
		}
		if (buttonValue)
		{
			inputs += 2;
		}
		if (currState == goE) // Simulated button release
		{
			buttonValue = 0;
		}

		if (counter == 10)
		{
			inputs += 1;
			counter = 0;
		}

		printf("Inputs: %d\n\n", inputs);
		printf("----------------------------------------------\n\n");
		currState = FSM[currState].next[inputs];
	}
}