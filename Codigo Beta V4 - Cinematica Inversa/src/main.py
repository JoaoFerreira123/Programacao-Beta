from tkinter import *
import serial

w = Tk()
w.minsize(400, 200)
w.title('Painel de Controle Beta')

esp32 = serial.Serial('COM4', 115200)

def baseGir(pos_BaseGir):
    pos_BaseGir = 'R'+pos_BaseGir+"/"
    esp32.write(pos_BaseGir.encode())
    print(pos_BaseGir)

def bracoA(pos_BracoA):
    pos_BracoA = 'A'+pos_BracoA+"/"
    esp32.write(pos_BracoA.encode())
    print(pos_BracoA)

def bracoB(pos_BracoB):
    pos_BracoB = 'B'+pos_BracoB+"/"
    esp32.write(pos_BracoB.encode())
    print(pos_BracoB)

def bracoC(pos_BracoC):
    pos_BracoC = 'C'+pos_BracoC+"/"
    esp32.write(pos_BracoC.encode())
    print(pos_BracoC)

def conectorGarra(pos_ConectorGarra):
    pos_ConectorGarra = 'T'+pos_ConectorGarra+"/"
    esp32.write(pos_ConectorGarra.encode())
    print(pos_ConectorGarra)

def garra(pos_Garra):
    pos_Garra = 'G'+pos_Garra+"/"
    esp32.write(pos_Garra.encode())
    print(pos_Garra)


nPos = -1
def gravar():
    global nPos 
    nPos += 1
    salvar = "S"+str(nPos)+"/"
    esp32.write(salvar.encode())
    print(salvar)

def play():
    p = "P/"
    esp32.write(p.encode())
    print(p)

def erase():
    e = "E/"
    esp32.write(e.encode())
    print(e)
    

baseGir = Scale(from_=0, to=180, command=baseGir, showvalue=True, orient = 'horizontal')
bracoA = Scale(from_=0, to=180, command=bracoA, showvalue=True, orient= 'horizontal')
bracoB = Scale(from_=0, to=180, command=bracoB, showvalue=True, orient='horizontal')
bracoC = Scale(from_=0, to=180, command=bracoC, showvalue=True, orient='horizontal')
conectorGarra = Scale(from_=0, to=180, command=conectorGarra, showvalue=True, orient='horizontal')
garra = Scale(from_=0, to=180, command=garra, showvalue=True, orient='horizontal')

botaoSalvar = Button(text='Salvar Poisção', command=gravar)

botaoPlay = Button(text='Play', command=play)

botaoErase = Button(text='Apagar', command=erase)

texto = Text(height=5, width=30)
texto.insert(END, "POSICOES AQUI")



baseGir.grid(row=0, column=0)
bracoA.grid(row=1, column=0)
bracoB.grid(row=2, column=0)
bracoC.grid(row=3, column=0)
conectorGarra.grid(row=4, column=0)
garra.grid(row=5, column=0)

botaoSalvar.grid(row=5, column=1)
botaoPlay.grid(row=5, column=2)
botaoErase.grid(row=5, column=3)

texto.grid(row=2, column=2)

baseGir.set(90)
bracoA.set(90)
bracoB.set(90)
bracoC.set(90)
conectorGarra.set(90)


w.mainloop()