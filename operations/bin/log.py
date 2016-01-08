#!/usr/bin/python

import sys
import os
import time
import pysvn
from Tkinter import Tk, Text, INSERT, END, Button
from tkFileDialog import askopenfilename



path = '/usr/local/cnts/epics/operations/lib/utilities/Settings'

# Now change the directory
os.chdir(path)



Tk().withdraw() # we don't want a full GUI, so keep the root window from appearing
file_name = askopenfilename(title='Choose a file to view log of: ') # show an "Open" dialog box and return the path to the selected file



client_svn = pysvn.Client()



log_svn=client_svn.log(file_name)


root = Tk()

text = Text(root)

Button(root, text="Quit", command=quit).pack()

longstr=''

i=0
for x in log_svn:

    str1='Message: ' + x.message + '\r\n'
    strdate=str(x.revision)
    #str2=strdate.split('number ')[1]
    #str2=str2.split('>')[0]
    str2='Revision: ' + str(i) + '\r\n'
    str3=time.ctime(x.date) + '\r\n'
    longstr=longstr+str2+str3+str1+'\r\n'+'\r\n'+'\r\n'
    i=i+1


text.insert(INSERT, longstr)

text.insert(END, 'Finished\r\n')
text.pack()

#strpath=file_name.split('/lib/')[1]
#strpath='File Name: ' + strpath

#root.title(strpath)



#text.tag_add("here", "1.0", "1.4")
#text.tag_add("start", "1.8", "1.13")
#text.tag_config("here", background="yellow", foreground="blue")
#text.tag_config("start", background="black", foreground="green")

root.mainloop()




