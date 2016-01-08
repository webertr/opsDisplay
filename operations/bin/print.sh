#!/bin/bash
##
#
# First the user chooses particle type, this sends different macros to an embedded window
# whos "File Select" button sends difference commands the browser(c-code -- XWIN)
# With the appropriate commands passed, upon file selection the confirm print window appears.
# Upon confirmation, this script is ran, which prints the selected file (pointed to by PVTEMP). 
#
##

#Variable Declarations
ETYPE="CCC:SR:SelectionIndex"
ETYPEN=""
FETCHEDETYPE=""
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
OUTPUT=""
DEFAULTPV="CCC:SR:save:morns"
DEFAULTN=""
FETCHEDDEFAULT=""
PVTEMP="CCC:SR:temp"
#DRYRUN=y
DRYRUN=n
IOCDEBUG="Operations:iocDebugValue"
DEBUG=1
if [ -f ./functions.sh ]; then
	. ./functions.sh
fi
#
echolog(){
        if [ "$DEBUG" -ne 0 ]; then
                echo $1
                logger -i $1
        fi
}


set_etypen(){
echolog $1
	#Stores the value of $ETYPE for comparisons
	#This is an analog enumerated value that the user selects using radio-like buttons,
	#it is enumerated such that:
	#		
	#	1 = Proton 
	#	2 = H2+
	#	3 = Deuteron
	#	4 = He3
	#	5 = Alpha
	#
	#The energy type is used to determine which subdirectory to save the setting in,
	#all saved settings are saved in the 'energy type' then "nDefault" subdirectories.
	case "$1" in
	1*)
		ETYPEN="Proton"
		;;
	2*)
		ETYPEN="H2+"
		;;
	3*)
		ETYPEN="Deuteron"
		;;
	4*)
		ETYPEN="Helium3"
		;;
	5*)
		ETYPEN="Alpha"
		;;
	esac

	return $ETYPEN

}


if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
	. /usr/local/cnts/epics/base/startup/Site.bashrc
fi 

echolog "entering $0"

#Makes sure the command "caget" is available	
if [ ! -x ` which caget ` ]; then
	echolog "cannot run caget"  && exit 1
fi


#Makes sure a value can be fetched from the PV $DEFAULTPV, if not doesn't print
OUTPUT=` caget -t $DEFAULTPV 2>/dev/null `
if [ $? -ne 0 ];then
	echolog "failed to connect to $DEFAULTPV   print not completed"  && exit 1
fi
DEBUG=` caget -t $IOCDEBUG `

#Stores the value of $DEFAULTPV for comparisons
#This is an analog enumerated value that the user selects using a checkbox-like button,
#it is enumerated such that:
#
#	1 = Default
#	0 = nDefault
#
#The default is used to determine which subdirectory inside the energy subdirectory to 
#look for the setting in.	
FETCHEDDEFAULT=` caget -t $DEFAULTPV `
echolog "$FETCHEDDEFAULT is fetcheddefault"
if [ $FETCHEDDEFAULT == 1 ];then
	DEFAULTN="Default"
else
	DEFAULTN="nDefault"
fi
echolog "defaultN is $DEFAULTN" 

#Makes sure a value can be fetched from the PV $ETYPE, if not doesn't print			
FETCHEDETYPE=` caget -t $ETYPE | cut -d ' ' -f 1`
if [ $? -ne 0 ];then
	echolog "failed to connect to $ETYPE print not completed"  && exit 1
fi

#Stores the value of $ETYPE for comparisons
echolog "fetchedetype is $FETCHEDETYPE"
set_etypen $FETCHEDETYPE
echolog "|$ETYPEN|"

OUTPUT=` caget -t $PVTEMP `
echolog "$OUTPUT from $PVTEMP"
if [ "$DRYRUN" == "y" ]; then
	echolog "caput CCC:OpsDisplay:System:Write Printing:\ $OUTPUT "
	#echolog "cat \"$FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT\" to  lpr ps143e "
        echolog "/usr/local/cnts/epics/operations/bin/print.py $ETYPEN $DEFAULTN $OUTPUT | enscript -d ps143e "
else
	caput CCC:OpsDisplay:System:Write Printing:\ $OUTPUT
	#Sends the file pointed by the above computations to the printer.		
	##cat "$FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT" | lp -d ps143e
        /usr/local/cnts/epics/operations/bin/print.py $ETYPEN $DEFAULTN $OUTPUT | enscript -d ps143e 
        #/usr/local/cnts/epics/operations/bin/print.py $ETYPEN $DEFAULTN $OUTPUT 
fi

echolog "exiting $0"
exit 

