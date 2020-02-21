#pragma once
#include "Tree.h"

SingleSourceMovesTreeNode* createNewTreeNode(checkersPos *pos, Board board, unsigned short capture, SingleSourceMovesTreeNode*left, SingleSourceMovesTreeNode*right)
{
	SingleSourceMovesTreeNode*res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	memoryAllocationCheck(res);
	for (int i = 1; i <= BOARD_SIZE; i++) 
	{
		for (int j = 1; j <= BOARD_SIZE; j++)
		{
			res->board[i][j] = board[i][j];
		}
	}
	res->pos = pos;
	res->total_captures_so_far = capture;
	res->next_move[0] = left;
	res->next_move[1] = right;
	return res;
}
void createEmptyCell(int direction, int col, int row, int path, SingleSourceMovesTreeNode* root, Board board, int gap, Player p, unsigned short capture)//makes a node of the tree accordint the the given data
{
	checkersPos*temp = (checkersPos*)malloc(sizeof(checkersPos));
	memoryAllocationCheck(temp);
	if (direction == LEFT)//update the position according to given gap and direction of player
		temp->col = toCharNum((col - gap));
	else//update the position according to given gap and direction of player
		temp->col = toCharNum((col + gap));
	temp->row = toLetter(row + path * gap);
	root->next_move[direction] = createNewTreeNode(temp, board, capture, NULL, NULL);
	updateBoard(root->next_move[direction]->board, p, row, col, toRow(temp->row), toCol(temp->col));

}
void FindSingleSourceMovesRec(SingleSourceMovesTreeNode*root, Board board, int row, int col, int capture, Player player)
{
	Player opponent;
	int path;
	//äëøçé
	updatePlayer(player, &path, &opponent); //update player and opponent
	if (isValidRow(player, row, 1))//check if row is valid
		if (isValidCol(col, LEFT, 1))//LEFT
		{
			directionRec(root, board, row, col, capture, path, player, LEFT, -1);
		}
		else
			root->next_move[LEFT] = NULL;
		//move right
		if (isValidCol(col, RIGHT, 1))
		{
			directionRec(root, board, row, col, capture, path, player, RIGHT, 1);
		}
		else{ // not valid move
			root->next_move[RIGHT] = NULL;
	}
}
void directionRec(SingleSourceMovesTreeNode*root, Board board, int row, int col, int capture, int playerDirection, Player player, int direction, int colDirection)
{
	if (isValidCol(col, direction, 1))//LEFT
	{
		if (board[row + playerDirection][col + colDirection] == player)//check if there is the same player next move 
			root->next_move[direction] = NULL;
		else if (board[row + playerDirection][col + colDirection] == EMPTY && capture == 0)//first move and empty
		{
			createEmptyCell(direction, col, row, playerDirection, root, board, 1, player, capture);
		}

		else if (capture > 0 && board[row + playerDirection][col + colDirection] == EMPTY) // not first move and after is empty, stop rec
			root->next_move[direction] = NULL;
		else //there is opponent
		{
			if (isValidCol(col, direction, 2) && isValidRow(player, row, 2)) //check if the input is ok
			{
				if (board[row + (2 * playerDirection)][col + (colDirection * 2)] == EMPTY)
				{
					createEmptyCell(direction, col, row, playerDirection, root, board, 2, player, capture + 1);
					FindSingleSourceMovesRec(root->next_move[direction], board, row + (2 * playerDirection), col + 2 * colDirection, capture + 1, player);
				}
				else
					root->next_move[direction] = NULL;
			}
		}
	}
}
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	Player player;
	int row, col;
	unsigned short capture = 0;
	row = toRow(src->row);
	col = toCol(src->col);
	player = board[row][col];
	SingleSourceMovesTree* treeMoves;
	if (board[row][col] != 'B' && board[row][col] != 'T')//if there is no player in the given position,returns empty tree
	{
		treeMoves = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		memoryAllocationCheck(treeMoves);
		treeMoves->source = NULL;
		free(src); 
	}
	else
	{
		{
			treeMoves = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
			memoryAllocationCheck(treeMoves);
			treeMoves->source = createNewTreeNode(src, board, 0, NULL, NULL);
			FindSingleSourceMovesRec(treeMoves->source, board, row, col, capture, player);//create a list using recursion
			if (treeMoves->source->next_move[0] == NULL && treeMoves->source->next_move[1] == NULL)//if the tree is a leaf,no possible moves,returns empty list
			{
				free(treeMoves->source->pos);
				free(treeMoves->source);
				treeMoves->source = NULL;
			}
		}
	}
	return treeMoves;
}

void freeTree(SingleSourceMovesTree* tree)//free single source move tree
{
	FreeTreeRec(tree->source);
	free(tree);
}

void FreeTreeRec(SingleSourceMovesTreeNode* root)//free tree recursive
{
	if (root != NULL)
	{
		FreeTreeRec(root->next_move[0]);
		FreeTreeRec(root->next_move[1]);
		free(root->pos);
		free(root);
	}
}