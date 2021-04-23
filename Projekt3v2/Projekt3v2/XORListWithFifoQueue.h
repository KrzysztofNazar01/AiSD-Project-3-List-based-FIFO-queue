#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAX_INPUT_LENGTH 50
#define COM_COUNT 12
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
	GARBAGE_HARD
};

struct node {
	int value;
	node* npx;
};

class XORListWithFifoQueue {
private:
	node* head, * tail, * front, * back;
	int listSize = 0, queueSize = 0, backPos = 0, frontPos = 0;

public:
	node* getNode(int index)
	{
		int i = 0;
		node* curr = head;
		node* prev = NULL, * next = XOR(head->npx, NULL);

		if (index == listSize - 1) return tail;
		if (index == 0) return head;
		
		while (i != index){
		
			i++;
			next = XOR(prev, curr->npx);
			prev = curr;
			curr = next;

		}
		return curr;
	}
	bool checkIfQueue(node * toAnalyze)
	{
		bool found = false;
		if (front != NULL)
		{

			node* curr = front;
			node* next = NULL, * prev = NULL;

			if (frontPos <= listSize - 2) //Front is one before last elemet
				next = getNode(frontPos + 1);
			else//front to tail, next to NULL
				next = NULL; 
			
			if (frontPos >= 1)
				prev = getNode(frontPos - 1);
			else //Fpos = 0
				prev = NULL; 

			while (true)
			{
				if (curr == toAnalyze) found = true;
				if (curr == back) break;
				
				if (curr != head)
				{
					prev = XOR(next, curr->npx);
					next = curr;
					curr = prev;
				}
				else //goes from head to the tail
				{
					prev = XOR(tail->npx, NULL);
					next = NULL;
					curr = tail;
				}
			}
		}
		return found;
	}

	void showListSize()
	{
		printf("%d\n", listSize);
	}
	void showQueueSize()
	{
		printf("%d\n", queueSize);
	}

	void push(int value) {
		node* newnode = new node;
		newnode->value = value;

		if (head == NULL)
		{
			newnode->npx = NULL;
			back = front = head = tail = newnode;
			listSize++;
		}
		else
		{
			if (listSize > queueSize)//list is not extended
			{
				if (back == NULL && front == NULL)
				{
					tail->value = value;
					back = front = tail;
					frontPos = backPos = listSize - 1;
				}
				else
				{
					if (backPos == 0)
					{
						tail->value = value;
						backPos = listSize - 1;
						back = tail;
					}
					else if (backPos == frontPos - 1 && back == tail)
					{
						backPos = listSize - 2;
						frontPos = listSize - 1;
						node* temp = XOR(tail->npx, NULL);
						temp->value = value;
						back = temp;
					}
					else
					{
						node* Bfollowing = getNode(backPos + 1);
						node* temp = XOR(back->npx, Bfollowing);
						temp->value = value;
						back = temp;
						backPos--;
					}
				}
			}
			else
			{
				if (frontPos + 1 == backPos)
				{
					newnode->npx = XOR(front, back);
					front->npx = XOR(newnode, XOR(back, front->npx));
					back->npx = XOR(newnode, XOR(front, back->npx));
					back = newnode;
				}
				else
				{
					newnode->npx = XOR(NULL, head);
					head->npx = XOR(newnode, XOR(NULL, head->npx));
					back = head = newnode;
					frontPos++;
				}
				listSize++;
			}
		}
		queueSize++;
	}
	void addBeg(int value)
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

