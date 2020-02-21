#pragma once
#include "General.h"
#include "List.h"
#include "Tree.h"
#include "Files.h"


void PlayGame(Board board, Player starting_player);
BOOL isThereAWinner(Board b, char* winner);
BOOL checkARowForB(Board b);
BOOL checkHRowForT(Board b);
BOOL checkForBInBoard(Board b);
BOOL checkForTInBoard(Board b);
void Turn(Board board, Player player);
