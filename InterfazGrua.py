from tkinter import *


a = "text"

def takefromto(x):
        # if x=="P1":
        #     a
        print(x)

def takefrom(x):
        # if x=="P1":
        #     a.set("Hello")
        #     print(a.get())

        # elif x=="P2":
        #     a.set("bye")
        #     print(a.get())
        # elif x=="P3":
        #     a.set("algo")
        #     print(a.get())
        print(x)

def taketo(x):
    print(x)

def up():
    print("arriba")
    a

def down():
    print("abajo")
    a

def left():
    print("izquierda")
    a

def right():
    print("derecha")
    a

def stop():
    print("pare")
    a

def first():
    a

def second():
    a

def third():
    a

def magnet():
    a

def taketo():
    a

def hanoi():
    a


Ventana=Tk()
Ventana.geometry("800x600+0+0")
Ventana.title("Grúa")

o1=StringVar(Ventana)
o1.set("Selecciona")
o = OptionMenu(Ventana, o1, "P1", "P2", "P3", command=takefrom)
o.place(x = 30, y = 420)

o2=StringVar(Ventana)
o2.set("Selecciona")
to= OptionMenu(Ventana, o2, "P1", "P2", "P3", command=taketo)
to.place(x = 30, y = 520)

o3=StringVar(Ventana)
o3.set("Selecciona")
tph=OptionMenu(Ventana, o3, "P1", "P2", "P3", command=takefromto)
tph.place(x = 250, y = 420)

o4=StringVar(Ventana)
o4.set("Selecciona")
h = OptionMenu(Ventana, o4, "P1", "P2", "P3", command=takefromto)
h.place(x = 150, y = 520)


e1=Label(Ventana,text="Coger de:",fg='black',bg='ivory3').place(x=30,y=398)
Ventana.config(bg="ivory3")
#Ventana.config(width="1200"
# miframe=Frame()
# miframe.pack()
# miframe.config(bg="ivory3")
# miframe.config(width="800",height="400")

e2=Label(Ventana,text="Llevar hasta",fg='black',bg='ivory3').place(x = 250, y = 398)

e3=Label(Ventana, text = "Transportar desde, hasta", fg = 'black', bg = 'ivory3').place(x = 30, y = 498)

#e4=Label(Ventana,text="_______________________________________________________________________").place(x=0,y=470)


flecharriba=PhotoImage(file="resources/flechaarriba.PNG")
ButtArr=Button(Ventana,image=flecharriba,height=110,width=110,command=up).place(x=120,y=0)
flechabajo=PhotoImage(file="resources/flechabajo.PNG")
ButtAba=Button(Ventana,image=flechabajo,height=110,width=110,command=down).place(x=120,y=230)
flechaizq=PhotoImage(file="resources/flechaizq.PNG")
ButtArr=Button(Ventana,image=flechaizq,height=110,width=110,command=left).place(x=0,y=115)
flechader=PhotoImage(file="resources/flechader.PNG")
ButtArr=Button(Ventana,image=flechader,height=110,width=110,command=right).place(x=240,y=115)
ImgRay=PhotoImage(file="resources/rayo.PNG")
BtStop=Button(Ventana,image=ImgRay,height=110,width=110,command=stop).place(x=120,y=115)
# RayaNegra=PhotoImage(file="resources/Negra.PNG")
# lblRaya=Label(Ventana,image=RayaNegra).place(x=0,y=470)

ButtonHanoi=Button(Ventana,text="Jugar Hanoi", height=6,width=15,command=hanoi).place(x=400,y=120)

ButtonGoTDH=Button(Ventana,text= "GO",height=1,width=2,command=taketo).place(x=260,y=520) #Aquí cambiar comando
ButtonGoCD=Button(Ventana,text="GO",height=1,width=2,command=taketo).place(x=145,y=420)
ButtonGoLH=Button(Ventana,text="GO",height=1,width=2,command=taketo).place(x=360,y=420)


ButtonP1=Button(Ventana,text= "P1",height=3,width=10,command=first).place(x=530,y=120)
ButtonP2=Button(Ventana,text= "P2",height=3,width=10,command=second).place(x=530,y=220)
ButtonP3=Button(Ventana,text= "P3",height=3,width=10,command=third).place(x=530,y=320)
Ventana.mainloop()