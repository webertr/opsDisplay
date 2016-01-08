#!/usr/bin/python

import sys
import time
import pysvn
from Tkinter import *



client_svn = pysvn.Client()

root = Tk()
text = Text(root)

Button(root, text="Quit", command=quit).pack()

stat_svn=client_svn.status('/usr/local/cnts/epics/operations/lib/utilities/Settings')


root.title('Files Status')


cln=0

for x in stat_svn:

    if x.text_status == pysvn.wc_status_kind.modified:
        cln=1
        strpath=str(x.path)
        strpath=strpath.split('/lib/')[1]
        stradd='need to commit:  '+strpath+'\r\n'
        text.insert(INSERT, stradd)

    if x.text_status == pysvn.wc_status_kind.added:
        cln=1
        strpath=str(x.path)
        strpath=strpath.split('/lib/')[1]
        stradd='need to commit:  '+strpath+'\r\n'
        text.insert(INSERT, stradd)

    if x.text_status ==  pysvn.wc_status_kind.unversioned:
        cln=1
        strpath=str(x.path)
        strpath=strpath.split('/lib/')[1]
        stradd='need to add:  ' + strpath+'\r\n'
        text.insert(INSERT, stradd)


if cln==0:
    text.insert(END, 'Everything is up to date\r\n')
else:
    text.insert(END, 'End of log\r\n')


text.pack()

root.mainloop()



   



