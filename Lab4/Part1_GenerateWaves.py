# -*- coding: utf8 -*-
import RPi.GPIO as IO  #calling for header file which helps in using GPIO’s of PI
import time 
IO.setwarnings(False)  #do not show any warnings

IO.setmode(IO.BOARD)
IO.setup(7, IO.OUT)

def SquareWave():
	while 1:
		IO.output(7,1)
		time.sleep(0.0000005)
		IO.output(7,0)
		time.sleep(0.0000005)
	# # 200 MHz
	# 	while 1:
	# 		IO.output(7,1)
	# 		time.sleep(0.0000000025)
	# 		IO.output(7,0)
	# 		time.sleep(0.0000000025)
	# # 600 MHz
	# 	while 1:
	# 		IO.output(7,1);
	# 		time.sleep(0.000000000833)
	# 		IO.output(7,0)
	# 		time.sleep(0.000000000833)
	# # 800 MHz
	# 	while 1:
	# 		IO.output(7,1)
	# 		time.sleep(0.000000000625)
	# 		IO.output(7,0)
	# 		time.sleep(0.000000000625)


SquareWave();
#Max it reached was 140k
