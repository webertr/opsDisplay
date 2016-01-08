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
DRYRUN="n"
DEBUG=1

if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
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

	#return $ETYPEN
	return $1

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
        echolog "cannot run caput command"  && exit 1
else
        echolog "have caput command"
fi

OUTPUT=` caget -t $ETYPE  2>/dev/null `
if [ $? -ne 0 ];then
	echolog "failed to connect to $ETYPE"
else
	echolog "etype is $OUTPUT"
	set_etypen $OUTPUT
	if [ -f "$FPATH/SavedSettings/$ETYPEN/nDefault/$(caget -t $PVSAVE )" ]; then
  		caput "$PVFEXIST" 1
		echolog "PVFEXIST=1"
	else
  		caput "$PVFEXIST" 0
		echolog "PVFEXIST=0"
	fi
		
	#This part checks to see if the selected file to delete has is also a default setting, if it is it places
	#a 1 into the PV CC:SR:save:defaultexisits otherwise it sticks a 0 into it.
	if [ -f "$FPATH/SavedSettings/$ETYPEN/Default/$(caget -t $PVTEMP )" ]; then
		caput $DEFAULTEXISTS 1
		echolog "$DEFAULTEXISTS 1"
	else
		caput $DEFAULTEXISTS 0
		echolog "$DEFAULTEXISTS 0"
	fi
		
	#This part checks to see if the clipboard file exists, if it does it places a 1 into the PV $CLIPEXISTS
	#otherwise it sticks a 0 into it. 
	if [ -f "$FPATH/clipboard" ]; then
		caput $CLIPEXISTS 1
		echolog "$CLIPEXISTS 1"
	else
		caput $CLIPEXISTS 0
		echolog "$CLIPEXISTS 0"
	fi

fi

exit

