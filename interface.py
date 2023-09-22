# -*- coding: utf-8 -*-
"""
Created on Thu Sep 21 11:22:49 2023

@author: 33667
"""

from tkinter import * 
from tkinter import ttk
import tkinter as tk

wnd = Tk()
wnd.geometry("420x300")


# Navigation menu
def alert():
    showinfo("alerte", "Bravo!")

menubar = Menu(wnd)

menu1 = Menu(menubar, tearoff=0)
menu1.add_command(label="Créer", command=alert)
menu1.add_command(label="Editer", command=alert)
menu1.add_separator()
menu1.add_command(label="Quitter", command=wnd.quit)
menubar.add_cascade(label="Fichier", menu=menu1)

menu2 = Menu(menubar, tearoff=0)
menu2.add_command(label="Couper", command=alert)
menu2.add_command(label="Copier", command=alert)
menu2.add_command(label="Coller", command=alert)
menubar.add_cascade(label="Editer", menu=menu2)

menu3 = Menu(menubar, tearoff=0)
menu3.add_command(label="A propos", command=alert)
menubar.add_cascade(label="Aide", menu=menu3)

wnd.config(menu=menubar)

label = Label(wnd, text="Connect first!")
label.grid(row=1)

categories = [
    "Common Commands",
    "MMEMory Commands",
    "OUTPut Command",
    "SOURce Commands",
    "STATus Commands",
    "SYSTem Commands",
    "TRIGger Commands",
    "UNIT Command"
] 


common = [
     "*CLS",
     "*ESE", 
     "*ESR?",
     "*IDN?",
     "*OPT?",
     "*PSC",
     "*RST",
     "*SRE",
     "*STB?",
     "*TRG",
     "*WAI"
]

textExplanation = "Clear all the event registers and the error queue."


def Explanation(request):
    textExplanation = StringVar(wnd)
    if request=="*CLS":
        textExplanation = "Clear all the event registers and the error queue."
    elif request=="*IDN?":
        textExplanation = "Query the ID character string of the instrument."
    return textExplanation

 
def switchCategoriesToRequests(category):
    common = [
        "*CLS",
        "*ESE", 
        "*ESR?",
        "*IDN?",
        "*OPT?",
        "*PSC",
        "*RST",
        "*SRE",
        "*STB?",
        "*TRG",
        "*WAI"
    ]
        
    mmemory = [
        "MMEMory:CATalog",
        "MMEMory:CATalog:LENGth",
        "MMEMory:COPY",
        "MMEMory:DATA:IQ",
        "MMEMory:DATA:IQ:LIST",
        "MMEMory:DELete",
        "MMEMory:DISK:FORMat",
        "MMEMory:DISK:INFormation",
        "MMEMory:FILEtype",
        "MMEMory:LDISk:SPACe",
        "MMEMory:MDIRectory"
        ]
    
    output = [
        "OUTPut[:STATe]"
        ]
    
    source = [
        "[SOURce]:AM Command Subsystem",
        "[SOURce]:CORRection Command Subsystem"    
        ]
    
    status = [
        "STATus:OPERation:CONDition",
        "STATus:OPERation:ENABle"
        ]
    
    system = [
        ":SYSTem:BRIGhtness",
        ":SYSTem:CLEar"
        ]
    
    trigger = [
        ":TRIGger:IQ[IMMediate]",
        ":TRIGger:LFOutput[IMMediate]",
        ":TRIGger:PULSe[IMMediate]",
        ":TRIGger:SWEep[IMMediate]"
        ]
    
    unit = [
        "UNIT:POWer"
            ]

    match category:
        case "Common Commands":
            return common 
        case "MMEMory Commands":
            return mmemory
        case "OUTPut Command":
            return output
        case "SOURce Commands":
            return source
        case "STATus Commands":
            return status
        case "SYSTem Commands":
            return system
        case "TRIGger Commands":
            return trigger
        case "UNIT Command":
            return unit

    
def callback1(selection):
    categorie=var1.get()
    
    # Reset var and delete all old options
    var2.set('')
    opt2['menu'].delete(0, 'end')

    categorieRequest = switchCategoriesToRequests(categorie)
    var2.set(categorieRequest[0])

    for common in categorieRequest:
        opt2['menu'].add_command(label=common, command=tk._setit(var2, common))
        
        
def callback2(selection):
    print(selection)
    explanation = Explanation(selection)
    labelExplanation.config(text=explanation)
        

# dropdown list for categories
var1 = StringVar(wnd)
var1.set(categories[0])

opt1 = OptionMenu(wnd, var1, *categories, command=callback1)
opt1.config(width=30, font=('Helvetica', 12))
opt1.grid(row=2, columnspan = 6)

# dropdown list for requests
var2 = StringVar(wnd)
var2.set(common[0])

opt2 = OptionMenu(wnd, var2, *common, command=callback2)
opt2.config(width=40, font=('Helvetica', 12))
opt2.grid(row=3, columnspan = 6)


# Line break
Label(wnd, text="").grid(row=4, column=0)  

 
# label Explanation
labelTitle = Label(wnd, text="Explanations : ", bg="yellow")
labelTitle.grid(row=5, column=0)  

labelExplanation = Label(wnd, text=textExplanation)
labelExplanation.grid(row=5, column=1, columnspan= 4)  

# Line break
Label(wnd, text="").grid(row=6, column=0)  

# Write
btn_write = Button(wnd, text ='Write')
btn_write.grid(row=7, column=0)

# entrée
def recupere():
    showinfo("Alerte", entree.get())

# Text zone for request
value = StringVar()
value.set("Valeur")
entree = Entry(wnd, textvariable=value, width=10)
entree.grid(row=7, column=1)

# Choose unit
Units=["kHz", "MHz","GHz"]
listUnits = ttk.Combobox(wnd, values=Units, width=5)
listUnits.current(0)
listUnits.grid(row=7, column=2)

# Read
btn_read = Button(wnd, text ='Read')
btn_read.grid(row=8, column=0)

# Connect button
btn_connect =Button(wnd, text ='OnConnect')
btn_connect.grid(row=7, column=5)

# Valid button
btn_valid = Button(wnd, text="Valider", command=recupere)
btn_valid.grid(row=8, column=5)

# Quit button
bnt_quit=Button(wnd, text="Fermer", command=wnd.quit)
bnt_quit.grid(row=9, column=5)



wnd.mainloop()
