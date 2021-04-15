#include "XORListWithFifoQueue.h"

char input[MAX_INPUT_LENGTH];

int main() {
	while (scanf("%s", input) != EOF)
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
	char commands[COM_COUNT][COM_LENGTH]{
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
		"GARBAGE_HARD",
	};
	for (int j = 0; j < COM_COUNT; j++)
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
		List.add_beg(value);
		break;
	case ADD_END:
		List.add_end(value);
		break;
	case DEL_BEG:
		List.del_beg();
		break;
	case DEL_END:
		List.del_end();
		break;
	case PRINT_FORWARD:
		List.print_forward();
		break;
	case PRINT_BACKWARD:
		List.print_backward();
		break;
	case SIZE:
		List.size();
		break;
	case PUSH:
		List.push(value);
		break;
	case POP:
		List.pop();
		break;
	case PRINT_QUEUE:
		List.print_queue();
		break;
	case COUNT:
		List.count();
		break;
	case GARBAGE_SOFT:
		List.garbage_soft();
		break;
	case GARBAGE_HARD:
		List.garbage_hard();
		break;
	}
}

