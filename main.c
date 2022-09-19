#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define ENDSTRUCT "endStr"

typedef struct keyword
{
	char name[10];
} tKeyword;

tKeyword keywords[20] = {
	{"if"},
	{"else"},
	{"elseif"},
	{"while"},
	{"do"},
	{"for"},
	{"function"},
	{"array"},
	{"switch"},
	{"case"},
	{"default"},
	{"break"},
	{"continue"},
	{"static"},
	{"global"},
	{"return"},
	{"echo"},
	{ENDSTRUCT}};

typedef struct delimiter
{
	char name[10];
} tDelimiter;

tDelimiter delimiters[40] = {
	{'{'},
	{'}'},
	{'['},
	{']'},
	{'('},
	{')'},
	{';'},
	{','},
	{' '},
	{'+'},
	{'-'},
	{'*'},
	{'/'},
	{'>'},
	{'<'},
	{'='},
	{'!'},
	{'&'},
	{'|'},
	{'?'},
	{'~'},
	{'"'},
	{'.'},
	//@ eh invalido
	{'@'},
	{ENDSTRUCT}};

typedef struct operator{
	char name[10];
} tOperator;

tOperator operators[40] = {
	// Aritmeticos
	{'+'},
	{'-'},
	{'*'},
	{'/'},
	{'%'},
	{"**"},
	{"++"},
	{"--"},

	// Atribuicao
	{'='},
	{"+="},
	{"-="},
	{"*="},
	{"/="},

	// Comparacao
	{"||"},
	{"&&"},
	{"<<"},
	{">>"},
	{"==="},
	{"!=="},
	{"=="},
	{"!="},
	{"<="},
	{">="},
	{'<'},
	{'>'},
	{'!'},
	{'?'},
	{'~'},
	{ENDSTRUCT}};

bool isDelimiter(char ch)
{
	int i = 0;
	while (strcmp(delimiters[i].name, ENDSTRUCT))
	{
		if (delimiters[i].name[0] == ch)
			return (true);
		i++;
	}

	return (false);
}

bool isOperator(char ch)
{
	int i = 0;
	while (strcmp(operators[i].name, ENDSTRUCT))
	{
		if (strlen(operators[i].name) == 1 && operators[i].name[0] == ch)
			return (true);
		i++;
	}

	return (false);
}

bool isDoubleOperator(char ch1, char ch2)
{
	int i = 0;
	while (strcmp(operators[i].name, ENDSTRUCT))
	{
		if (strlen(operators[i].name) == 2)
		{
			if (operators[i].name[0] == ch1 && operators[i].name[1] == ch2)
				return (true);
		}
		i++;
	}

	return (false);
}

bool isTripleOperator(char ch1, char ch2, char ch3)
{
	int i = 0;
	while (strcmp(operators[i].name, ENDSTRUCT))
	{
		if (strlen(operators[i].name) == 3)
		{
			if (operators[i].name[0] == ch1 && operators[i].name[1] == ch2 && operators[i].name[2] == ch3)
				return (true);
		}
		i++;
	}

	return (false);
}

bool functionIdentifier(char *str)
{
	int i = 0;
	while (i < strlen(str)-1)
	{
        if(str[i] == '_')
            i++;
		else if (str[i] >= '1' && str[i] <= '9')
			i++;
		else if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			i++;
		else
			return (false);
	}

	return (true);
}

bool variableIdentifier(char *str)
{
	if (str[0] != '$')
		return (false);
	int i = 1;
	while (i < strlen(str) - 2)
	{
        if(str[i] == '_')
            i++;
		else if (str[i] >= '1' && str[i] <= '9')
			i++;
		else if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			i++;
		else
			return (false);
	}
	return (true);
}

bool isKeyword(char *str)
{
	for (int i = 0; strcmp(keywords[i].name, ENDSTRUCT); i++)
		if (strcmp(str, keywords[i].name) == 0)
			return (true);

	return (false);
}

bool isInteger(char *str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		if ((str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

char *subString(char *str, int left, int right)
{
	int i;
	char *subStr = (char *)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

void parse(char *str)
{
	int left = 0, right = 0;
	int len = strlen(str);
	int *array = calloc(100, sizeof(int));

	while (right <= len && left <= right)
	{
		if (isDelimiter(str[right]) == false)
			right++;
		else{
			if (isOperator(str[right]) == false && str[right] != ' ')
				printf("Delimiter: '%c'\n", str[right]);
		}

		if (isDelimiter(str[right]) == true && left == right)
		{
			int start = right;
			if (isOperator(str[right]) == true)
			{
				if (right + 1 < strlen(str) && isOperator(str[right + 1]))
				{
					if (right + 2 < strlen(str) && isOperator(str[right + 2]))
					{
						right++;
						left = right;
					}
					right++;
					left = right;
				}
			}

			if (right - start == 2)
			{
				if (isTripleOperator(str[start], str[start + 1], str[start + 2]))
				{
					printf("Triple operator: '%c%c%c'\n", str[start], str[start + 1], str[start + 2]);
				}
				else if (isDoubleOperator(str[start], str[start + 1]))
				{
					printf("Double operator: '%c%c'\n", str[start], str[start + 1]);
					right--;
				}
				else if (isDoubleOperator(str[start + 1], str[start + 2]))
				{
					printf("Operator: '%c'\n", str[start]);
					printf("Double operator: '%c%c'\n", str[start + 1], str[start + 2]);
				}
				else
				{
					printf("Operator: '%c'\n", str[start]);
					right = right - 2;
				}
			}
			else if (right - start == 1)
			{
				if (isDoubleOperator(str[start], str[start + 1]))
				{
					printf("Double operator: '%c%c'\n", str[start], str[start + 1]);
				}
				else
				{
					printf("Operator: '%c'\n", str[start]);
					printf("Operator: '%c'\n", str[start + 1]);
				}
			}
			else if (right - start == 0 && isOperator(str[right]) == true)
			{
				printf("Operator: '%c'\n", str[right]);
			}

			right++;
			left = right;
		}
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
		{
			char *subStr = subString(str, left, right - 1);

			if (isKeyword(subStr) == true)
				printf("Keyword:'%s'\n", subStr);

			else if (isInteger(subStr) == true)
				printf("Integer: '%s'\n", subStr);

			else if (variableIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
				printf("Variable Identifier: '%s'\n", subStr);

			else if (functionIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
				printf("Function Identifier: '%s'\n", subStr);

			else if (variableIdentifier(subStr) == false && functionIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
				if (!strcmp(str, " ")) printf("Invalid Identifier: '%s'\n", str);
			left = right;
		}
	}
	return;
}

int main()
{
	FILE *in_file = fopen("input.txt", "r");
	//Aqui vou usar pra salvar a saída depois
	//FILE *out_file = fopen("output.txt", "w");

	if (in_file == NULL)
	{
		printf("Error in file\n");
		return (0);
	}

	char str[100];
	while (fgets(str, 100, in_file) != NULL)
	{
		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';

		// printf("%d", strlen(str));
		// printf("Lido:%s\n", str);
		parse(str);
	}

	return (0);
}
