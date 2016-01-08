
# top level makefile


all:  files dirs groups owners bindirs

files:
	find . -type f -exec chmod 2664 {} \;

dirs:
	find . -type d -exec chmod 2775 {} \;
	find . -type d -name "tmp" -exec chmod 1777 {} \;

groups:
	chgrp -R cnts .

owners:
	chown -R duma .

bindirs:
	find bin/ -type f -exec chmod 2775 {} \;
	find sbin/ -type f -exec chmod 2775 {} \;
	find opIOC/linux-x86/bin/ -type f -exec chmod 2775 {} \;
	find . -type f -name "st.cmd" -exec chmod 2775 {} \;
	find etc/init.d/ -type f  -exec chmod 2775 {} \;

