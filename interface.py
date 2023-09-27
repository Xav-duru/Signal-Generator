# -*- coding: utf-8 -*-
"""
Created on Thu Sep 21 11:22:49 2023

@author: 33667
"""

from tkinter import * 
from tkinter import ttk
import tkinter as tk
import csv
import pandas

#lire = pandas.read_csv(r"C:/Users/33667/OneDrive - ESEO/Bureau/ESEO/Suède/Percy Roc/Python\Commands.csv")
#print(lire)

wnd = Tk()
wnd.geometry("420x300")




#label = Label(wnd, text="Connect first!")
#label.grid(row=1)

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
    
def getRequest():
    request=syntax + entree.get()
    print(request)
        
# Title
labelTitle = Label(wnd, text="Signal generator: RIGOL", font=("Courier", 22), bg="yellow")
labelTitle.grid(row=0, column=0, columnspan=6)  

# Line break
Label(wnd, text="").grid(row=1, column=0)  

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
labelTitle = Label(wnd, text="Explanations:")
labelTitle.grid(row=5, column=0)  

labelExplanation = Label(wnd, text=textExplanation)
labelExplanation.grid(row=5, column=1, columnspan= 4)  

# Line break
Label(wnd, text="").grid(row=6, column=0)  

 
# label syntax
syntax = "syntax:"
labelSyntax = Label(wnd, text=syntax)
labelSyntax.grid(row=8, column=0)  


# Text zone for request
value = StringVar()
value.set("")
request = StringVar()
entree = Entry(wnd, textvariable=value, width=20)
entree.grid(row=8, column=1)



# Connect button
btn_connect =Button(wnd, text ='OnConnect', width=10, padx=5, pady=5)
btn_connect.grid(row=7, column=5)

# Valid button
btn_valid = Button(wnd, text="Valider", command=getRequest, width=10, padx=5, pady=5)
btn_valid.grid(row=8, column=5)

# Quit button
bnt_quit=Button(wnd, text="Fermer", command=wnd.quit, width=10, padx=5, pady=5)
bnt_quit.grid(row=9, column=5)



wnd.mainloop()
