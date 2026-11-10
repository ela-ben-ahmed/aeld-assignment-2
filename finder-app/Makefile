CC ?= gcc
CFLAGS ?= -Wall -Werror

ifneq ($(CROSS_COMPILE),)
	CC := $(CROSS_COMPILE)gcc
endif

all: writer

writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c -o writer.o

clean:
	rm -f writer *.o

.PHONY: all clean
