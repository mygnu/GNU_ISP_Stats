CFILES  = test.c
OBJS    = object.o
EXEC    = app
DBFILE  = debugfile
AFILE   = assembly.asm

CC      = gcc

## standard Flags
CFLAGS  = -Wall -Wno-unused-variable -Wno-unused-result -g -std=gnu99 -O3

## flags for Flymake
FFLAGS	= -Wall -std=gnu99

## debuging flags
DFLAGS  = -Wall -ggdb -std=gnu99 -O0

## gtk+ library additions
GFLAGS  = `pkg-config --cflags --libs gtk+-2.0`

##libcurl flogs
CURLF = -lcurl

## assembaly flags
AFLAGS  = -O2 -S -c --save-temps -masm=intel 

$(EXEC): $(CFILES)
	$(CC) $(CFILES) $(CURLF) $(CFLAGS) -o $(EXEC)   


.PHONY: r
r: $(EXEC)
	./$(EXEC)


.PHONY: d
d: $(CFILES)
	$(CC) $(DFLAGS) -o $(DBFILE) $(CFILES) 
	gdb $(DBFILE)

.PHONY: a
a:	$(CFILES)
	$(CC) $(AFLAGS) -o $(AFILE) $(CFILES)


check-syntax:
	gcc $(FFLAGS) $(GFLAGS) $(CURLF) -o null -S ${CHK_SOURCES}

.PHONY: clean
clean:
	rm -f $(EXEC) $(DBFILE) *.o *~ *.asm *.s *.out






