#Importando 
from tkinter import*
from tkinter import messagebox
from tkinter.filedialog import askopenfilename
from tkinter.messagebox import showerror

import tkinter.messagebox
import matplotlib.pyplot as plt
import numpy as np

from lagrange import *

import shutil, os

#Creando ventana
ventana = Tk()
ventana.geometry("330x400")
ventana.title("Interpolación Polinómica de Lagrange")


#Declarando Variables
a = DoubleVar()
b = DoubleVar()
c= DoubleVar()
restx1 = StringVar()
restx2 = StringVar()

#Declarando funciones 

##Funcion graficar
def graficar():
     a = aA.get()
     b = bB.get()
     c = cC.get()
     ax = float(a)
     bx = float(b)
     cx  = float (c)  
     x = np.arange(-10,10,0.5)
     y = ax*x**2 + bx*x + cx
     plt.plot(x,y)
     plt.title('a*x^2 + b*x + c = 0')
     plt.xlabel('X')
     plt.ylabel('Y')
     plt.show()

##Funcion para usar .in y que te de el resultado
def load_file():
    filename = askopenfilename()
    #filetypes=(("Datos", "*.in"), ("All files", "*.*"))
    if filename:
        try:
            ruta = os.getcwd() + os.sep
            origen = filename
            destino = ruta + 'datos/datos.in'
            try:
                shutil.copyfile(origen, destino)
                print("Archivo copiado")
            except:
                print("Se ha producido un error")
            tupla = lagrange_interpolation()
            lista = list(tupla)
            numeros = lista[::-1]
            texto = ""
            for i in numeros:
              if numeros.index(i) != 0:
                texto += " + " + str(i) + "*(x^" + str(numeros.index(i)) + ")"
              else:
                texto += str(i)
            tkinter.messagebox.showinfo("Resulado", texto)
        except:                     # <- naked except is a bad idea
              showerror("Open Source File", "No se puede leer archivo\n'%s'" % filename)
        return
 
             
#Maquetado interfaz
aA = Entry(ventana, textvariable = a)
aA.place(bordermode = OUTSIDE, height = 30, width = 50, x = 10, y = 290)
bB = Entry (ventana, textvariable = b)
bB.place(bordermode = OUTSIDE, height = 30, width = 50, x = 130, y = 290)
cC = Entry(ventana, textvariable = c)
cC.place(bordermode = OUTSIDE, height = 30, width = 50, x = 230, y = 290)

#Entrada de Texto
xa = Label(ventana, text = "X^2 + ")
xa.place(bordermode = OUTSIDE, height = 30, width = 50, x =70,y=290)
xb = Label(ventana, text = "X + ")
xb.place(bordermode = OUTSIDE, height = 30, width = 50, x = 180, y = 290)
xc = Label(ventana, text = "= 0 ")
xc.place(bordermode = OUTSIDE, height = 30, width = 50, x=280, y = 290)

#Boton de graficar

graficar = Button ( ventana, text = "Graficar", command = graficar)
graficar.place(bordermode= OUTSIDE, height= 40, width = 100, x = 110, y = 340)

#Boton para buscar archivo

button = Button(ventana, text="Buscar .in y resultado", command=load_file, width=10)
button.place(bordermode= OUTSIDE, height= 40, width = 150, x = 90, y = 220)


#Instrucciones
ins = Label(ventana, text = "Instrucciones")
ins.place(bordermode = OUTSIDE, height = 30, width = 120, x=110, y = 20)

instext = Label(ventana, text = "hoalasddasdadasdvbaasjsadaskfbakdjjfdasdadasdadaas\n \njasjaasdkshajhfajdsajhbasjhdasfhjhfkfsdfadfhgjdjsjasja\njajajshabsjdabfahfsjhfahfahhdasdjshbajdha\n \n \n \n \n gjdafjahdsadjdadsa")#cuando las tengamos
instext.place(bordermode = OUTSIDE, height = 160 , width = 280, x=20, y = 40)

ventana.mainloop()
