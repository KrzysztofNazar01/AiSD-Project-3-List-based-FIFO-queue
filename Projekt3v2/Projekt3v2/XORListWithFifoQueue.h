#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAX_INPUT_LENGTH 50
#define COM_COUNT 13
#define COM_LENGTH 20

enum Commands {
	ADD_BEG,
	ADD_END,
	DEL_BEG,
	DEL_END,
	PRINT_FORWARD,
	PRINT_BACKWARD,
	SIZE,
	PUSH,
	POP,
	PRINT_QUEUE,
	COUNT,
	GARBAGE_SOFT,
	GARBAGE_HARD,
};

struct node {
	int value;
	node* npx;
	bool queue = false;
};

class XORListWithFifoQueue {
public:

	node* head, * tail, * Front, * Back;
	int LSize, QSize, Bpos = 0, Fpos = 0;

	void size()
	{
		printf("%d\n", LSize);
	}
	void count()
	{
		printf("%d\n", QSize);
	}

	node* XOR(struct node* FirstNode, struct node* SecondNode)
	{
		return (node*)((uintptr_t)(FirstNode) ^ (uintptr_t)(SecondNode));
	}

	node* searchQueueTrueNodeFromTail() {
		node* curr = tail,* prev, * next = NULL;

		while (curr->queue == false) {
			prev = XOR(next, curr->npx);
			next = curr;
			curr = prev;
		}

		return curr;
	}
	node* searchQueueTrueNodeFromHead()
	{
		node* curr = head, * prev = NULL, * next;
		while (curr->queue == false)
		{
			next = XOR(prev, curr->npx);
			prev = curr;
			curr = next;
		}
		return curr;
	}

	int searchQueueIndexFromTail()
	{
		int i = LSize - 1;

		if (head != NULL)
		{
			node* curr = tail;
			node* prev, * next = NULL;

			while (curr->queue == false)
			{
				prev = XOR(next, curr->npx);
				next = curr;
				curr = prev;
				i--;
			}
			return i;
		}
		else
			return 0;
	}
	int searchQueueIndexFromHead()
	{
		if (head != NULL)
		{
			int i = 0;
			node* curr = head,* prev = NULL, * next;

			while (curr->queue == false)
			{
				next = XOR(prev, curr->npx);
				prev = curr;
				curr = next;
				i++;
			}

			return i;
		}
		else
			return 0;
	}

	node* getNode(int index)
	{
		int i = 0;
		node* curr = head;
		node* prev = NULL, * next;

		while (i != index)
		{
			next = XOR(prev, curr->npx);
			prev = curr;
			curr = next;
			i++;
		}
		return curr;
	}

	void push(int value) {
		node* newnode = new node;
		newnode->value = value;

		if (head == NULL)
		{
			newnode->npx = NULL;
			newnode->queue = true;
			Back = Front = head = tail = newnode;
			LSize++;
		}
		else {
			if (LSize > QSize)//lista nie jest rozszerzana
			{
				if (Back == NULL && Front == NULL)
				{
					tail->value = value;
					tail->queue = true;
					Back = Front = tail;
					Fpos = Bpos = searchQueueIndexFromTail();
				}
				else
				{
					if (Bpos == 0)
					{
						tail->queue = true;
						tail->value = value;
						Bpos = LSize - 1;
						Back = tail;
					}
					else if (Bpos == Fpos - 1 && Back == tail)
					{
						Bpos = LSize - 2;
						Fpos = LSize - 1;
						node* temp = XOR(tail->npx, NULL);
						temp->value = value;
						temp->queue = true;
						Back = temp;
					}
					else
					{
						node* Bfollowing = getNode(Bpos + 1);
						node* temp = XOR(Back->npx, Bfollowing);
						temp->queue = true;
						temp->value = value;
						Back = temp;
						Bpos--;
					}
				}
			}
			else {
				newnode->npx = XOR(NULL, head);
				head->npx = XOR(newnode, XOR(NULL, head->npx));
				head = newnode;
				head->queue = true;
				Back = head;
				Fpos++;
				LSize++;
			}
		}
		QSize++;
	}
	void add_beg(int value)
	{
		node* newnode = new node;
		newnode->value = value;

		if (head == NULL)
		{
			newnode->npx = NULL;
			head = tail = newnode;
		}
		else
		{
			newnode->npx = XOR(NULL, head);
			head->npx = XOR(newnode, XOR(NULL, head->npx));
			head = newnode;
		}

		LSize++;
		Bpos++;
		Fpos++;
		Front = getNode(Fpos);
		Back = getNode(Bpos);
	}
	void add_end(int value) {
		node* newnode = new node;
		newnode->value = value;
		newnode->queue = false;


		if (head == NULL) {
			newnode->npx = NULL;
			head = tail = newnode;
		}
		else {
			newnode->npx = XOR(tail, NULL);
			tail->npx = XOR(newnode, XOR(tail->npx, NULL));
			tail = newnode;
		}
		LSize++;

	}

