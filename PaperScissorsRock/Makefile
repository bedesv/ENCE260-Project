# File:    Makefile
# Author:  Bede Skinner-Vennell, Jack Warburton
# Date:    30 Sep 2020
# Descr:   Makefile for PaperScissorsRock

.RECIPEPREFIX = +

#Definitions.
CFLAGS = -g -std=c99 -Wall -Werror -I../../drivers/avr

#Main target
PaperScissorsRock: PaperScissorsRock.o
+gcc $(CFLAGS) -c PaperScissorsRock.c

#Intermediate target:
PaperScissorsRock.o: PaperScissorsRock.c
+gcc $(CFLAGS) -c PaperScissorsRock.c

#Clean up target ("make clean")
clean:
+rm *.o
