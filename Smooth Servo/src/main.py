from tkinter import VERTICAL, Scale, Tk, Button
import serial

w = Tk()
w.minsize(400, 200)

arduino = serial.Serial('COM4', 115200)

def servo(pos):
    pos = pos+'/'
    arduino.write(pos.encode())
    print(pos)

servo = Scale(from_=0, to=180, command=servo, showvalue=True, orient='horizontal')
servo.pack()
servo.set(90)


w.mainloop()