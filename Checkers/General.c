#pragma once
#include "General.h"
#include "List.h"
#include "Tree.h"
#include "Files.h"
#include "Game.h"

void updateBoard(Board b, Player p, int curRow, int curCol, int rowToUpdate, int colToUpdate)//the function gets the board and updates the board according to the coordinate
{

	b[curRow][curCol] = EMPTY;
	b[rowToUpdate][colToUpdate] = p;
}
int toLetter(int row)
{
	return row + LETTER_TO_INT;
}
int toCharNum(int col)
{
	return col + CHAR_NUMBER_TO_INT;
}
int toRow(char letter)
{
	return letter - LETTER_TO_INT;
}
int toCol(char number)
{
	return number - CHAR_NUMBER_TO_INT;
}
BOOL isValidRow(Player p, int row, int gap)//chekc if the row is valid according to board size and the gap
{
	if (p == 'T'&&row + gap < BOARD_SIZE)
		return TRUE;
	if (p == 'B'&&row - gap >= 0)
		return TRUE;
	return FALSE;
}

BOOL isValidCol(int col, int direction, int gap)//chekc if the col is valid according to board size and the gap
{
	if (direction == LEFT)
	{
		if (col - gap >= 0)
			return TRUE;
	}

	else
	{
		if (col + gap < BOARD_SIZE)
			return TRUE;
	}

	return FALSE;
}

void updatePlayer(Player p, int *path, Player*opponent)//make moves of each player, B going up, T going down
{
	if (p == 'B')
	{
		*opponent = 'T';
		*path = -1;
	}
	else
	{
		*opponent = 'B';
		*path = 1;
	}

}

void firstBoard(Board b)//make the first board of the game
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (i % 2 == 0 && j % 2 != 0 && i <= 2)
				b[i][j] = 'T';
			else if (i % 2 != 0 && j % 2 == 0 && i <= 2)
				b[i][j] = 'T';
			else if (i % 2 == 0 && j % 2 != 0 && i >= 5)
				b[i][j] = 'B';
			else if (i % 2 != 0 && j % 2 == 0 && i >= 5)
				b[i][j] = 'B';
			else
				b[i][j] = EMPTY;
		}
	}
}


void printBoard(Board b)// print board
{
	int i, j;
	char row, col;
	printf("|| ||1||2||3||4||5||6||7||8|\n");
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("||%c|", toLetter(i));
		for (j = 0; j < BOARD_SIZE; j++)
		{
			printf("|%c|", b[i][j]);
		}
		printf("\n");
	}
}


void memoryAllocationCheck(void* ptr)//check if memory allocation was completed
{
	if (ptr == NULL)
	{
		printf("Memory allocation falied, the program will exit now");
		exit(1);
	}
}
int main()
{
	Board b;
	Player p='B';
	PlayGame(b,p);
	system("Pause");
}