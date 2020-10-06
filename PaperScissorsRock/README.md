# Paper Scissors Rock

*Written by Bede Skinner-Vennell and Jack Warburton*

## Overview

This game is a basic implementation of the classic Paper, Scissors, Rock game with a scorekeeping system that tracks wins, losses, draws and games played.

## How to Play

The game will start with the blue LED turning on and a welcome message scrolling across the screen until the joystick is moved in any direction.

Once the joystick has been moved, another message telling the user to pick a move will scroll repeatedly across the screen until the user moves the joystick again.

The blue LED will now turn off, signifying that the game is now in move selection mode; the user must move the joystick up and down (the top of the board is the side with the usb port) to choose what character they want to play, with R = Rock, P = Paper and S = Scissors. Once the user has decided on their move, they must point their IR sensors (on the left side of the board) towards the sensors on their opponents board and press the joystick button down. Their opponents blue LED will now turn on, meaning that they have successfully received the move, once both players have successfully received their opponents move (the blue LED is lit on both boards), they must press the button on the left side of the board, between the matrix display and the IR sensors to end the round and display the current scores.

The scores will now scroll repeatedly across the screen until the user moves the joystick. The scores are in the form "W% L% D% P%" where %'s are the relevant scores to display and W, L, D and P are wins, losses, draws and games played respectively.
