// 4900: 7 더하기
/*
 * 7 세그먼트 포멧의 두 수가 주어졌을 때, 두 수의 합의 7 세그먼트 포멧을 구하여라.
 */
// https://www.acmicpc.net/problem/4900

#include <stdio.h>
#include <string.h>

void strrev(char* string);

char* const seven_seg[10] =
{
	"063",
	"010",
	"093",
	"079",
	"106",
	"103",
	"119",
	"011",
	"127",
	"107"
};
const int seven_size = 10;

int single_seven_to_decimal(char* seven);
int seven_to_decimal(char* seven);

char* const single_decimal_to_seven(int decimal);
char* const decimal_to_seven(int decimal);

char* const seven_add(char* p, char* q);

int main(void)
{
	while (1)
	{
		char input[21];
		scanf("%s", input);
		if (!strcmp(input, "BYE"))
			break;

		char* p = strtok(input, "+");
		char* q = strtok(NULL, "=");

		printf("%s+%s=%s\n", p, q, seven_add(p, q));
	}

	return 0;
}

void strrev(char* string)
{
	int len = strlen(string);
	for (int i = 0; i < len / 2; i++)
	{
		char temp = string[i];
		string[i] = string[len - i - 1];
		string[len - i - 1] = temp;
	}
}

int single_seven_to_decimal(char* seven)
{
	for (int i = 0; i < seven_size; i++)
	{
		if (!strcmp(seven, seven_seg[i]))
			return i;
	}
}

int seven_to_decimal(char* seven)
{
	int decimal = 0;
	for (int i = 0; seven[i] != '\0'; i += 3)
	{
		char temp[10] = "";
		memcpy(temp, seven + i, 3 * sizeof(char));

		decimal += single_seven_to_decimal(temp);
		decimal *= 10;
	}
	decimal /= 10;

	return decimal;
}

char* const single_decimal_to_seven(int decimal)
{
	return seven_seg[decimal];
}

char* const decimal_to_seven(int decimal)
{
	static char seven[10] = "";

	if (decimal == 0)
		return single_decimal_to_seven(0);

	seven[0] = seven[0] ? '\0' : seven[0];
	while (decimal > 0)
	{
		char temp[4] = "";
		strcpy(temp, single_decimal_to_seven(decimal % 10));
		strrev(temp);
		strcat(seven, temp);

		decimal /= 10;
	}
	strrev(seven);

	return seven;
}

char* const seven_add(char* p, char* q)
{
	int i = seven_to_decimal(p);
	int j = seven_to_decimal(q);

	return decimal_to_seven(i + j);
}
