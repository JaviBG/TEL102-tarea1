import matplotlib.pyplot as plt
import numpy as np

lala = (4,5,6,2)

def graficar(tupla):
     if len(tupla) == 1:
          y = tupla[0]
          x = np.arange(-10,10,0.5)   
          plt.plot(x,y)
          plt.title(str(y)+ "x")
          plt.xlabel('X')
          plt.ylabel('Y')
          plt.show()
     elif len(tupla) == 2:
          b = tupla[0]
          c = tupla[1]
          x = np.arange(-10,10,0.5)
          y = b*x + c
          plt.plot(x,y)
          plt.title(str(b) + 'x + ' + str(c))
          plt.xlabel('X')
          plt.ylabel('Y')
          plt.show()
     elif len(tupla) == 3:
          a = tupla[0]
          b = tupla[1]
          c = tupla[2]
          x = np.arange(-10,10,0.5)
          y = a*x**2 + b*x + c
          plt.plot(x,y)
          plt.title(str(a) + 'x^2 + ' + str(b) + 'x + ' + str(c))
          plt.xlabel('X')
          plt.ylabel('Y')
          plt.show()

     elif len(tupla) == 4:
          a = tupla[0]
          b = tupla[1]
          c = tupla[2]
          d = tupla[3]
          x = np.arange(-10,10,0.5)
          y = a*x**3 + b*x**2 + b*x + c
          plt.plot(x,y)
          plt.title(str(a) + 'x^3 + ' + str(b) + 'x^2 + ' + str(c) + 'x + ' + str(d))
          plt.xlabel('X')
          plt.ylabel('Y')
          plt.show()         
     #else: ?? lo que queramos, un error o algo 

graficar(lala)





