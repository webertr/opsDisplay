#!/bin/bash
##
#
# First the user chooses particle type, this sends different macros to an embedded window
# whos "File Select" button sends difference commands the browser(c-code -- XWIN)
# With the appropriate commands passed, upon file selection the confirm add default window appears.
# Upon confirmation, this script is ran, which copies the selected file into the default directory (pointed to by PVTEMP). 
#
##

#Variable Declarations
ETYPE="CCC:SR:SelectionIndex"
ETYPEN=""
FETCHEDETYPE=""
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
OUTPUT=""
PVTEMP="CCC:SR:temp"
IOCDEBUG="Operations:iocDebugValue"
# set debug default vailue = 1 to get past "entering" 
DEBUG=1
# dryrun will not do anything but only display what it would do
DRYRUN="n"

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
echo $1
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

	return 0
}

echolog "entering $0"

if [ "$DRYRUN" == "y" ]; then 
        echolog "dry run happening"
fi

#Makes sure the command "$CAGET" is available
if [ ! -x ` which caget ` ]; then 
        echolog "cannot run caget" && exit 1
fi
DEBUG=` caget -t $IOCDEBUG `

OUTPUT=` caget -t $ETYPE -t 2>/dev/null `
echolog "ETYPE is $OUTPUT"
if [ $? -ne 0 ];then
	echolog "failed to connect to $ETYPE print not completed" && exit 1
fi

#Stores the value of $ETYPE for comparisons
FETCHEDETYPE=` caget -t $ETYPE | cut -d ' ' -f 1 `
set_etypen $FETCHEDETYPE
echolog "|$ETYPEN|"

OUTPUT=` caget -t  $PVTEMP `
if [ $? -ne 0 ]; then
	echolog "unable to caget $PVTEMP " && exit 1
fi

echolog "output pvtemp: |$OUTPUT|"
if [ "$DRYRUN" == "y" ]; then 
	echolog "caput CCC:OpsDisplay:System:Write Default\ setting\ added:\ $OUTPUT "
else
	caput CCC:OpsDisplay:System:Write Default\ setting\ added:\ $OUTPUT
fi

#Copies the file pointed by the above computations to the associated default subdirectory.	
if [ "$DRYRUN" == "y" ]; then 
	echolog "cp $FPATH/SavedSettings/$ETYPEN/nDefault/$OUTPUT $FPATH/SavedSettings/$ETYPEN/Default/$OUTPUT"
	echolog "cp $FPATH/SavedDescs/$ETYPEN/nDefault/desc.$OUTPUT $FPATH/SavedDescs/$ETYPEN/Default/desc.$OUTPUT" 
else
	cp "$FPATH/SavedSettings/$ETYPEN/nDefault/$OUTPUT" "$FPATH/SavedSettings/$ETYPEN/Default/$OUTPUT"
	cp "$FPATH/SavedDescs/$ETYPEN/nDefault/desc.$OUTPUT" "$FPATH/SavedDescs/$ETYPEN/Default/desc.$OUTPUT" 
fi

echolog "exiting $0"

exit

