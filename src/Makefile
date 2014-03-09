CFILES  = main.c credentials.c internodeAPI.c xmlparsing.c
OBJS    = main.o credentials.o internodeAPI.o xmlparsing.o
DOBJS   = dmain.o dcredentials.o dinternodeAPI.o dxmlparsing.o
EXEC    = gisps
DBFILE  = debugfile
AFILE   = assembly.asm

CC      = gcc

## standard Flags
CFLAGS  = -Wall -std=gnu11 -O0 -pipe
#-Wno-unused-variable -Wno-unused-result

## flags for Flymake
FFLAGS	= -Wall -std=gnu11

## debuging flags
DFLAGS  = -Wall -ggdb -std=gnu11 -O0

## Link libraries Flags
LINKF  = `(curl-config --libs)` `(xml2-config --libs)` `(pkg-config --libs libconfuse)`

## External libraries Compile flags
LIBF = `(xml2-config --cflags)` `(pkg-config --cflags libconfuse)`

## assembaly flags
AFLAGS  = -O2 -S -c --save-temps -masm=intel 

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)  $(LINKF)    

main.o: main.c internodeAPI.h credentials.h
	$(CC) $(CFLAGS) -c main.c

credentials.o: credentials.c credentials.h
	$(CC) $(LIBF) $(CFLAGS) -c credentials.c 

internodeAPI.o: internodeAPI.c internodeAPI.h credentials.h
	$(CC) $(LIBF) $(CFLAGS) -c internodeAPI.c

xmlparsing.o: xmlparsing.c xmlparsing.h
	$(CC) $(LIBF) $(CFLAGS) -c xmlparsing.c


.PHONY: run
run: $(EXEC)
	./$(EXEC)

$(DBFILE): $(DOBJS)
	$(CC) $(OBJS) $(DFLAGS) -o $(DBFILE) $(LINKF)

dmain.o: main.c internodeAPI.h credentials.h
	$(CC) $(DFLAGS) -c main.c

dcredentials.o: credentials.c credentials.h
	$(CC) $(LIBF) $(DFLAGS) -c credentials.c 

dinternodeAPI.o: internodeAPI.c internodeAPI.h credentials.h
	$(CC) $(LIBF) $(DFLAGS) -c internodeAPI.c

dxmlparsing.o: xmlparsing.c xmlparsing.h
	$(CC) $(LIBF) $(DFLAGS) -c xmlparsing.c

.PHONY: dbg
dbg: $(DBFILE)
	gdb $(DBFILE)

.PHONY: mem
mem: $(DBFILE)
	valgrind --leak-check=yes $(DBFILE)


check-syntax:
	gcc $(LIBF) $(FFLAGS) -o null -S ${CHK_SOURCES} $(LINKF)

.PHONY: clean
clean:
	rm -f $(EXEC) $(DBFILE) *.o *~ *.asm *.s tmp/*.xml






