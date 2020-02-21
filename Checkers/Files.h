#pragma once
#include "List.h"
#include "General.h"
#include "Tree.h"


void StoreBoard(Board board, char* filename);
unsigned short bitSetInPlace(unsigned short bit, int location);
void makeBoardFromArr(unsigned short* arr, Board board);
void LoadBoard(char *filename, Board board);
unsigned short bitVal(unsigned short bit, int location);
void checkFile(FILE *fp);//check if file open