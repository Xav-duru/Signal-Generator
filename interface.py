# -*- coding: utf-8 -*-
"""
Created on Thu Sep 21 11:22:49 2023

@author: 33667
"""

from tkinter import * 
from tkinter import ttk

wnd = Tk()
wnd.geometry("400x300")


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
label.pack()

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



mmemory = [
    "MMEMory:CATalog",
    "MMEMory:CATalog:LENGth"
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



def switchCategoriesToRequests(category):
    match category:
        case "Common Commands":
            return 'common'
        case "MMEMory Commands":
            return 'mmemory'
        case "OUTPut Command":
            return 'output'
        case "SOURce Commands":
            return 'source'
        case "STATus Commands":
            return 'status'
        case "SYSTem Commands":
            return 'system'
        case "TRIGger Commands":
            return 'trigger'
        case "UNIT Command":
            return 'unit'
        
        
def choose(category):
    if category=="Common Commands":
        return common
    elif category=="MMEMory Commands":
        return mmemory
    elif category=="OUTPut Commands":
        return output
    
def callback(selection):
    print(variable.get())
    label['text'] = variable.get()
    categorie=variable.get()
    print(switchCategoriesToRequests(categorie))

    variable2.set(switchCategoriesToRequests(categorie[0]))
    opt2 = OptionMenu(wnd, variable, *categorie)
    opt2.config(width=90, font=('Helvetica', 12))
    opt2.pack() 
    
    return variable.get()
    
variable = StringVar(wnd)
variable.set(categories[1])

variable2 = StringVar(wnd)

opt = OptionMenu(wnd, variable, *categories, command=callback)
opt.config(width=90, font=('Helvetica', 12))
opt.pack()
 
# label
text = StringVar()
label = Label(wnd, text=variable.get(), bg="yellow")
label.pack()   


#listeCombo = ttk.Combobox(wnd, values=switchCategoriesToRequests(variable.get))
#listeCombo.current(0)
#listeCombo.pack()


# Write
btn_write = Button(wnd, text ='Write')
btn_write.pack(side=LEFT, padx=10, pady=10)

# entrée
def recupere():
    showinfo("Alerte", entree.get())

value = StringVar()
value.set("Valeur")
entree = Entry(wnd, textvariable=value, width=30)
entree.pack()

# Read
btn_read = Button(wnd, text ='Read')
btn_read.pack(side=LEFT, padx=10, pady=10)





# Connect button
btn_connect =Button(wnd, text ='OnConnect')
btn_connect.pack(side=RIGHT)


btn_valid = Button(wnd, text="Valider", command=recupere)
btn_valid.pack(side=RIGHT)

# bouton de sortie
bnt_quit=Button(wnd, text="Fermer", command=wnd.quit)
bnt_quit.pack(side=RIGHT)



wnd.mainloop()