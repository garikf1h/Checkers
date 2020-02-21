
#include "Files.h"

void StoreBoard(Board board, char* filename)//get board and save it to a binary file 
{
	unsigned short int arr[8] = { 0,0,0,0,0,0,0,0 };
	int i, j, indexForBit = 15;
	FILE* Fbits;
	Fbits = fopen(filename, "wb");
	checkFile(Fbits);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 'T')
				arr[i] = bitSetInPlace(arr[i], indexForBit - 1);

			if (board[i][j] == 'B')
			{
				arr[i] = bitSetInPlace(arr[i], indexForBit);
			}
			indexForBit -= 2;
		}
		indexForBit = 15;
	}
	for (int i = 0; i < 8; i++)
	{
		fwrite(&arr[i], sizeof(unsigned short int), 1, Fbits);
	}

	fclose(Fbits);
}

unsigned short bitSetInPlace(unsigned short bit, int location)//get a number and make it value to biswise
{
	unsigned short res;
	res = bit | (1 << location);
	return res;
}

void LoadBoard(char *filename, Board board)//get file and put data on arr, make from this arr the wanted board from the file
{
	FILE* fbits = fopen(filename, "rb");
	checkFile(fbits);
	unsigned short arr[8] = { 0 };
	fread(arr, sizeof(unsigned short), 8, fbits);
	makeBoardFromArr(arr, board);
	fclose(fbits);
}

void makeBoardFromArr(unsigned short* arr, Board board)//get arr and make board
{
	int i, j;
	int indexForBit;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		indexForBit = 15;
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (bitVal(arr[i], indexForBit) == 1)
				board[i][j] = 'B';
			else
				if (bitVal(arr[i], indexForBit - 1) == 1)
					board[i][j] = 'T';
				else
					board[i][j] = ' ';
			indexForBit -= 2;
		}
	}
}
unsigned short bitVal(unsigned short bit, int location)//get bits and make them to short value
{
	//unsigned short res;
	unsigned short mask = 1;
	if ((bit & (mask << location)) != 0)
		return 1;

	else
		return 0;

}
void checkFile(FILE *fp)//check if file opend
{
	if (fp == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(0);
	}
}