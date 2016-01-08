#!/usr/bin/env python

import sys
import string

settingsPath="/usr/local/cnts/epics/operations/var/SnapShot/SavedSettings/"
descriptionPath="/usr/local/cnts/epics/operations/var/SnapShot/SavedDescs/"

# arg  is  particle type
# arg 2 is Default or NDefault
# arg 3 is file  PVTEMP

eType = sys.argv[1]
defaultOrNot = sys.argv[2]
targetFileName = sys.argv[3]

print targetFileName
print defaultOrNot

fullDescPath = descriptionPath + eType + '/' + defaultOrNot + '/desc.' + targetFileName
fullSettingsPath = settingsPath + eType + '/' + defaultOrNot + '/' + targetFileName

dFile = open(fullDescPath,'r')
sFile = open(fullSettingsPath,'r')

print "Description:\t" +  dFile.read()
dFile.close()

dLine = ""

def process(line):
	pvLine = string.split(line,"{")
	pvName = pvLine[0]
	if len(pvLine) > 2:
		pvRest = pvLine[1]
		pvData = pvLine[3]
		data = string.split(pvData,"}")[0]
	if len(pvLine) <= 2:
		print pvName.ljust(30),
	else:
		print pvName.ljust(30) + data.rjust(10)

# ignore the top part of the file
for index in range(1,13):
	sFile.readline(),

# read in file line by line, split it up and print it out
for line in sFile:
	# eliminates the final curly brace in the file
	if line == "}\n":
		line = ""
	if line == "  \n":
		line = ""
		break

        if line.find("VAL") != -1:
                process(line)
        if line.find("Set") != -1:
                process(line)


sFile.close()

