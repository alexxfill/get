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

def adc1():
    for i in range(256):
        sig = dec2bin(i)
        GPIO.output(dac, sig)       
        time.sleep(0.01)
        if GPIO.input(comp) == 0:
            return(i)

def adc2():
    R = 0
    for i in range(7, -1, -1):
        R += 2**i 
        sgn = dec2bin(R)
        GPIO.output(dac, sgn)
        time.sleep(0.001)
        if GPIO.input(comp) == 0:
            R -= 2**i
    return R   