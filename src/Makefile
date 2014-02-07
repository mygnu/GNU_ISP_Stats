CFILES  = main.c credentials.c internodeAPI.c xmlparsing.c
OBJS    = main.o credentials.o internodeAPI.o xmlparsing.o
EXEC    = gisps
DBFILE  = debugfile
AFILE   = assembly.asm

CC      = gcc

## standard Flags
CFLAGS  = -Wall -Wno-unused-variable -Wno-unused-result -g -std=gnu11 -O2 -pipe

## flags for Flymake
FFLAGS	= -Wall -std=gnu11

## debuging flags
DFLAGS  = -Wall -ggdb -std=gnu11 -O0

## Link libraries Flags
LINKF  = `(curl-config --libs)` `(xml2-config --libs)`

## External libraries Compile flags
LIBF = `(xml2-config --cflags)`

## assembaly flags
AFLAGS  = -O2 -S -c --save-temps -masm=intel 

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)  $(LINKF)    

$(DBFILE): $(OBJS)
	$(CC) $(OBJS) $(DFLAGS) -o $(DBFILE) $(LINKF)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

credentials.o: credentials.c credentials.h
	$(CC) $(CFLAGS) -c credentials.c 

internodeAPI.o: internodeAPI.c internodeAPI.h credentials.h
	$(CC) $(CFLAGS) -c internodeAPI.c

xmlparsing.o: xmlparsing.c xmlparsing.h
	$(CC) $(LIBF) $(CFLAGS) -c xmlparsing.c


.PHONY: r
r: $(EXEC)
	./$(EXEC)


# .PHONY: d
# d: $(DBFILE)
# 	gdb $(DBFILE)


check-syntax:
	gcc $(LIBF) $(FFLAGS) -o null -S ${CHK_SOURCES} $(LINKF)

.PHONY: clean
clean:
	rm -f $(EXEC) $(DBFILE) *.o *~ *.asm *.s tmp/*.xml






