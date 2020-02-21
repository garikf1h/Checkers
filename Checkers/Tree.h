#pragma once
#include "General.h"

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

SingleSourceMovesTreeNode* createNewTreeNode(checkersPos *pos, Board board, unsigned short capture, SingleSourceMovesTreeNode*left, SingleSourceMovesTreeNode*right);
void createEmptyCell(int direction, int col, int row, int path, SingleSourceMovesTreeNode* root, Board board, int gap, Player p, unsigned short capture);
void FindSingleSourceMovesRec(SingleSourceMovesTreeNode*root, Board board, int row, int col, int capture, Player player);
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
void freeTree(SingleSourceMovesTree* tree);
void FreeTreeRec(SingleSourceMovesTreeNode* root);//free tree recursive
void directionRec(SingleSourceMovesTreeNode*root, Board board, int row, int col, int capture, int path, Player player, int direction, int colDirection);


