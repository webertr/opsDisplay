########
#This is a basic make file that compiles browse.c out outputs it as browse
#
# 17 mar 2010  sb  edited slightly for readability
#
#
#Simple Assignments
CC=gcc
CFLAGS= -g -Wall -fPIC 
XLIBS=-lXm -lXt -lX11
PROJS= browse text browse2 browse3
PREFIX=/usr/local/cnts/epics/operations
#Tells which targets to make in this case it will make everything
all:	$(PROJS)

#target browse
browse:	browse.o browse_callbacks.o
	$(CC) $(XLIBS) -combine browse_callbacks.o browse.o -o $@

#target browse2
browse2: browse2.o browse_callbacks2.o
	$(CC) $(XLIBS) -combine browse_callbacks2.o browse2.o -o $@

#target browse3
browse3: browse3.o browse_callbacks3.o
	$(CC) $(XLIBS) -combine browse_callbacks3.o browse3.o -o $@

#target text
text:	text.o
	$(CC) $(XLIBS) text.o -o $@

#Builds Object files for all source code.
%.o:    %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Copies all the binaries into the designated directory
install: $(PROJS)
	install -m 0755 $(PROJS) $(PREFIX)/bin

#removes all the object and bin files from the current directory
clean:
	rm -f core *.o $(PROJS)

uninstall:
	rm $(PREFIX)/bin/$(PROJS)

.PHONY: clean install uninstall
