#!/bin/bash

PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11

if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

OUTPUT=""
PVSTOREDTIME="CCC:SR:clip:storedtime"
PVSYSTIME="CCC:OpsDisplay:Operator:TimeStamp"
FPATH="/usr/local/cnts/epics/operations/var/SnapShot"
CLIPBOARD="clipboard"
REQUESTFILE="Cyclotron.request"
DRYRUN="n"
DEBUG=1

# REQUESTFILE is now under RPATH, different from FPATH
RPATH="/usr/local/cnts/epics/operations/lib/SnapShot"

echolog(){
        if [ "$DEBUG" -ne 0 ]; then
                echo $1
                logger -i $1
        fi
}

log_and_exit(){
	echolog $1
	echolog "clipsave could not complete"
	exit 1
}

echolog "entering $0"

if [ ! -f $RPATH/$REQUESTFILE ]; then
	log_and_exit "no request file found at $RPATH/$REQUESTFILE"
fi
echolog " found $RPATH/$REQUESTFILE"

if [ ! -x ` which caget ` ];then
	log_and_exit "cannot run caget"
fi
echolog "have caget "

if [ ! -x ` which casave ` ];then
	log_and_exit "cannot run casave"
fi
echolog "have casave "

echolog "testing caput"
if [  ! -x ` which caput ` ];then
	log_and_exit "cannot run caput"
fi
echolog "have caput"

OUTPUT=` caget -t $PVSTOREDTIME 2>/dev/null `
if [ $? -ne 0 ];then
	log_and_exit "Warning, failed to connect to $PVSTOREDTIME"
fi

OUTPUT=` caget -t $PVSYSTIME 2>/dev/null `
if [ $? -ne 0 ];then
	log_and_exit "Warning, failed to connect to $PVSYSTIME"
fi

casave -asciiin $RPATH/$REQUESTFILE -asciiout $FPATH/$CLIPBOARD
if [ $? -ne 0 ]; then
	log_and_exit "failed to CAsave clipboard"
fi

echolog "clipsave complete"
caput CCC:OpsDisplay:System:Write Clipboard\ save\ completed
caput $PVSTOREDTIME $(caget -t $PVSYSTIME )

exit

