# -*- coding: utf8 -*-
import RPi.GPIO as IO  #calling for header file which helps in using GPIO’s of PI
import time            #calling for time to provide delays in program
import binascii
IO.setwarnings(False)  #do not show any warnings

IO.setmode (IO.BCM)  #programming the GPIO by BCM pin numbers. (like PIN29 as'GPIO5')
IO.setup(2,IO.IN)  #initialize GPIO2 (PIN 3) as an output.
IO.setup(3,IO.IN)  #initialize GPIO3 (PIN 5) as an output.
IO.setup(4,IO.IN)
IO.setup(14,IO.IN)
IO.setup(15,IO.IN)
IO.setup(10,IO.IN)
IO.setup(9,IO.IN)
IO.setup(11,IO.IN)

while True:
	full_bits = ""
	dip_1 = IO.input(2)
	dip_2 = IO.input(3)
	dip_3 = IO.input(4)
	dip_4 = IO.input(14)
	dip_5 = IO.input(15)
	dip_6 = IO.input(10)
	dip_7 = IO.input(9)
	dip_8 = IO.input(11)
	#full_bits = full_bits + str(dip_1) + str(dip_2) + str(dip_3) + str(dip_4)
	full_bits = full_bits + str(dip_5) + str(dip_6) + str(dip_7) + str(dip_8)
	print full_bits
	hex_value = hex(int(full_bits,2))
	print hex_value
	ascii_value = binascii.unhexlify(hex_value)
	print ascii_value
	time.sleep(1)


