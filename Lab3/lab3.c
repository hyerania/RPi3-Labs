#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>

#define INPUT  0
#define OUTPUT 1

#define goE        0
#define flashOnE   1
#define flashOffE  2
#define goNdigitR  3
#define goNdigitL  4
#define flashOnN   5
#define flashOffN  6
#define waitButton 7

double counter = 0.00; // Used for flashing the LED's and segment display the appropriate amount of times

typedef struct State
{
	uint32_t out[6];
	uint32_t time;
	uint32_t next[4];
} State;

State FSM[8] = {
	{{1, 0, 0, 0, 0, 1}, 100, {goE, goE, flashOnE, flashOnE}},
	{{1, 0, 0, 0, 1, 0}, 200, {flashOffE, goNdigitR, flashOffE, goNdigitR}},
	{{1, 0, 0, 0, 0, 0}, 200, {flashOnE, flashOnE, flashOnE, flashOnE}},
	{{0, 0, 1, 1, 0, 0}, 5, {goNdigitL, flashOnN, goNdigitL, flashOnN}},
	{{0, 0, 1, 1, 0, 0}, 5, {goNdigitR, goNdigitR, goNdigitR, goNdigitR}},
	{{0, 1, 0, 1, 0, 0}, 500, {flashOffN, waitButton, flashOffN, waitButton}},
	{{0, 0, 0, 1, 0, 0}, 500, {flashOnN, flashOnN, flashOnN, flashOnN}},
	{{1, 0, 0, 0, 0, 1}, 30000, {goE, goE, goE, goE}},
};

void rightDigit(double time) // Prints the right digit on the dual 14-segment display
{
	digitalWrite(40, 1); // Adjust the ground pins appropriately
	digitalWrite(12, 0);

	if (time >= 9 && time < 10) // Print the number
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
	else if (time >= 8 && time < 9)
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
	else if (time >= 7 && time < 8)
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
	else if (time >= 6 && time < 7)
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
	else if (time >= 5 && time < 6)
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
	else if (time >= 4 && time < 5)
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
	else if (time >= 3 && time < 4)
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
	else if (time >= 2 && time < 3)
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
	else if (time >= 1 && time < 2)
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
	else if (time >= 0 && time < 1)
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

void leftDigit(double time) // Prints the left digit on the dual 14-segment display
{
	if (time >= 10 && time < 20)
	{
		digitalWrite(12, 1);
		digitalWrite(40, 0);

		// Left side digit 1
		digitalWrite(35, 0);
		digitalWrite(37, 0);
		digitalWrite(38, 1);
		digitalWrite(32, 1);
		digitalWrite(22, 0);
		digitalWrite(7, 0);
		digitalWrite(36, 0);
		digitalWrite(18, 0);
	}
	else if (time < 10)
	{
		// No digit on left side
		digitalWrite(12, 0);
		digitalWrite(40, 1);
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
	
	pinMode(35, OUTPUT); //Top left
	pinMode(37, OUTPUT); //Top
	pinMode(38, OUTPUT); //Top right
	pinMode(32, OUTPUT); //Bottom right
	pinMode(22, OUTPUT); //Bottom
	pinMode(7, OUTPUT);	 //Bottom left
	pinMode(36, OUTPUT); //Middle left
	pinMode(18, OUTPUT); //Middle right

	pinMode(40, OUTPUT); //Ground for Left Digit
	pinMode(12, OUTPUT); //Ground for Right Digit
	
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

	delay(1000); // Shut both pins off for a second to recognize program reset
	currState = goE; // Initial state
	while (1)
	{
		// Light up the LED's correspondent to the current state
		digitalWrite(11, FSM[currState].out[0]);
		digitalWrite(13, FSM[currState].out[1]);
		digitalWrite(15, FSM[currState].out[2]);
		digitalWrite(29, FSM[currState].out[3]);
		digitalWrite(31, FSM[currState].out[4]);
		digitalWrite(33, FSM[currState].out[5]);

		// Print the remaining time on the 14-segment display if necessary
		if (currState == goNdigitR)
		{
			rightDigit(10 - counter);
			counter += 0.01;
		}
		else if (currState == goNdigitL)
		{
			leftDigit(20 - counter);
		}
		else if (currState == flashOnN)
		{
			rightDigit(9 - counter);
			counter += 1;
		}

		// Wait for how long the state is supposed to delay for
		delay(FSM[currState].time);
		
		// Turn off segment display when the time is up
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

		// Increment the flash count when the traffic light is flashing
		if (currState == flashOnE)
		{
			counter++;
		}

		// Use the inputs to determine which state to go to next
		inputs = 0;
		externalButtonValue = digitalRead(16);
		if (externalButtonValue)
		{
			inputs += 2;
		}
		if (counter >= 10) // The counter will always be at 10 when it's ready to go to a new state
		{
			inputs += 1;
			counter = 0;
		}

		// Go to the next state (it might loop back to the same state)
		currState = FSM[currState].next[inputs];
	}
}