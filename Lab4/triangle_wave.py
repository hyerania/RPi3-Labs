import time
import math
# Import the MCP4725 module.
import Adafruit_MCP4725

# Create a DAC instance.
dac = Adafruit_MCP4725.MCP4725()

def triangle_wave():
	t = 1
	tStep = 0.05
	while True:
		#voltage = 2048*(1.0+0.5*math.sin(6.2832*t))
		for i in range (0, 10*t, 1):
			voltage = (2048/t) * (i*tStep)
			dac.set_voltage(int(voltage))
			time.sleep(0.0005)
		for i in range (10*t, 0, -1):
			voltage = (2048/t) * (i*tStep)
			dac.set_voltage(int(voltage))
			time.sleep(0.0005)

triangle_wave()