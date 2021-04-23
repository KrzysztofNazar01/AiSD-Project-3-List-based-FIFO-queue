#ifndef przed_dwoma_testami

#include "XORListWithFifoQueue.h"

char input[MAX_INPUT_LENGTH];

int main() {
	while (scanf("%49s", input) != EOF)
	{
		int commandIndex = 0;

		if (getCommand(&commandIndex))
			doCommand(commandIndex);
		else
			printf("Incorrect input!\n");
	}
	return 0;
}


bool getCommand(int* com_index)
{
	const int sizeOfComArray = COM_COUNT + 1;
	char commands[sizeOfComArray][COM_LENGTH]{
		"ADD_BEG",
		"ADD_END",
		"DEL_BEG" ,
		"DEL_END" ,
		"PRINT_FORWARD" ,
		"PRINT_BACKWARD",
		"SIZE",
		"PUSH",
		"POP",
		"PRINT_QUEUE",
		"COUNT",
		"GARBAGE_SOFT",
		"GARBAGE_HARD"
	};
	for (int j = 0; j < sizeOfComArray; j++)
	{
		if (strcmp(input, commands[j]) == 0)
		{
			*com_index = j;
			return true;
		}
	}
	return false;
}

void doCommand(int com_index)
{
	int value = 0;

	if (com_index == ADD_BEG || com_index == ADD_END || com_index == PUSH)
		scanf_s("%10d", &value);

	switch (com_index)
	{
	case ADD_BEG:
		ListWithQueue.addBeg(value);
		break;
	case ADD_END:
		ListWithQueue.addEnd(value);
		break;
	case DEL_BEG:
		ListWithQueue.delBeg();
		break;
	case DEL_END:
		ListWithQueue.delEnd();
		break;
	case PRINT_FORWARD:
		ListWithQueue.printForward();
		break;
	case PRINT_BACKWARD:
		ListWithQueue.printBackward();
		break;
	case SIZE:
		ListWithQueue.showListSize();
		break;
	case PUSH:
		ListWithQueue.push(value);
		break;
	case POP:
		ListWithQueue.pop();
		break;
	case PRINT_QUEUE:
		ListWithQueue.printQueue();
		break;
	case COUNT:
		ListWithQueue.showQueueSize();
		break;
	case GARBAGE_SOFT:
		ListWithQueue.garbageSoft();
		break;
	case GARBAGE_HARD:
		ListWithQueue.garbageHard();
		break;
	}
}


#endif
