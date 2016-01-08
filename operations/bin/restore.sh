#!/bin/bash
##
#
# First the user chooses particle type, this sends different macros to an embedded window
# whos "File Select" button sends difference commands the browser(c-code -- XWIN)
# With the appropriate commands passed, upon file selection the confirm restore window appears.
# Upon confirmation, this script is ran, which restores the selected file (pointed to by PVTEMP). 
#
# 05may2010 - Modified to accomodate the new particle type 	ddr
# 27jul2010 - Modified to check machine state before doing 
#	      the restore operation
##

PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11

#Variable Declarations
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
OUTPUT=""
TMPOUTPUT=""
PVCURLOADTIME="CCC:SR:current:loadedtime"
PVTEMPTIME="CCC:OpsDisplay:Operator:TimeStamp"
PVCUR="CCC:SR:current"
PVCURMAKEUSER="CCC:SR:current:makeuser"
PVTEMPMAKEUSER="CCC:SR:temp:makeuser"
PVCURMAKEDATE="CCC:SR:current:makedate"
PVTEMPMAKEDATE="CCC:SR:temp:makedate"
PVCURDESC="CCC:SR:current:desc"
PVTEMP="CCC:SR:temp"
ETYPE="CCC:SR:SelectionIndex"
ETYPEN=""
FETCHEDETYPE=""
DEFAULTPV="CCC:SR:save:morns"
DEFAULTN=""
FETCHEDDEFAULT=""
MACHINESTATE="RF:HighPowerOn:Status"
FETCHEDSTATE=""
#DRYRUN="y"
DRYRUN="n"
DEBUG=1
IOCDEBUG="Operations:iocDebugValue"

if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

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


if [ -f ./functions.sh ]; then
  . ./functions.sh
fi


#Makes sure the command "caget" is available	
if [ ! -x ` which caget ` ]; then
	echolog "cannot run caget, restore operation failed"  && exit 1
fi
DEBUG=` caget -t $IOCDEBUG `
echolog "entering $0"

#Makes sure a value can be fetched from the PV $PVTEMP, if not doesn't restore
OUTPUT=` caget -t $PVTEMP  2>/dev/null `
if [ $? -ne 0 ];then
	echolog "failed to connect to $PVTEMP, restore operation not completed" && exit 1
fi

#Makes sure a value can be fetched from the PV $DEFAULTPV, if not doesn't restore
OUTPUT=` caget -t $DEFAULTPV  2>/dev/null `
if [ $? -ne 0 ];then
	echolog  "failed to connect to $DEFAULTPV deletion not completed" && exit 1
fi

#Stores the value of $DEFAULTPV for comparisons
#This is an analog enumerated value that the user selects using a checkbox-like button,
#it is enumerated such that:
#	1 = Default
#	0 = nDefault
#The default is used to determine which subdirectory inside the energy subdirectory to 
#look for the setting in.	
FETCHEDDEFAULT=` caget -t $DEFAULTPV `
if [ $FETCHEDDEFAULT == 1 ];then
	DEFAULTN="Default"
else
	DEFAULTN="nDefault"
fi

#Makes sure a value can be fetched from the PV $ETYPE, if not doesn't restore	
FETCHEDETYPE=` caget -t $ETYPE 2>/dev/null `
if [ $? -ne 0 ];then
	logger -i "failed to connect to $ETYPE deletion not completed" && exit 1
fi
echolog "fetched etype is $FETCHEDETYPE"

#Store the value of $ETYPE for comparisons
set_etypen $FETCHEDETYPE
echolog "|$ETYPEN|"
		
#This part checks to see if the file exists
OUTPUT=` caget -t $PVTEMP `

echolog "$OUTPUT is pvtemp val"
echolog "$FPATH is fpath"
echolog "$DEFAULTN is defaultn"
echolog "$FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT  is output path"

if [ ! -f "$FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT" ]; then
	echolog "no file $FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT  restore operation failed" && exit 1
fi

#Makes sure the command 'carestore' exists
if [ ! -x ` which carestore ` ]; then
	echolog "cannot run carestore, restore operation failed"  && exit 1
fi

#Show that restore has started
#Restores the setting
if [ "$DRYRUN" == "y" ]; then
	echolog "caput CCC:OpsDisplay:System:Write Saved\ Settings\ Being\ Loaded  "
	echolog "carestore -asciiin $FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT"
