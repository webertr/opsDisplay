#!/usr/bin/python

import csv
import sys
import os
import time
import pysvn
from Tkinter import *
from tkFileDialog import askopenfilename



def submit():
    global file_name
    client_svn = pysvn.Client()
    client_svn.add(file_name)
    root.quit()


path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)



Tk().withdraw() # we don't want a full GUI, so keep the root window from appearing
file_name = askopenfilename(title='Choose a file to Add: ') # show an "Open" dialog box and return the path to the selected file


# Now change the directory
os.chdir(path)


root = Tk()

root.title('Adding Files')

label = Message( root, text='Do you want to add: \n'+file_name+'?', width=500, font=30)

submit = Button(root, text ='Yes', command = submit)

nosubmit = Button(root, text ='No', command = root.quit)

label.pack()

nosubmit.pack(side=BOTTOM)

submit.pack(side=BOTTOM)


root.mainloop()



