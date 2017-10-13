import time
import math
import RPi.GPIO as IO
# Import the MCP4725 module.
import Adafruit_MCP4725

# Create a DAC instance.
dac = Adafruit_MCP4725.MCP4725()

IO.setmode(IO.BOARD)
IO.setup(15, IO.IN) #Setup input from button


def sin_wave(volt_input, freq_input):
	t = 0.0
	tStep = 0.0005
	scale = 4096/3.3
	# for i in range (0, 40000):
	while True:
		voltage = scale * ((volt_input - 1) + math.sin(freq_input*t*(50/3.0)))
		dac.set_voltage(int(voltage))
		t += tStep
		time.sleep(0.0005)

def square_wave(volt_input, freq_input):
	# for i in range (0, freq_input*20):
	while True:
		voltage = volt_input * (4096/3.3)
		dac.set_voltage(int(voltage))
		time.sleep((1.0/freq_input)/2.0)
		voltage = 0
		dac.set_voltage(int(voltage))
		time.sleep((1.0/freq_input)/2.0)

def triangle_wave(volt_input, freq_input):
	tStep = 0.005
	scale = volt_input*(4096 / 3.3)
	slope = 2*volt_input*freq_input*(10/8.4)

	while True:
		voltage = 0
		while voltage<volt_input:
			voltage += slope * tStep
			dac.set_voltage(int(voltage*(4096/3.3)))
			time.sleep(0.005)
		while voltage >= 0:
			voltage -= slope * tStep
			dac.set_voltage(int(voltage*(4096/3.3)))
			time.sleep(0.005)
while True:
	if(IO.input(15)):
		shape_input = input("Shape of Waveform: ")
		volt_input = input("Max output voltage: ")
		freq_input = input("Frequency: ")

		if (shape_input == 'sin'):
			sin_wave(volt_input, freq_input)
		elif (shape_input == 'triangle'):
			triangle_wave(volt_input, freq_input)
		elif (shape_input == 'square'):
			square_wave(volt_input, freq_input)
		else:
			print "Wrong shape input"

	#print "Max entered:", volt_input
