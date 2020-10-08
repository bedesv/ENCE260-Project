# File:   Makefile
# Author: Bede Skinner-Vennell & Jack Warburton
# Date:   02 Oct 2020
# Descr:  Makefile for PaperScissorsRock

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../../utils -I../../../fonts -I../../../drivers -I../../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: PaperScissorsRock.out


# Compile: create object files from C source files.
PaperScissorsRock.o: PaperScissorsRock.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../fonts/font5x7_1.h ../../../utils/font.h ../../../utils/pacer.h ../../../utils/tinygl.h ../../../drivers/avr/ir_uart.h ../../../drivers/navswitch.h ScoreControl.h ../../../drivers/led.h ../../../drivers/button.h ../../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../../drivers/avr/system.c ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../../drivers/avr/pio.c ../../../drivers/avr/pio.h ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../../drivers/avr/timer.c ../../../drivers/avr/system.h ../../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../../drivers/display.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../../drivers/ledmat.c ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../../utils/font.c ../../../drivers/avr/system.h ../../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../../utils/pacer.c ../../../drivers/avr/system.h ../../../drivers/avr/timer.h ../../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../../utils/tinygl.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../utils/font.h ../../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../../drivers/avr/ir_uart.c ../../../drivers/avr/ir_uart.h ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/avr/timer0.h ../../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../../drivers/avr/usart1.c ../../../drivers/avr/system.h ../../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../../drivers/avr/timer0.c ../../../drivers/avr/bits.h ../../../drivers/avr/prescale.h ../../../drivers/avr/system.h ../../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../../drivers/avr/prescale.c ../../../drivers/avr/prescale.h ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ScoreControl.o: ScoreControl.c ScoreControl.h  ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../../drivers/led.c ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../../drivers/button.c ../../../drivers/avr/pio.h ../../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../../drivers/navswitch.c ../../../drivers/avr/pio.h ../../../drivers/navswitch.h ../../../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
PaperScissorsRock.out: PaperScissorsRock.o system.o pio.o timer.o display.o ledmat.o font.o pacer.o tinygl.o ir_uart.o usart1.o timer0.o prescale.o ScoreControl.o led.o button.o navswitch.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: PaperScissorsRock.out
	$(OBJCOPY) -O ihex PaperScissorsRock.out PaperScissorsRock.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash PaperScissorsRock.hex; dfu-programmer atmega32u2 start
