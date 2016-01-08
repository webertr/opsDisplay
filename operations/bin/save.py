#!/usr/bin/python

import csv
import sys
import os
import time
import epics
import save_restore_uwcc
from Tkinter import *
import tkFileDialog


def submit():

    global file_name

    OpsLogPV=epics.PV('CCC:OpsDisplay:System:Write.VAL')

    OpsLogPV.put(value='Saving...')

    submit.pack_forget()

    nosubmit.configure(text = 'Abort', command = root.quit)

    pvconnectedstatus=OpsLogPV.wait_for_connection()

    save_success=save_restore_uwcc.save_pvs('/usr/local/cnts/epics/operations/lib/utilities/Cyclotron.request.test', file_name, debug=False)

    if save_success==True:
        OpsLogPV.put(value='Save Successfull')
    else:
        OpsLogPV.put(value='Save Failed')

    root.quit()




path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)


file_name = tkFileDialog.asksaveasfilename(title='Choose a file to Save to:')


root = Tk()

root.title('Save Files')

label = Message( root, text='Do you want to save: \n'+file_name+'?', width=500, font=30)

submit = Button(root, text ='Yes', command = submit)

nosubmit = Button(root, text ='No', command = root.quit)

label.pack()

nosubmit.pack(side=BOTTOM)

submit.pack(side=BOTTOM)


root.mainloop()


