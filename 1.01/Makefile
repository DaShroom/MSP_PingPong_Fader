CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430x2012
CFLAGS=-std=gnu99

OBJS=MSP_fade.o


all: $(OBJS)
	$(CC) $(CFLAGS) -o MSP_fade.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr MSP_fade.elf $(OBJS)
