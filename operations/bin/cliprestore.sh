#! /bin/sh

PATH=/usr/local/bin:/usr/bin:/bin:/usr/bin/X11

if [ -f /usr/local/cnts/epics/base/startup/Site.bashrc ]; then
  . /usr/local/cnts/epics/base/startup/Site.bashrc
fi

echolog(){
        if [ "$DEBUG" -ne 0 ]; then
                echo $1
                logger -i $1
        fi
}

FPATH="/usr/local/cnts/epics/operations/var/SnapShot"

OUTPUT=""
DEBUG=1
DRYRUN="n"

if [ -x ` which carestore ` ]; then
	if [ -f "$FPATH/clipboard" ];then
		carestore -asciiin "$FPATH/clipboard"
		echolog "cliprestore complete"
		caput CCC:OpsDisplay:System:Write "Clipboard restore completed"
	else 
		echolog "no clipboard file"
	fi
else
	echolog "cannot run carestore, restore operation failed"
fi
exit

