#define _CRT_SECURE_NO_WARNINGS
#pragma once


#include <stdlib.h>
#include <stdio.h>

#define CHAR_NUMBER_TO_INT 49
typedef int BOOL;
#define BOARD_SIZE 8
#define LETTER_TO_INT 65
#define LEFT 0
#define RIGHT 1
#define FALSE 0
#define TRUE 1
#define EMPTY ' '
#define NOMOVES 1
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _checkersPos
{
	char row;
	char col;
}checkersPos;

void updateBoard(Board b, Player p, int curRow, int curCol, int rowToUpdate, int colToUpdate);
void firstBoard(Board b);
BOOL isValidRow(Player p, int row, int gap);
BOOL isValidCol(int col, int direction, int gap);
void printBoard(Board b);
void memoryAllocationCheck(void* ptr);//check if memory allocation was completed
void updatePlayer(Player p, int *path, Player*opponent);
int createRandom();
int toLetter(int row);
int toCharNum(int col);
int toRow(char letter);
int toCol(char number);
