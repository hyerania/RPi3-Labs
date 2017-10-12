import time
import math
# Import the MCP4725 module.
import Adafruit_MCP4725

# Create a DAC instance.
dac = Adafruit_MCP4725.MCP4725()

def square_wave():
	t = 1
	while True:
		voltage = 2048
		dac.set_voltage(int(voltage))
		time.sleep(t/2)
		voltage = 0
		dac.set_voltage(int(voltage))
		time.sleep(t/2)

square_wave()

# t = 1/freq_input #Period
# voltage = volt_input
#...
# time.sleep(t/2)