else
	caput CCC:OpsDisplay:System:Write Saved\ Settings\ Being\ Loaded
	caput CCC:NewSettingLoaded.PROC 1
	carestore -asciiin "$FPATH/SavedSettings/$ETYPEN/$DEFAULTN/$OUTPUT"
fi


#Updates the current setting time status display information
TMPOUTPUT=` caget -t $PVCURLOADTIME 2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "Warning, failed to connect to $PVCURLOADTIME"
else
	TMPOUTPUT=` caget -t $PVTEMPTIME  2>/dev/null `
	if [ $? -ne 0 ]; then
		echolog "Warning, failed to connect to $PVTEMPTIME"
	else
		if [ "$DRYRUN" == "y" ]; then
			echolog "caput $PVCURLOADTIME $(caget -t $PVTEMPTIME ) "
		else
			caput $PVCURLOADTIME $(caget -t $PVTEMPTIME )
		fi
	fi
fi

#Updates the current setting status display information
TMPOUTPUT=` caget -t $PVCUR  2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "Warning, failed to connect to $PVCUR"
else
	if [ "$DRYRUN" == "y" ]; then
		echolog "caput $PVCUR $(caget -t $PVTEMP ) "
	else
		caput $PVCUR $(caget -t $PVTEMP )
	fi
fi

#Updates the current setting user status display information
TMPOUTPUT=` caget -t $PVCURMAKEUSER 2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "Warning, failed to connect to $PVCURMAKEUSER"
else
	TMPOUTPUT=` caget -t $PVTEMPMAKEUSER  2>/dev/null `
	if [ $? -ne 0 ]; then
		echolog "Warning, failed to connect to $PVTEMPMAKEUSER"
	else
		if [ "$DRYRUN" == "y" ]; then
			echolog "caput $PVCURMAKEUSER $(caget -t $PVTEMPMAKEUSER ) "
		else
			caput $PVCURMAKEUSER $(caget -t $PVTEMPMAKEUSER )
		fi
	fi
fi

#Updates the current setting makedate status display information
TMPOUTPUT=` caget -t $PVCURMAKEDATE  2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "Warning, failed to connect to $PVCURMAKEDATE"
else
	TMPOUTPUT=` caget -t $PVTEMPMAKEDATE  2>/dev/null `
	if [ $? -ne 0 ]; then
		echolog "Warning, failed to connect to $PVTEMPMAKEDATE"
	else
		if [ "$DRYRUN" == "y" ]; then
			echolog "caput $PVCURMAKEDATE $(caget -t $PVTEMPMAKEDATE ) "
		else
			caput $PVCURMAKEDATE $(caget -t $PVTEMPMAKEDATE )
		fi
	fi
fi

#Updates the current setting description status display information
#from the description file 
TMPOUTPUT=` caget -t $PVCURDESC 2>/dev/null `
if [ $? -ne 0 ]; then
	echolog "Warning, failed to connect to $PVCURDESC"
else
	if [ -f "$FPATH/SavedDescs/$ETYPEN/$DEFAULTN/desc.$OUTPUT" ]; then
		if [ "$DRYRUN" == "y" ]; then
			echolog "caput $PVCURDESC $( <$FPATH/SavedDescs/$ETYPEN/$DEFAULTN/desc.$OUTPUT) "
		else
			caput $PVCURDESC $( <$FPATH/SavedDescs/$ETYPEN/$DEFAULTN/desc.$OUTPUT)
		fi
	else
		echolog "Warning, no description file for $FPATH/StoredSettings/$OUTPUT"
	fi
fi

#writes to system log that restore was sucessful
if [ "$DRYRUN" == "y" ]; then
	echolog "caput CCC:OpsDisplay:System:Write Restore\ completed:\ $OUTPUT "
	echolog "caput NewSettingSeq.PROC 1"
else
	caput CCC:OpsDisplay:System:Write Restore\ completed:\ $OUTPUT
	#Processes record in NewSettingLoaded.vdb on Operations-console
	#This will in turn process records to take required action after a 
	#new setting has been loaded
fi

echolog "Restore operation complete."

echolog "exiting $0"
exit
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

