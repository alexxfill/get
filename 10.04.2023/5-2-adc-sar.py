import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

dac = [26, 19, 13, 6, 5, 11, 9, 10]
comp = 4
troyka = 17

levels = 2**len(dac)
maxV = 3.3

GPIO.setup(dac, GPIO.OUT)
GPIO.setup(troyka, GPIO.OUT, initial = GPIO.HIGH)
GPIO.setup(comp, GPIO.IN)

def dec2bin(x):
    return [int(i) for i in bin(x)[2:].zfill(8)]

def adc():
    R = 0
    for i in range(7, -1, -1):
        R += 2**i 
        sgn = dec2bin(R)
        GPIO.output(dac, sgn)
        time.sleep(0.001)
        if GPIO.input(comp) == 0:
            R -= 2**i
    return R

try:
    while True:
        value = adc()
        V = (value / levels) * maxV
        print("ADC value = {:^3}, input = {:.2f}".format(value, V))
finally:
    GPIO.output(dac, 0)
    GPIO.output(troyka, 0)
    GPIO.cleanup()