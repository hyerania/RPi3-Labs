# -*- coding: utf8 -*-
import RPi.GPIO as IO  #calling for header file which helps in using GPIO’s of PI
import time 
IO.setwarnings(False)  #do not show any warnings

IO.setmode(IO.BOARD)
IO.setup(7, IO.OUT)

while 1:
	IO.output(7,1)
	IO.output(7,0)