		listSize++;
		backPos++;
		frontPos++;
		front = getNode(frontPos);
		back = getNode(backPos);
	}
	void addEnd(int value) {
		node* newnode = new node;
		newnode->value = value;

		if (head == NULL) {
			newnode->npx = NULL;
			head = tail = newnode;
		}
		else {
			newnode->npx = XOR(tail, NULL);
			tail->npx = XOR(newnode, XOR(tail->npx, NULL));
			tail = newnode;
		}
		listSize++;
	}

	void pop()
	{
		if (front != NULL)
		{
			printf("%d\n", front->value);

			if (queueSize == 1)
			{
				queueSize = 0;
				front = back = NULL;
				backPos = frontPos = 0;
			}
			else if (queueSize == 2)
			{
				front = back;
				frontPos = backPos;
				queueSize = 1;
			}
			else
			{
				if (front == head)
				{
					frontPos = backPos + queueSize - 2 ;
					front = getNode(frontPos);
				}
				else
				{
					frontPos--;
					front = getNode(frontPos);
				}

				queueSize--;
			}
		}
		else
		{
			printf("NULL\n");
		}


	}
	void delBeg()
	{
		if (head != NULL)
		{
			node* next = XOR(head->npx, NULL);

			if (next == NULL)
				tail = NULL;
			else
				next->npx = XOR(head, XOR(next->npx, NULL));


			if(frontPos == 0 || backPos == 0 || checkIfQueue(head))
				queueSize--;

			listSize--;

			head = next;

			if (backPos > 0) backPos--;
			if (frontPos > 0) frontPos--;
			
			front = getNode(frontPos);
			back = getNode(backPos);
		}
	}
	void delEnd()
	{
		if (head != NULL)
		{
			node* prev = XOR(tail->npx, NULL);

			if (NULL == prev)
				head = NULL;
			else
				prev->npx = XOR(tail, XOR(prev->npx, NULL));

			if (frontPos == listSize-1 || backPos == listSize-1 || checkIfQueue(tail))
				queueSize--;

			if (tail == back)
			{
				back = head;
				backPos = 0;
			}
			listSize--;

			tail = prev;
		}
	}

	void printBackward()
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
	void printForward()
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
	void printQueue()
	{
		if (front != NULL)
		{
			node* curr = front;
			node* next = NULL, * prev = NULL;

			if (frontPos <= listSize - 2) 
				next = getNode(frontPos + 1);
			else
				next = NULL;

			if (frontPos >= 1)
				prev = getNode(frontPos - 1);
			else
				prev = NULL;

			while (true)
			{
				printf("%d ", curr->value);

				if(curr == back) break;

				if (curr != head)
				{
					prev = XOR(next, curr->npx);
					next = curr;	
					curr = prev;
				}
				else //goes from head to the tail
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

	void garbageSoft()
	{
		if (head != NULL)
		{
			node* curr = head;
			node* prev = NULL, * next;

			while (NULL != curr)
			{
				if (checkIfQueue(curr) == false)
					curr->value = 0;

				next = XOR(prev, curr->npx);
				prev = curr;
				curr = next;
			}
		}
	}
	void garbageHard()
	{
		if (head != NULL)
		{
			if (listSize == 1 && queueSize==0)
			{
				listSize = 0;
				back = front = head = tail = NULL;
			}
			else
			{
				node* prev = NULL, * curr = head, * foll = XOR(NULL, head->npx), * foll2 = tail;
				int i = 0;

				if (foll != NULL)
					foll2 = XOR(head, foll->npx);

				while (curr != NULL)
				{
					if (checkIfQueue(curr) == false)
					{
						if (curr == head || curr == tail)
						{
							if (curr == head)
							{
								delBeg();
							}
							if (curr == tail)
							{
								delEnd();
								break;
							}
						}
						else {
							prev->npx = XOR(prev->npx, XOR(curr, foll2));
							foll2->npx = XOR(foll2->npx, XOR(curr, prev));
							curr = foll2;
							foll2 = XOR(prev, curr->npx);
						}
						listSize--;

						if (i <= backPos) backPos--;
						if (i <= frontPos) frontPos--;
					}
					else
					{
						if (listSize == queueSize) break; //any next nodes will not be deleted

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

	node* XOR(struct node* FirstNode, struct node* SecondNode)
	{
		return (node*)((uintptr_t)(FirstNode) ^ (uintptr_t)(SecondNode));
	}
} ListWithQueue;

bool getCommand(int* com_index);
void doCommand(int com_index);
