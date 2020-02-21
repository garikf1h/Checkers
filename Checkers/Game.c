#include "Game.h"

void PlayGame(Board board, Player starting_player)//play game function, start the game until there is a winner 
{
	Player currPlayer = starting_player;
	char winner;
	firstBoard(board);
	printBoard(board);
	while (isThereAWinner(board, &winner) == FALSE)// until there is a winner play the game
	{
		Turn(board, currPlayer);
		if (currPlayer == 'B')//switch to the other player
			currPlayer = 'T';
		else//switch to the other player
			currPlayer = 'B';
	}
	if (winner == 'B')// output how is the winner of the game
		printf("the winner is player B\n");
	else
		printf("the winner is player T\n");
}

void Turn(Board board, Player player)//play the cuurent turn of the given player
{
	checkersPos* firstMove = NULL;
	int listCaptures = 0;
	SingleSourceMovesList*bestTurn = getBestTurn(board, player, &listCaptures);
	if (bestTurn->head == NULL)
	{
		exit(NOMOVES);
	}
	SingleSourceMovesListCell*curr = bestTurn->head;
	firstMove = curr->position;
	int direction = 1;
	if (player == 'B')//output what player turn it is
		printf("player BOTTOM_UP'S turn\n");
	if (player == 'T')
		printf("player TOP_DOWN'S turn\n");
	if (listCaptures == 0 && bestTurn->head != NULL)//no captures 
	{
		updateBoard(board, player, toRow(bestTurn->head->position->row), toCol(bestTurn->head->position->col), toRow(bestTurn->tail->position->row), toCol(bestTurn->tail->position->col));
		printf("%c%c->", firstMove->row, firstMove->col);
		firstMove = bestTurn->tail->position;

	}
	//there is captures
	else
	{
		int pDirection;
		if (player == 'T')
			pDirection = 1;
		else
			pDirection = -1;
		while (curr->next != NULL)
		{
			if (curr->position->col > curr->next->position->col)
				direction = -1;
			board[toRow(curr->position->row + pDirection)][toCol(curr->position->col + direction)] = EMPTY;
			updateBoard(board, player, toRow(curr->position->row), toCol(curr->position->col), toRow(curr->next->position->row), toCol(curr->next->position->col));
			curr = curr->next;
			printf("%c%c->", firstMove->row, firstMove->col);
			firstMove = curr->position;
		}
	}
	printf("%c%c\n", firstMove->row, firstMove->col);//print the last move of the player
	freeList(bestTurn);
	printf("\n");
}

BOOL isThereAWinner(Board b, char* winner)// check every turn if there is a winner, if there is a winner stop the game
{
	if (checkARowForB(b) == TRUE)//if B arrive to A line the game end
	{
		*winner = 'B';
		return TRUE;
	}

	if (checkHRowForT(b) == TRUE)//if T arrive to H line the game end
	{
		*winner = 'T';
		return TRUE;
	}
	if (checkForTInBoard(b) == FALSE)//check if there are T players on board, if not end of game
	{
		*winner = 'B';
		return TRUE;
	}
	if (checkForBInBoard(b) == FALSE)//check if there are B players on board, if not end of game
	{
		*winner = 'T';
		return TRUE;
	}
	return FALSE;
}

BOOL checkARowForB(Board b)//if B arrive to A line the game end
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (b[0][i] == 'B')
			return TRUE;
	}
	return FALSE;

}

BOOL checkHRowForT(Board b)//if T arrive to H line the game end
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (b[7][i] == 'T')
			return TRUE;
	}
	return FALSE;

}

BOOL checkForBInBoard(Board b)//check if there are B players on board, if not end of game
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (b[i][j] == 'B')
				return TRUE;
		}
	}
	return FALSE;
}

BOOL checkForTInBoard(Board b)//check if there are T players on board, if not end of game
{

	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (b[i][j] == 'T')
				return TRUE;
		}
	}
	return FALSE;
}