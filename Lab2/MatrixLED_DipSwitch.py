# -*- coding: utf8 -*-
import RPi.GPIO as IO  #calling for header file which helps in using GPIO’s of PI
import time            #calling for time to provide delays in program
IO.setwarnings(False)  #do not show any warnings
x=1
y=1

#Initialize the pins for Matrix LEDs
IO.setmode (IO.BCM)  #programming the GPIO by BCM pin numbers. (like PIN29 as'GPIO5')
IO.setup(12,IO.OUT)  #initialize GPIO12 as an output.
IO.setup(22,IO.OUT)  #initialize GPIO22 as an output.
IO.setup(27,IO.OUT)
IO.setup(25,IO.OUT)
IO.setup(17,IO.OUT)
IO.setup(24,IO.OUT)
IO.setup(23,IO.OUT)
IO.setup(18,IO.OUT)
IO.setup(21,IO.OUT)
IO.setup(20,IO.OUT)
IO.setup(26,IO.OUT)
IO.setup(16,IO.OUT)
IO.setup(19,IO.OUT)
IO.setup(13,IO.OUT)
IO.setup(6,IO.OUT)
IO.setup(5,IO.OUT)

#Initialize the pins for DIP Switch
IO.setup(2,IO.IN)  #initialize GPIO2 (PIN 3) as an output.
IO.setup(3,IO.IN)  #initialize GPIO3 (PIN 5) as an output.
IO.setup(4,IO.IN)
IO.setup(14,IO.IN)
IO.setup(15,IO.IN)
IO.setup(10,IO.IN)
IO.setup(9,IO.IN)
IO.setup(11,IO.IN)

PORTVALUE = [128,64,32,16,8,4,2,1]

#value of pin in each port for the left and right sides
A_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10010000,0b10010000,0b11111111]
B_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b01111110,0b10010001,0b10010001,0b11111111]
C_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b10000001,0b10000001,0b10000001,0b01111110]
D_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b00111100,0b01000010,0b10000001,0b11111111]
E_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b10010001,0b10010001,0b10010001,0b11111111]
F_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b10010000,0b10010000,0b10010000,0b11111111]
arr_0_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10000001,0b10000001,0b11111111]
arr_1_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00000000,0b00000000]
arr_2_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11110001,0b10010001,0b10010001,0b10011111]
arr_3_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10010001,0b10010001,0b10010001]
arr_4_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00010000,0b00010000,0b11110000]
arr_5_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b10011111,0b10010001,0b100010001,0b11110001]
arr_6_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b10011111,0b10010001,0b10010001,0b11111111]
arr_7_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10000000,0b10000000,0b10000000]
arr_8_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10010001,0b10010001,0b11111111]
arr_9_left=[0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10010001,0b10010001,0b11110001]


