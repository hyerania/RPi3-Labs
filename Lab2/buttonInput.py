#buttonInput.pyD
import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
sleepTime = 0.1

lightPin = 4
buttonPin = 17

GPIO.setup(lightPin, GPIO.OUT)
GPIO.setup(buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.output(lightPin, False)

while True:
	GPIO.output(lightPin, GPIO.input(buttonPin))
	sleep(.1)
