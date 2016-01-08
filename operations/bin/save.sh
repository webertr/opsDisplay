#!/bin/bash
##
# When the user chooses to save a file this script is run. It takes the particle type
# enumerated in PV CCC:SR:save:etype to determine which directory it should be saved in.
#
# Changing the "CCC:SR:save:etype" PV to "CCC:SR:ParticleType"
#
# Adding Energy Setting
##


#Variables used
JUNK=""
OUTPUT=""
PVSAVE="CCC:SR:save"
PVDESC="CCC:SR:save:desc"
REQUESTFILE="Cyclotron.request"
ETYPE="CCC:SR:ParticleTypeStored"
ENERGY="CCC:SR:EnergySetting"
ENERGYUNIT="CCC:SR:EnergySetting.EGU"
TIMESTAMP="CCC:OpsDisplay:Operator:TimeStamp"
ETYPEN=""
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
FETCHEDETYPE=""
FETCHEDENERGY=""
FETCHEDUNIT=""
CAGET=` which caget `
IOCDEBUG="Operations:iocDebugValue"
# set debug default vailue = 1 to get past "entering" 
DEBUG=1
# dryrun will not do anything but only display what it would do
#DRYRUN="y"
DRYRUN="n"

# REQUESTFILE is now under RPATH, different from FPATH
RPATH="/usr/local/cnts/epics/operations/lib/SnapShot"

#Makes sure the Epics libraries are available for Channel Access commands
PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11
if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

if [ -f ./functions.sh ]; then
	. ./functions.sh
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
echolog "entering $0"

if [ "$DRYRUN" == "y" ]; then 
        echolog "dry run happening"
fi

#Makes sure the command "$CAGET" is available
if [ ! -x ` which caget ` ]; then 
	echolog "cannot run $CAGET" && exit 1
fi
DEBUG=` caget -t $IOCDEBUG `

if [ ! -x ` which caput ` ]; then
	echolog "cannot run caput command" && exit 1
fi

#Makes sure the request file (a list of PVs) exists, if it doesn't it wont try to save
if [ ! -f "$RPATH/$REQUESTFILE" ]; then 
	echolog "no request file found at $RPATH/$REQUESTFILE" && exit 1
fi

#Makes sure a value can be fetched from the PV $PVSAVE, if not doesn't save
JUNK=` $CAGET -t $PVSAVE  2>/dev/null `
if [ $? -ne 0 ];then 
	echolog "failed to connect to $PVSAVE save not completed" && exit 1
fi

#Makes sure $ETYPE is avaiable, if not doesn't save 
JUNK=` $CAGET -t $ETYPE  2>/dev/null `
if [ $? -ne 0 ];then
	echolog "failed to connect to $ETYPE save not completed" && exit 1
fi

#Store the value of $ETYPE for comparisons
#The energy type is used to determine which subdirectory to save the setting in,
#all saved settings are saved in the 'particle type' then "nDefault" subdirectories.
FETCHEDETYPE=` $CAGET -t $ETYPE | cut -d ' ' -f 1 `
if [ ! -x ` which casave ` ]; then
	echolog "could not run casave" && exit 1
fi

echolog "$FETCHEDETYPE is fetched etype"
set_etypen $FETCHEDETYPE
echolog "|$ETYPEN|"


#Get the energy setting
FETCHEDENERGY=` $CAGET -t -s $ENERGY | cut -d ' ' -f 1 `
echolog "FETCHEDENERGY = |$FETCHEDENERGY|"
#Get the energy units
FETCHEDUNIT=` $CAGET -t $ENERGYUNIT | cut -d ' ' -f 1 `
echolog "ENERGYUNIT: |$FETCHEDUNIT|"

if [ $FETCHEDENERGY == 0 ]; then
	echolog "Enter Energy Setting before saving...."
	if [ "$DRYRUN" == "y" ]; then 
		echolog	"caput CCC:OpsDisplay:System:Write Enter\ Energy\ Setting\ before\ saving "
	else
		caput CCC:OpsDisplay:System:Write Enter\ Energy\ Setting\ before\ saving 
	fi
else
	#Actual save line, stores it in a simple text ascii file.
	OUTPUT=` $CAGET -t $PVSAVE `
	echolog "$OUTPUT is caget output of $PVSAVE"
	CURRENTTIME=` $CAGET -t $TIMESTAMP |  awk '{print $2;}'`
	echolog "$CURRENTTIME is caget output of $TIMESTAMP"

	OUTPUT=` echo $OUTPUT| tr '\ ' '_'  `
	echolog "$OUTPUT is rewritten version of OUTPUT "
	OUTPUT=` echo $OUTPUT $CURRENTTIME | awk '{printf("%s_%s", $1, $2);}' `
	echolog "$OUTPUT is rewritten version of OUTPUT "
	echolog "line 158"
	ENERGYSTAMP=` echo $FETCHEDENERGY $FETCHEDUNIT | awk '{printf("%s_%s", $1, $2);}' `
	echolog "$ENERGYSTAMP is rewritten version of ENERGYSTAMP "

	if [ "$DRYRUN" == "y" ]; then 
		#echolog "casave -asciiin $RPATH/$REQUESTFILE -asciiout $FPATH/SavedSettings/$ETYPEN/nDefault/$ETYPEN:$FETCHEDENERGY$FETCHEDUNIT:$OUTPUT"
#		echolog "casave $ETYPEN:$FETCHEDENERGY$FETCHEDUNIT:$OUTPUT    line 162"
		echolog "casave $ETYPEN:$ENERGYSTAMP:$OUTPUT    line 162"
	else
#		casave -asciiin "$RPATH/$REQUESTFILE -asciiout $FPATH/SavedSettings/$ETYPEN/nDefault/$ETYPEN:$FETCHEDENERGY$FETCHEDUNIT:$OUTPUT"
#		casave -asciiin $RPATH/$REQUESTFILE -asciiout $FPATH/SavedSettings/$ETYPEN/nDefault/$ETYPEN:$FETCHEDENERGY$FETCHEDUNIT:$OUTPUT
		casave -asciiin $RPATH/$REQUESTFILE -asciiout $FPATH/SavedSettings/$ETYPEN/nDefault/$ETYPEN:$ENERGYSTAMP:$OUTPUT
	fi
					
	#Posts a message to the system log indicating save completed					
	if [ "$DRYRUN" == "y" ]; then 
		echolog "caput CCC:OpsDisplay:System:Write Setting\ saved\ $OUTPUT  line 170"
	else
		caput CCC:OpsDisplay:System:Write Setting\ saved\ $OUTPUT 
	fi

	#Saves the associated description file in a a parallel directory structure
	echolog "line 176"
	JUNK=` caget -t $PVDESC 2>/dev/null `
	echolog "line 178"
	if [ $? -ne 0 ];then
		echolog "failed to connect to $PVDESC and description not saved    line 180" && exit 1
	else
		if [ "$DRYRUN" == "y" ]; then 
			echolog "$JUNK is caget output at line 182"
		else
#			caget -t $PVDESC  >"$FPATH/SavedDescs/$ETYPEN/nDefault/desc.$ETYPEN:$FETCHEDENERGY$FETCHEDUNIT:$OUTPUT"
			caget -t $PVDESC  >"$FPATH/SavedDescs/$ETYPEN/nDefault/desc.$ETYPEN:$ENERGYSTAMP:$OUTPUT"
		fi
	fi
fi

echolog "exiting $0"
exit


