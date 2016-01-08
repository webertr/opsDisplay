TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

PROD_IOC = opsDisplayIOC
DBD = opsDisplayIOC.dbd

opsDisplayIOC_DBD += commonInclude.dbd

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
opsDisplayIOC_SRCS += opsDisplayIOC_registerRecordDeviceDriver.cpp
opsDisplayIOC_SRCS += opsDisplayIOCMain.cpp

opsDisplayIOC_LIBS += asyn calc sscan modbus seq stream

#===========================

opsDisplayIOC_LIBS += $(EPICS_BASE_IOC_LIBS)
#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
