#!/bin/bash
##
#
# First the user chooses particle type, this sends different macros to an embedded window
# whos "File Select" button sends difference commands the browser(c-code -- XWIN)
# With the appropriate commands passed, upon file selection the confirm print window appears.
# Upon confirmation, this script is ran, which prints the selected file (pointed to by PVTEMP). 
#
##

FPATH="/usr/local/cnts/epics/operations/var/log/system"

#Writes to the system log that the system log is printing.	
caput CCC:OpsDisplay:System:Write Printing\ System\ Log
#Sends the file pointed by the above computations to the printer.		
#cat "$FPATH/temp.log" | lp -d ps143e
cat "$FPATH/temp.log" | enscript -d ps143e


