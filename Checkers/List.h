#pragma once
#include "General.h"
#include "Tree.h"
typedef struct _SingleSourceMovesListCell
{
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;

} SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList * single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell*head;
	MultipleSourceMovesListCell*tail;
}MultipleSourceMovesList;
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell* newHead);
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList* makeEmptyList();
int isEmptyList(SingleSourceMovesList lst);
SingleSourceMovesListCell* createNode(unsigned short captures, checkersPos* position, SingleSourceMovesListCell* next);
void insertNodeToTail(SingleSourceMovesList* lst, SingleSourceMovesListCell* newTail);
MultipleSourceMovesList*FindAllPossiblePlayerMoves(Board board, Player p);
void insertNodeToTailOfMultipleList(MultipleSourceMovesList *lst, MultipleSourceMovesListCell*newTail);
MultipleSourceMovesListCell*createNewNodeOfMultipleList(SingleSourceMovesList * data, MultipleSourceMovesListCell *next);
int pathCaptures(SingleSourceMovesList*lst);
SingleSourceMovesList*getBestTurn(Board board, Player player, int* maxCaptures);
MultipleSourceMovesList* makeMulEmptyLst();
void freeList(SingleSourceMovesList* lst);//free single list
void freeMulList(MultipleSourceMovesList* lst);//free multi list
SingleSourceMovesList makeEmptyListNotMalloc();
void freeNodesFromList(SingleSourceMovesList lst);