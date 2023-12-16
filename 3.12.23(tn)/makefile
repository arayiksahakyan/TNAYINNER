CC = gcc
CFLAGS = -Wall

all: init destroy set check

init: init.c
    $(CC) $(CFLAGS) init.c -o init

destroy: destroy.c
    $(CC) $(CFLAGS) destroy.c -o destroy

set: set.c
    $(CC) $(CFLAGS) set.c -o set

check: check.c
    $(CC) $(CFLAGS) check.c -o check

clean:
    rm -f init destroy set check
