#!/usr/bin/python

import csv
import sys
import os
import time
import epics
import save_restore_uwcc
from Tkinter import *
import tkFileDialog
import pysvn


def commit():

    global file_name
    global var1

    client_svn = pysvn.Client()
    stat_svn=client_svn.status(file_name)

    OpsLogPV=epics.PV('CCC:OpsDisplay:System:Write.VAL')

    OpsLogPV.put(value='Saved Settings Loading...')

    submit.pack_forget()

    nosubmit.configure(text = 'Abort', command = root.quit)

    pvconnectedstatus=OpsLogPV.wait_for_connection()

    restore_success=save_restore_uwcc.restore_pvs(file_name, debug=False)

    if restore_success==True:
        OpsLogPV.put(value='Restore Completed')
    else:
        OpsLogPV.put(value='Restore Failed')

    root.quit()




def submit():

    global file_name
    global var1
    global submit

    client_svn = pysvn.Client()
    stat_svn=client_svn.status(file_name)
    if stat_svn[0].text_status != pysvn.wc_status_kind.normal:
        submit.configure(text = 'Fine, do it', command=commit)
        nosubmit.configure(text = 'No, don\'t', command = root.quit)
        var1.set('File Not Up to Date')
        return


    OpsLogPV=epics.PV('CCC:OpsDisplay:System:Write.VAL')

    pvconnectedstatus=OpsLogPV.wait_for_connection()
            
    OpsLogPV.put(value='Saved Settings Being Loaded')

    restore_success=save_restore_uwcc.restore_pvs(file_name, debug=False)

    if restore_success==True:
        OpsLogPV.put(value='Restore Completed')
    else:
        OpsLogPV.put(value='Restore Failed')

    root.quit()


root = Tk()

path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)


file_name = tkFileDialog.askopenfilename(title='Choose a file to Restore To:')


root.title('Restore Files')

var1 = StringVar()

label = Message(root, textvariable=var1, width=500, font=30)

submit = Button(root, text='Yes', command = submit)

nosubmit = Button(root, text ='No', command = root.quit)

var1.set('Do you want to restore: \n'+file_name+'?')

label.pack()

nosubmit.pack(side=BOTTOM)

submit.pack(side=BOTTOM)

root.mainloop()


