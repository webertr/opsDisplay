#!../../bin/linux-x86/opsDisplayIOC

## You may have to change opsDisplay to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}
#This is here so you have time to open the log when rebooting opsIOC
epicsThreadSleep(5)
## Register all support components
dbLoadDatabase("dbd/opsDisplayIOC.dbd")
opsDisplayIOC_registerRecordDeviceDriver(pdbbase)


## Load record instances
dbLoadRecords("db/ew.db")


dbLoadRecords("db/SaveRestore.vdb")

# Load IOC Heartbeat database
dbLoadRecords("db/IocHeartbeat.vdb", "SubSys=Operations")



# Loads the Backend databases for the edm console.
#   they used to be located on tuning (put there by Robert Horax)
#   moved to Operations Terminal IOC (by Mat Hicks August 2009)
#
# This database handles the delay and appendage of user and timestamp to the system log.
dbLoadRecords("db/Ctrl_Console_EDM_Backend/Messaging.db", "SubSys=CCC,Device=OpsDisplay,Queue=System")

dbLoadRecords("db/Ctrl_Console_EDM_Backend/Messaging.db", "SubSys=CCC,Device=OpsDisplay,Queue=Operator")


# This converts the system time into a PV, and stores the currently logged in user.
dbLoadRecords("db/Ctrl_Console_EDM_Backend/Operator.db")

# This converts the system time into a PV, may be a duplicate not needed. 
dbLoadRecords("db/Ctrl_Console_EDM_Backend/System.db")



# Propogates signal indicating new setting has been loaded
dbLoadRecords("db/NewSettingLoaded.vdb")



## Set this to see messages from mySub
#var mySubDebug 1

cd ${TOP}/iocBoot/${IOC}
iocInit()

## Start any sequence programs
#seq opsDisplaySnc,"user=rootHost"
