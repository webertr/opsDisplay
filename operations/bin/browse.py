#!/usr/bin/python
"""
Python replacement for opsDisplay/src/browse3.c
Two options: no graphics, just print on / read from console 
 OR if any sys.argv[4] present, use PyQt GUI
"""
import sys, os, stat, re, datetime, time, subprocess
from epics import caput, caget

#print 'entering browse.py' # DEBUG
particle, subdir, action =  sys.argv[1], sys.argv[2], sys.argv[3]
#print particle, subdir, action  # DEBUG - progress message

# provide any fourth arg to run the qtbrowse demo
qt = bool(len(sys.argv) > 4)
if qt:
    import qtbrowse

# get list of file names 
# docs.python.org on os.listdir: "The list is in arbitrary order"
datapath = '/usr/local/cnts/epics/operations/var/SnapShot' # absolute path OK here
settingpath = '%s/SavedSettings/%s/%s/' % (datapath, particle, subdir)
descpath = '%s/SavedDescs/%s/%s/' % (datapath, particle, subdir)
try:
    fnraw = os.listdir(settingpath) 
except OSError:
    fnraw = list()
fnames = [ fn for fn in fnraw if 
           stat.S_ISREG(os.stat('%s/%s' % (settingpath,fn)).st_mode) ] # exclude dirs etc.

# look up description in another file
def desc(fname):
    try:
        fd = open('%s/desc.%s' % (descpath, fname))
    except IOError: # desc. file might be missing
        fd = None
    return fd.read().rstrip('\n') if fd else ''

# extract operator name and timestamp from the file
# handle both in one function so we read the file just once
reoper = r'Logonid{"(.*)"}'   # Logonid{"dorman (Eric Dorman,,,)"}
retime = r'TimeStamp{"(.*)"}' # TimeStamp{"Fri Jan 27 12:56:18 2012 "}

def oper_time(fname):
    contents = open('%s/%s' % (settingpath, fname)).read()
    moper = re.search(reoper, contents)
    oper = moper.group(1) # 'dorman (Eric Dorman,,,)'
    mtime = re.search(retime, contents)
    datetime = mtime.group(1) # 'Fri Jan 27 12:56:18 2012 '
    return oper, datetime

# collect the data
finfo = [ (fname, desc(fname), oper_time(fname)) for fname in fnames ]

# functions for key argument in sorted function
def identity(finfo): finfo  # just a placeholder

def fyear(finfo):
    fname, desc, op_time = finfo
    oper, datetime = op_time
    return datetime.strip().split()[-1]

def fdate(finfo): 
    fname, desc, op_time = finfo
    oper, datetime = op_time
    # datetime example: 'Wed May 12 15:07:34 2010 '
    dt = datetime.strip().split()
    year, month, day, hour =  \
        (dt[4], time.strptime(dt[1],'%b').tm_mon, int(dt[2]), dt[3]) \
        if len(dt) > 4 else '','','',''
    return year, month, day, hour

def particle_energy_date(finfo):
    # assumes fname has form particle:energy:...
    fname, desc, op_time = finfo
    pe_list = fname.split(':')[:2]
    particle, energy = pe_list if len(pe_list) == 2 else '',''
    year, month, day, hour =  fdate(finfo)
    return particle, energy, year, month, day, hour

# see http://docs.python.org/howto/sorting.html
fsorted = sorted(finfo, key=particle_energy_date) 

model = list() # for qt
fi = -1 # in case fsorted is empty
for fi,finfo in enumerate(fsorted):
    fname, desc, op_time = finfo
    oper, datetime = op_time
    row = (fi+1, fname, desc, oper, datetime)
    if qt:
        model.append(row[1:]) # for qt, omit line number
    else:
        print '%3d %-36s %-40s %-24s %-24s' % row
flinemax = fi+1 # first line number is 1 not 0

if qt:
    fline = qtbrowse.choose(action, model)
    # print 'qtbrowse returned fline %d' % fline # DEBUG
else:
    # get file name line number from user, with type and range checking
    # user can enter 0 to cancel with no selection
    fline = -1 # force at least one iteration
    while fline not in range(0,flinemax+1):  
        try:
            fline = int(raw_input('Enter file number [%d-%d, or 0 to cancel]: ' % (1,flinemax)))
        except ValueError: # can't convert raw input to int
            pass

# use fline from qt or terminal
if fline > 0:
    finfo = fsorted[fline-1] # first line number is 1 not 0
else:
    # print 'Cancel, no selection' # DEBUG
    exit()

# DEBUG - confirm we got what we wanted
fname, desc, op_time = finfo
oper, datetime = op_time
# print '%3d %-36s %-40s %-24s %-24s' % (fline, fname, desc, oper, datetime) 

# pyepics!
caput('CCC:SR:temp', fname) 
caput('CCC:SR:temp:makeuser', oper)
caput('CCC:SR:temp:makedate', datetime)

# based on opsDisplay/bin/restore2sh, set_etypen function
etype = { 'Proton':1, 'H2+':2, 'Deuteron':3, 'Helium3':4, 'Alpha':5 } 
caput('CCC:SR:SelectionIndex', etype[particle])

# Pass description as EDM macro, there is no CCC:SR:temp:desc
# replace , with . to avoid (rare) EDM error: Incomplete macro specification 
macros = '-m "DESC=%s"' % (desc.replace(',','.') if desc else '(no description)')

# based on opsDisplay/src/browse_callbacks3.c, line 160 ff
# assumes $PWD is .../operations/lib, assume that's where edm is started.
edmoptions = '-x -noscrl -noedit -eolc'
libpath = './SnapShot' # '/users/jon/opsDisplay/lib/SnapShot' # FIXME absolute
binpath = '../bin' # '/users/jon/opsDisplay/bin' # FIXME absolute path
checkcmd = '%s/%s' % (binpath, 'checkfileexist.sh')
edlconfirm = {'Restore':'confirmR.edl', 'Delete':'confirmD.edl', 
              'Print':'confirmP.edl', 'SetDefault':'confirmSetD.edl',
              'remDefault':'confirmRemD.edl'}
edmcmd = "edm %s %s %s/%s" % (edmoptions, macros, libpath, edlconfirm[action])
print edmcmd # DEBUG

# use subprocess.call to make it synchronous  
# with gnome-terminal -e ... term stays open until all done
if action == 'Delete':
     status = subprocess.call(checkcmd, shell=True)
# os.popen now deprecated: http://docs.python.org/library/subprocess.html
#result = os.popen(edmcmd).read() 
status = subprocess.call(edmcmd, shell=True)

#print 'exiting browse.py'