A_right=[0b11111111,0b10010000,0b10010000,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
B_right=[0b01111110,0b10010001,0b10010001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
C_right=[0b10000001,0b10000001,0b10000001,0b01111110,0b00000000,0b00000000,0b00000000,0b00000000]
D_right=[0b00111100,0b01000010,0b10000001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
E_right=[0b10010001,0b10010001,0b10010001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
F_right=[0b10010000,0b10010000,0b10010000,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
arr_0_right=[0b11111111,0b10000001,0b10000001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
arr_1_right=[0b00000000,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000]
arr_2_right=[0b11110001,0b10010001,0b10010001,0b10011111,0b00000000,0b00000000,0b00000000,0b00000000]
arr_3_right=[0b11111111,0b10010001,0b10010001,0b10010001,0b00000000,0b00000000,0b00000000,0b00000000]
arr_4_right=[0b11111111,0b00010000,0b00010000,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000]
arr_5_right=[0b10011111,0b10010001,0b100010001,0b11110001,0b00000000,0b00000000,0b00000000,0b00000000]
arr_6_right=[0b10011111,0b10010001,0b10010001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
arr_7_right=[0b11111111,0b10000000,0b10000000,0b10000000,0b00000000,0b00000000,0b00000000,0b00000000]
arr_8_right=[0b11111111,0b10010001,0b10010001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000]
arr_9_right=[0b11111111,0b10010001,0b10010001,0b11110001,0b00000000,0b00000000,0b00000000,0b00000000]

#mapping of hex value to the array on the left side of the matrix
hex_to_arr_left = {
    'a':A_left,
    'b':B_left,
    'c':C_left,
    'd':D_left,
    'e':E_left,
    'f':F_left,
    '0':arr_0_left,
    '1':arr_1_left,
    '2':arr_2_left,
    '3':arr_3_left,
    '4':arr_4_left,
    '5':arr_5_left,
    '6':arr_6_left,
    '7':arr_7_left,
    '8':arr_8_left,
    '9':arr_9_left 
}

#mapping of hex value to the array on the right side of the matrix
hex_to_arr_right = {
    'a':A_right,
    'b':B_right,
    'c':C_right,
    'd':D_right,
    'e':E_right,
    'f':F_right,
    '0':arr_0_right,
    '1':arr_1_right,
    '2':arr_2_right,
    '3':arr_3_right,
    '4':arr_4_right,
    '5':arr_5_right,
    '6':arr_6_right,
    '7':arr_7_right,
    '8':arr_8_right,
    '9':arr_9_right 
}

def PORT(pin):  #assigning GPIO state by taking 'pin' value
    if(pin&0x01 == 0x01):
        IO.output(21,0)   #if bit0 of 8bit 'pin' is true pull PIN21 low
    else:
        IO.output(21,1)   #if bit0 of 8bit 'pin' is false pull PIN21 high
    if(pin&0x02 == 0x02):
        IO.output(20,0)   #if bit1 of 8bit 'pin' is true pull PIN20 low
    else:
        IO.output(20,1)   #if bit1 of 8bit 'pin' is false pull PIN20 high
    if(pin&0x04 == 0x04):
        IO.output(26,0)   #if bit2 of 8bit 'pin' is true pull PIN26 low
    else:
        IO.output(26,1)   #if bit2 of 8bit 'pin' is false pull PIN26 high
    if(pin&0x08 == 0x08):
        IO.output(16,0)
    else:
        IO.output(16,1)
    if(pin&0x10 == 0x10):
        IO.output(19,0)
    else:
        IO.output(19,1)
    if(pin&0x20 == 0x20):
        IO.output(13,0)
    else:
        IO.output(13,1)
    if(pin&0x40 == 0x40):
        IO.output(6,0)
    else:
        IO.output(6,1)
    if(pin&0x80 == 0x80):
        IO.output(5,0)
    else:
        IO.output(5,1)


def PORTP(pinp):    #assigning GPIO logic for positive terminals by taking 'pinp' value
    if(pinp&0x01 == 0x01): 
        IO.output(12,1)     #if bit0 of 8bit 'pinp' is true pull PIN12 high
    else:
        IO.output(12,0)     #if bit0 of 8bit 'pinp' is false pull PIN12 low
    if(pinp&0x02 == 0x02):
        IO.output(22,1)     #if bit1 of 8bit 'pinp' is true pull PIN22 high
    else:
        IO.output(22,0)     #if bit1 of 8bit 'pinp' is false pull PIN22 low
    if(pinp&0x04 == 0x04):
        IO.output(27,1)     #if bit2 of 8bit 'pinp' is true pull PIN27 high
    else:
        IO.output(27,0)     #if bit2 of 8bit 'pinp' is false pull PIN27 low
    if(pinp&0x08 == 0x08):
        IO.output(25,1)
    else:
        IO.output(25,0)
    if(pinp&0x10 == 0x10):
        IO.output(17,1)
    else:
        IO.output(17,0)
    if(pinp&0x20 == 0x20):
        IO.output(24,1)
    else:
        IO.output(24,0)
    if(pinp&0x40 == 0x40):
        IO.output(23,1)
    else:
        IO.output(23,0)
    if(pinp&0x80 == 0x80):
        IO.output(18,1) #if bit7 of 8bit 'pinp' is true pull PIN18 high
    else:
        IO.output(18,0) #if bit7 of 8bit 'pinp' is false pull PIN18 low


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
    full_bits4 = full_bits + str(dip_1) + str(dip_2) + str(dip_3) + str(dip_4)
    full_bits8 = full_bits + str(dip_5) + str(dip_6) + str(dip_7) + str(dip_8)
    hex_value4 = hex(int(full_bits4,2)).replace('0x','') #Left side
    hex_value8 = hex(int(full_bits8,2)).replace('0x','') #right side
    #print hex_value4
    #print hex_value8

    for x in range (8): #execute the loop 8 times incrementing x value from zero to seven
        pin  = PORTVALUE[x]  #assigning value to 'pin' for each digit
        PORT(pin);  #mapping appropriate GPIO 
        if hex_value4 in hex_to_arr_left:
            result_arr = hex_to_arr_left[hex_value4] #find hex value in list of arrays
            pinp = result_arr[x] #assigning character of the first 4 bits
            PORTP(pinp); #turning the GPIO to show character of the first 4 bits
        else:
            print 'Value not in dictionary'
        if hex_value8 in hex_to_arr_right:
            result_arr = hex_to_arr_right[hex_value8] #find hex value in list of arrays
            pinp = result_arr[x] #assigning character of the last 4 bits
            PORTP(pinp); #turning the GPIO to show character of the last 4 bits
        else:
            print 'Value not in dictionary'
        time.sleep(0.0005) #wait for 0.5msec

    pinp= 0
    PORTP(pinp);