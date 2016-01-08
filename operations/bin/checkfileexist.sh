#!/bin/bash


ETYPE="CCC:SR:SelectionIndex"
ETYPEN=""
PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
PVSAVE="CCC:SR:save"
PVFEXIST="CCC:SR:save:fileexists"
DEFAULTEXISTS="CCC:SR:save:defaultexists"
OUTPUT=""
PVTEMP="CCC:SR:temp"
CLIPEXISTS="CCC:SR:clipboardexists"
IOCDEBUG="Operations:iocDebugValue"
# set debug default vailue = 1 to get past "entering" 
DEBUG=1
# dryrun will not do anything but only display what it would do
#DRYRUN="y"
DRYRUN="n"

if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

echolog(){
	if [ "$DEBUG" -ne 0 ]; then
		echo $1
		logger -i $1
	fi
}

echolog "entering $0"

if [ "$DRYRUN" == "y" ]; then 
	echolog "dry run happening"
fi

if [ ! -x ` which caget ` ]; then
	echolog "cannot run caget command"  && exit 1
else
    	echolog "have caget command"
fi
DEBUG=` caget -t $IOCDEBUG `

if [ ! -x ` which caput ` ]; then
    	echolog "cannot run caput command" && exit 1
else
    	echolog "have caput command"
fi

#exit 1

OUTPUT=` caget -t $ETYPE 2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "failed to connect to $ETYPE" && exit 1
else
	echolog "setting ETYPEN"
	echolog "OUTPUT is $OUTPUT"
	case "$OUTPUT" in
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
	echolog "ETYPEN is set to $ETYPEN"

	VALTOPUT=0
	FILENAME=` caget -t $PVSAVE `
	echolog "testing existence of PVSAVE file $FILENAME "
	if [ -f "$FPATH/SavedSettings/$ETYPEN/nDefault/$FILENAME" ]; then
		VALTOPUT=1
ls -la  "$FPATH/SavedSettings/$ETYPEN/nDefault/$FILENAME"
	else
		VALTOPUT=0
	fi
	if [ "$DRYRUN" == "y" ]; then 
		echolog "OUTPUT = caput $PVFEXIST $VALTOPUT "
	else
		OUTPUT=` caput $PVFEXIST $VALTOPUT `
		if [ $? -ne 0 ]; then
			echolog "failed to caput $VALTOPUT to $PVFEXIST with output"
			echolog "$OUTPUT"
		fi
	fi

	#This part checks to see if the selected file to delete has is also a default setting, if it is it places
	#a 1 into the PV CC:SR:save:defaultexisits otherwise it sticks a 0 into it.
	VALTOPUT=1
	FILENAME=` caget -t $PVTEMP `
	echolog "testing existence of PVTEMP file $FILENAME "
	if [ -f "$FPATH/SavedSettings/$ETYPEN/Default/$FILENAME" ]; then
		VALTOPUT=1
ls -la  "$FPATH/SavedSettings/$ETYPEN/Default/$FILENAME"
	else
		VALTOPUT=0
	fi
	if [ "$DRYRUN" == "y" ]; then 
		echolog "OUTPUT = caput $DEFAULTEXISTS $VALTOPUT "
	else
		OUTPUT=` caput $DEFAULTEXISTS $VALTOPUT `
		if [ $? -ne 0 ]; then
			echolog "failed to caput $VALTOPUT to $DEFAULTEXISTS with output"
			echolog "$OUTPUT"
		fi
	fi

	#This part checks to see if the clipboard file exists, if it does it places a 1 into the PV $CLIPEXISTS
	#otherwise it sticks a 0 into it. 
	VALTOPUT=1
	if [ -f "$FPATH/clipboard" ]; then
		VALTOPUT=1
	else
		VALTOPUT=0
	fi
	if [ "$DRYRUN" == "y" ]; then 
		echolog "OUTPUT = caput $CLIPEXISTS $VALTOPUT "
	else
		OUTPUT=` caput $CLIPEXISTS $VALTOPUT `
		if [ $? -ne 0 ]; then
			echolog "failed to caput $VALTOPUT to $CLIPEXISTS with output"
			echolog "$OUTPUT"
		fi
	fi
fi

echolog "exiting $0"
exit
