#!/bin/bash
##
#
# First the user chooses particle type, this sends different macros to an embedded window
# whos "File Select" button sends difference commands the browser(c-code -- XWIN)
# With the appropriate commands passed, upon file selection the confirm delete window appears.
# Upon confirmation, this script is ran, which deletes the selected file (pointed to by PVTEMP). 
#
##

PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11

echo "in RemoveDefault2"
#Variable Declarations
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
OUTPUT=""
PVTEMP="CCC:SR:temp"
ETYPE="CCC:SR:SelectionIndex"
ETYPEN=""
FETCHEDETYPE=""
DEBUG=1
#DRYRUN="y"
DRYRUN="n"
IOCDEBUG="Operations:iocDebugValue"

#Makes sure the Epics libraries are available for Channel Access commands
PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11
if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

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

	return $ETYPN

}

echolog "entering $0"

#Makes sure the command "caget" is available	
if [ ! -x ` which caget ` ]; then
	echolog "cannot run caget" && exit 1
fi
DEBUG=` caget -t $IOCDEBUG `

if [ ! -x ` which caput ` ]; then
	echolog "cannot run caput" && exit 1
fi

#Makes sure a value can be fetched from the PV $PVTEMP, if not doesn't delete anything	
OUTPUT=` caget -t $PVTEMP -t 2>/dev/null `
if [ $? -ne 0 ];then
	echolog  "failed to connect to $PVTEMP, delete operation not completed" && exit 1
fi

#Makes sure a value can be fetched from the PV $ETYPE, to determine energy subdirectory
FETCHEDETYPE=` caget -t $ETYPE 2>/dev/null `
if [ $? -ne 0 ];then
	echo "failed to connect to $ETYPE deletion not completed"  && exit 1
fi

#Store the value of $ETYPE for comparisons
set_etypen $FETCHEDETYPE
echolog "|$ETYPEN|"

#This part uses the above directory and file pointer information to delete
#the appropriate file and its associated description.
OUTPUT=` caget -t $PVTEMP `
echolog "pvtemp value is $OUTPUT"
if [ -f "$FPATH/SavedDescs/$ETYPEN/Default/desc.$OUTPUT" ];then
	if [ "$DRYRUN" == "y" ]; then
		echolog "rm $FPATH/SavedDescs/$ETYPEN/Default/desc.$OUTPUT"
	else
		rm "$FPATH/SavedDescs/$ETYPEN/Default/desc.$OUTPUT"
	fi
	echolog "description file deleted"
fi

if [ -f "$FPATH/SavedSettings/$ETYPEN/Default/$OUTPUT" ];then
	if [ "$DRYRUN" == "y" ]; then
		echolog "rm $FPATH/SavedSettings/$ETYPEN/Default/$OUTPUT"
		echolog	"caput CCC:OpsDisplay:System:Write Default\ setting\ deleted:\ $OUTPUT"
	else
		rm "$FPATH/SavedSettings/$ETYPEN/Default/$OUTPUT"
		caput CCC:OpsDisplay:System:Write Default\ setting\ deleted:\ $OUTPUT 
	fi
	echolog "saved setting $OUTPUT deleted"
fi

echolog "exiting $0"
exit

