#pragma once
#include "General.h"
#include "List.h"
#include "Tree.h"
#include "Files.h"

SingleSourceMovesListCell* createNode(unsigned short captures, checkersPos* position, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell *result;
	result = (SingleSourceMovesListCell *)malloc(sizeof(SingleSourceMovesListCell));
	memoryAllocationCheck(result);
	result->position = (checkersPos*)malloc(sizeof(checkersPos));// need to allocate new memory to position because the tree will be freed
	memoryAllocationCheck(result->position);
	result->position->row = position->row;
	result->position->col = position->col;
	result->captures = captures;
	result->next = next;
	return result;
}
SingleSourceMovesList* makeEmptyList()
{
	SingleSourceMovesList *result = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	memoryAllocationCheck(result);
	result->head = result->tail = NULL;
	return result;
}
int isEmptyList(SingleSourceMovesList lst)
{
	return (lst.head == NULL);
}
void insertNodeToTail(SingleSourceMovesList* lst, SingleSourceMovesListCell* newTail)
{
	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell* newHead)
{

	if (isEmptyList(*lst))
		lst->head = lst->tail = newHead;
	else
	{
		newHead->next = lst->head;
		lst->head = newHead;
	}
}
SingleSourceMovesList makeEmptyListNotMalloc()
{
	SingleSourceMovesList lst;
	lst.head = lst.tail = NULL;
	return lst;
}
SingleSourceMovesList FindSingleSourceOptimalMoveRec(SingleSourceMovesTreeNode* root, unsigned short* max_captures)// find the best possible move for the each player on the board, using output parameter
{
	int r = -1;
	if (root->next_move[LEFT] == NULL && root->next_move[RIGHT] == NULL) //if the root is a leaf
	{
		SingleSourceMovesList res = makeEmptyListNotMalloc();
		*max_captures = root->total_captures_so_far;
		insertNodeToHead(&res, createNode(root->total_captures_so_far, root->pos, NULL));
		return res;
	}
	else
	{
		SingleSourceMovesList lst_left = makeEmptyListNotMalloc(), lst_right = makeEmptyListNotMalloc();
		unsigned short max_captures_left = 0, max_captures_right = 0;;
		if (root->next_move[LEFT] != NULL)
			lst_left = FindSingleSourceOptimalMoveRec(root->next_move[LEFT], &max_captures_left);
		if (root->next_move[RIGHT] != NULL)
			lst_right = FindSingleSourceOptimalMoveRec(root->next_move[RIGHT], &max_captures_right);
		*max_captures = max(max_captures_left, max_captures_right);
		if (max_captures_left == max_captures_right)
			r = createRandom();
		if ((max_captures_left >= max_captures_right&& lst_left.head != NULL))
		{
			insertNodeToHead(&lst_left, createNode(root->total_captures_so_far, root->pos, lst_left.head));
			freeNodesFromList(lst_right);//free the other list
			return lst_left;
		}
		else
		{
			insertNodeToHead(&lst_right, createNode(root->total_captures_so_far, root->pos, lst_right.head));
			freeNodesFromList(lst_left);
			return lst_right;
		}

	}
}
int createRandom()
{
	srand(time(NULL));
	return rand() % 2;
}

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)//Q2 that use rec function
{
	SingleSourceMovesList lst;
	if (moves_tree->source == NULL)
	{ 
		return makeEmptyList();
	}
	else
	{
		unsigned short max_capture = 0;
		lst = FindSingleSourceOptimalMoveRec(moves_tree->source, &max_capture);
		SingleSourceMovesList*res = makeEmptyList();
		res->head = lst.head;
		res->tail = lst.tail;
		freeTree(moves_tree);
		return res;
	}
}

void insertNodeToTailOfMultipleList(MultipleSourceMovesList *lst, MultipleSourceMovesListCell*newTail)
{
	if (lst->head == NULL)
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		newTail->next = NULL;
		lst->tail = newTail;
	}
}
MultipleSourceMovesListCell*createNewNodeOfMultipleList(SingleSourceMovesList * data, MultipleSourceMovesListCell *next)
{
	MultipleSourceMovesListCell*res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	memoryAllocationCheck(res);
	res->single_source_moves_list = data;
	res->next = next;
	return res;
}
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player p)
{
	MultipleSourceMovesList *res = makeMulEmptyLst();
	SingleSourceMovesList * lst;
	SingleSourceMovesTree*tree = NULL;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == p)//check if there is a player on the spot
			{
				checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
				memoryAllocationCheck(src);
				src->row = toLetter(i);//convetring to cher
				src->col = toCharNum(j);//converting to int
				tree = FindSingleSourceMoves(board, src);//create tree of the possible moves
				if (tree->source != NULL)
				{
					lst = FindSingleSourceOptimalMove(tree);// the tree is not empty, using tree to make list of the best move 
					if (lst->head != NULL)
						insertNodeToTailOfMultipleList(res, createNewNodeOfMultipleList(lst, NULL));//update mul list
					else
						freeList(lst);
				}
				if (tree->source == NULL)// free the tree if is empty
					freeTree(tree);
			}

		}
	}
	return res;
}
MultipleSourceMovesList* makeMulEmptyLst()
{
	MultipleSourceMovesList* res = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	memoryAllocationCheck(res);
	res->head = res->tail = NULL;
	return res;
}
int pathCaptures(SingleSourceMovesList*lst)//returns the captures of the path
{
	SingleSourceMovesListCell*curr = lst->head;
	while (curr != NULL)
	{
		if (curr->next == NULL)
			return curr->captures;
		curr = curr->next;
	}
	return 0;
}

SingleSourceMovesList*getBestTurn(Board board, Player player, int* maxCaptures) //free mulLists and the lists that aren't the best, return the list of the best possible move for the player
{
	MultipleSourceMovesList*lst = FindAllPossiblePlayerMoves(board, player);
	MultipleSourceMovesListCell*curr = lst->head;
	SingleSourceMovesListCell* temp = curr->single_source_moves_list;
	SingleSourceMovesList*maxList = NULL;
	int maxLen = -1, currLen, r = -1;;
	while (curr != NULL)
	{
		currLen = pathCaptures(curr->single_source_moves_list);
		if (maxLen == currLen)// there are two moves with the same captures choose rendomly between the two
			r = createRandom();
		if (maxLen < currLen || r == 1)
		{
			if(maxList != NULL)
				freeList(maxList);//free list that ar not the max
			maxList = curr->single_source_moves_list;
			maxLen = currLen;
		}
		else
			freeList(curr->single_source_moves_list);
		curr = curr->next;
	}
	freeMulList(lst);//free multi lists
	*maxCaptures = maxLen;
	return maxList;
}

void freeMulList(MultipleSourceMovesList* lst)//free multi list
{
	MultipleSourceMovesListCell* current = lst->head;
	MultipleSourceMovesListCell* next;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(lst);
}
void freeList(SingleSourceMovesList* lst)//free single list
{
	SingleSourceMovesListCell* current = lst->head;
	SingleSourceMovesListCell* next = NULL;
	freeNodesFromList(*lst);
	free(lst);
}

void freeNodesFromList(SingleSourceMovesList lst)//free the nodes
{
	SingleSourceMovesListCell* curr = lst.head;
	SingleSourceMovesListCell* next;
	while (curr)
	{
		next = curr->next;
		free(curr->position);
		free(curr);
		curr = next;
	}
}