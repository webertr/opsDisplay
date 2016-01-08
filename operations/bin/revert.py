#!/usr/bin/python

import csv
import sys
import os
import time
import pysvn
from Tkinter import *
from tkFileDialog import askopenfilename




path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)



Tk().withdraw() # we don't want a full GUI, so keep the root window from appearing
file_name = askopenfilename(title='Choose a file to Revert: ') # show an "Open" dialog box and return the path to the selected file


root = Tk()


label1 = Label( root, text="What Verson Number ")

E1 = Entry(root, bd =5)


submit = Button(root, text ='Submit', command = root.quit)


label1.pack()
E1.pack()


submit.pack(side=BOTTOM)

root.mainloop()

revnumstr=E1.get()

revnumint=int(revnumstr)

client_svn = pysvn.Client()

log_svn=client_svn.log(file_name)

#print x


rev=log_svn[revnumint].revision


old_file = client_svn.cat(file_name, revision=rev)

text_file = open(file_name, 'w')
text_file.write(old_file)
text_file.close()


#client_svn.merge(file_name, rev1, file_name, rev2, file_name)



