import RPi.GPIO as GPIO
import time
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)

p = GPIO.PWM(24, 0.5)
q = GPIO.PWM(22, 1000)
p.start(0)
q.start(0)

try:
    while True:
        print("Введите коэффициент заполнения")
        a = input()
        if a == 'q':
            sys.exit()
        if a.isdigit() == 0:
            print("Введите корректный коэффициент заполнения \n")
        else:
            a = int(a)
            if not (0 <= a <= 100):
                print("Введите корректный коэффициент заполнения \n")
            else:
                p.start(a)
                q.start(a)
                print("V_out = {:.4f}".format(3.3*a/100))
finally:
    GPIO.output(24, 0)    
    GPIO.cleanup()