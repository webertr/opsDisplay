#!/usr/bin/python

import csv
import sys
import os
import time
import pysvn
from Tkinter import *
from tkFileDialog import askopenfilename



def submit():

    global logmsg
    global file_name
    logmsg=text.get(1.0,END)
    client_svn = pysvn.Client()
    client_svn.checkin(file_name, logmsg)
    root.quit()



path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)



Tk().withdraw() # we don't want a full GUI, so keep the root window from appearing
file_name = askopenfilename(title='Choose a file to Commit: ') # show an "Open" dialog box and return the path to the selected file


root = Tk()

root.title('Log Message: ')

text = Text(root)

submit = Button(root, text ='Submit', command = submit)

text.pack()

submit.pack(side=BOTTOM)

root.mainloop()
