# File:   Makefile
# Author: Bede Skinner-Vennell & Jack Warburton
# Date:   02 Oct 2020
# Descr:  Makefile for PaperScissorsRock

# Definitions.
DRIVERDIR = ../../drivers
UTILSDIR = ../../utils
FONTSDIR = ../../fonts

CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I$(UTILSDIR) -I$(FONTSDIR) -I$(DRIVERDIR) -I$(DRIVERDIR)/avr
OBJCOPY = avr-objcopy
SIZE = avr-size -C --mcu=atmega32u2
DEL = rm


# Default target.
all: PaperScissorsRock.out


# Compile: create object files from C source files.
PaperScissorsRock.o: PaperScissorsRock.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/display.h $(DRIVERDIR)/avr/timer0.o $(FONTSDIR)/font5x7_1.h $(UTILSDIR)/font.h $(UTILSDIR)/pacer.h $(UTILSDIR)/tinygl.h $(DRIVERDIR)/avr/ir_uart.h $(DRIVERDIR)/navswitch.h ScoreControl.h $(DRIVERDIR)/led.h $(DRIVERDIR)/button.h $(DRIVERDIR)/avr/pio.h PlayerSelection.h Visuals.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: $(DRIVERDIR)/avr/system.c $(DRIVERDIR)/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: $(DRIVERDIR)/avr/pio.c $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: $(DRIVERDIR)/avr/timer.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: $(DRIVERDIR)/display.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/display.h $(DRIVERDIR)/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: $(DRIVERDIR)/ledmat.c $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: $(UTILSDIR)/font.c $(DRIVERDIR)/avr/system.h $(UTILSDIR)/font.h
	$(CC) -c $(CFLAGS) $< -o $@

PlayerSelection.o: PlayerSelection.c PlayerSelection.h $(DRIVERDIR)/avr/system.h $(UTILSDIR)/pacer.h $(DRIVERDIR)/button.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: $(UTILSDIR)/pacer.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/avr/timer.h $(UTILSDIR)/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: $(UTILSDIR)/tinygl.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/display.h $(UTILSDIR)/font.h $(UTILSDIR)/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: $(DRIVERDIR)/avr/ir_uart.c $(DRIVERDIR)/avr/ir_uart.h $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/avr/timer0.h $(DRIVERDIR)/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: $(DRIVERDIR)/avr/usart1.c $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: $(DRIVERDIR)/avr/prescale.c $(DRIVERDIR)/avr/prescale.h $(DRIVERDIR)/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ScoreControl.o: ScoreControl.c ScoreControl.h  $(DRIVERDIR)/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: $(DRIVERDIR)/led.c $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/led.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: $(DRIVERDIR)/button.c $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/button.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: $(DRIVERDIR)/navswitch.c $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/navswitch.h $(DRIVERDIR)/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: $(DRIVERDIR)/avr/timer0.c $(DRIVERDIR)/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

Visuals.o:  Visuals.c Visuals.h  $(DRIVERDIR)/avr/system.h $(DRIVERDIR)/avr/pio.h $(DRIVERDIR)/navswitch.h $(UTILSDIR)/tinygl.h $(UTILSDIR)/pacer.h PlayerSelection.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
PaperScissorsRock.out: PaperScissorsRock.o system.o pio.o timer.o display.o ledmat.o font.o pacer.o tinygl.o ir_uart.o usart1.o timer0.o prescale.o ScoreControl.o led.o button.o navswitch.o PlayerSelection.o Visuals.o
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