	void pop()
	{
		if (Front != NULL)
		{
			printf("%d\n", Front->value);

			if (QSize == 1)
			{
				Front->queue = false;
				QSize = 0;
				Front = Back = NULL;
				Bpos = Fpos = 0;
			}
			else if (QSize == 2)
			{
				Front->queue = false;
				Front = Back = searchQueueTrueNodeFromTail();
				Fpos = Bpos = searchQueueIndexFromTail();
				QSize = 1;
			}
			else
			{
				Front->queue = false;

				if (Front == head)
					Fpos = searchQueueIndexFromTail();
				else
					Fpos--;

				QSize--;
				Front = getNode(Fpos);
			}
		}
		else
		{
			printf("NULL\n");
		}


	}
	void del_beg()
	{
		if (head != NULL)
		{
			node* next = XOR(head->npx, NULL);

			if (next == NULL)
				tail = NULL;
			else
				next->npx = XOR(head, XOR(next->npx, NULL));

			if (head->queue == true)
				QSize--;

			LSize--;

			head = next;

			if (Bpos > 0) Bpos--;
			if (Fpos > 0) Fpos--;
		}
	}
	void del_end()
	{
		if (head != NULL)
		{
			node* prev = XOR(tail->npx, NULL);

			if (NULL == prev)
				head = NULL;
			else
				prev->npx = XOR(tail, XOR(prev->npx, NULL));

			if (tail->queue == true)
				QSize--;

			if (tail == Back)
			{
				Back = head;
				Bpos = 0;
			}
			LSize--;

			tail = prev;
		}
	}

	void print_backward()
	{
		if (head != NULL)
		{
			node* curr = tail;
			node* next = NULL, * prev;

			while (NULL != curr)
			{
				printf("%d ", curr->value);
				prev = XOR(next, curr->npx);
				next = curr;
				curr = prev;
			}
			printf("\n");
		}
		else
			printf("NULL\n");
	}
	void print_forward()
	{
		if (head != NULL)
		{
			node* curr = head;
			node* prev = NULL, * next;

			while (NULL != curr)
			{
				printf("%d ", curr->value);
				next = XOR(prev, curr->npx);
				prev = curr;
				curr = next;
			}
			printf("\n");
		}
		else
			printf("NULL\n");
	}
	void print_queue()
	{
		if (Front != NULL)
		{
			int QueueCount = 0;

			node* curr = Front;
			node* next = NULL, * prev = NULL;

			if (Fpos <= LSize - 2) 
				next = getNode(Fpos + 1);
			else
				next = NULL;

			if (Fpos >= 1)
				prev = getNode(Fpos - 1);
			else
				prev = NULL;

			while (QueueCount < QSize)
			{
				if (curr->queue == true)
				{
					printf("%d ", curr->value);
					QueueCount++;
				}

				if (curr != head)
				{
					prev = XOR(next, curr->npx);
					next = curr;
					curr = prev;
				}
				else //przejscie na koniec listy
				{
					prev = XOR(tail->npx, NULL);
					next = NULL;
					curr = tail;
				}
			}

			printf("\n");
		}
		else
			printf("NULL\n");
	}

	void garbage_soft()
	{
		if (head != NULL)
		{
			node* curr = head;
			node* prev = NULL, * next;

			while (NULL != curr)
			{
				if (curr->queue == false)
					curr->value = 0;

				next = XOR(prev, curr->npx);
				prev = curr;
				curr = next;
			}
		}
	}
	void garbage_hard()
	{
		if (head != NULL)
		{
			if (LSize == 1 && head->queue == false)
			{
				LSize = 0;
				Back = Front = head = tail = NULL;
			}
			else
			{
				node* prev = NULL, * curr = head, * foll = XOR(NULL, head->npx), * foll2 = tail;
				int i = 0;

				if (foll != NULL)
					foll2 = XOR(head, foll->npx);

				while (curr != NULL)
				{
					if (curr->queue == false)
					{
						if (curr == head || curr == tail)
						{
							if (curr == head)
							{
								del_beg();
							}
							if (curr == tail)
							{
								del_end();
								break;
							}
						}
						else {
							prev->npx = XOR(prev->npx, XOR(curr, foll2));
							foll2->npx = XOR(foll2->npx, XOR(curr, prev));
							curr = foll2;
							foll2 = XOR(prev, curr->npx);
						}
						LSize--;

						if (i <= Bpos) Bpos--;
						if (i <= Fpos) Fpos--;
					}
					else
					{
						if (LSize == QSize) break; //kazdy element listy to czesc kolejki - linijka optymalizacji

						foll = XOR(prev, curr->npx);
						prev = curr;
						curr = foll;
						if (curr != NULL)
							foll2 = XOR(prev, curr->npx);

						i++;
					}
				}
			}
		}
	}

} List;

bool getCommand(int* com_index);
void doCommand(int com_index);

