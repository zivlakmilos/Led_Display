CC = avr-gcc
CCFLAGS = -mmcu=atmega8

SRC = \
	  main.c \
	  system.c \
	  uart.c \
	  timer.c \
	  eprom.c

OBJS = $(SRC:.c=.o)

LIBS =

all: $(OBJS)
	$(CC) $(CCFLAGS) -o display.elf $^ $(LIBS)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -Rf *.hex *.elf *.o

