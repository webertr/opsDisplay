

all:  files dirs groups owners

files:
	find . -type f -exec chmod 2664 {} \;

dirs:
	find . -type d -exec chmod 2775 {} \;

groups:
	chgrp -R cnts .

owners:
	chown -R duma .

