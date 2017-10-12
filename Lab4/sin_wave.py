import time
import math
# Import the MCP4725 module.
import Adafruit_MCP4725

# Create a DAC instance.
dac = Adafruit_MCP4725.MCP4725()

def sin_wave():
	t = 0.0
	tStep = 0.05
	while True:
		voltage = 2048*(1.0+0.5*math.sin(6.2832*t))
		dac.set_voltage(int(voltage))
		t += tStep
		time.sleep(0.0005)

sin_wave()

# scale = volt_input*(4096 / 3.3)
# f = freq_input
# voltage = scale * (1.0+0.5*math.sin(f*t))