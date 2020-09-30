# File:    Makefile
# Author:  Bede Skinner-Vennell, Jack Warburton
# Date:    30 Sep 2020
# Descr:   Makefile for Battleships

.RECIPEPREFIX = +

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../../utils -I../../../fonts -I../../../drivers -I../../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size



# Default target.
all: Battleships.out

# Compile: create object files from C files.
Battleships.o: Battleships.c ../../../drivers/avr/system.h
+$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../../drivers/avr/system.c ../../../drivers/avr/system.h
+$(CC) -c $(CFLAGS) $< -o $@


# Link
Battleships.out: Battleships.o system.o
+$(CC) $(CFLAGS) $^ -o $@ -lm
+$(SIZE) $@


# Clean project.
clean:
+rm *.o *.out *.hex

# Target program project.
program: Battleships.out
+$(OBJCOPY) -O ihex Battleships.out Battleships.hex
+dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash Battleships.hex; dfu-programmer atmega32u2 start
