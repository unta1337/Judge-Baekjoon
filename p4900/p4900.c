// 4900: 7 더하기
/*
 * 두 개의 7 세그먼트 입력이 주어질 때, 수 두의 합의 7 세그먼트 형식을 구하여라.
 */
// https://www.acmicpc.net/problem/4900

#include <stdio.h>
#include <string.h>

 char* seven_seg[10] =
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
const int seven_len = 7;
const int seven_size = 10;

int single_seven_to_decimal(char* seven);
int seven_to_decimal(char* seven);

char* reverse_seven(char* seven, int len);

 char* single_decimal_to_seven(int decimal);
 char* decimal_to_seven(int decimal);

 char* seven_add(char* p, char* q);

int main(void)
{
	char input[21] = "";
	scanf("%s", input);
	while (strcmp(input, "BYE") != 0)
	{
		char* p = strtok(input, "+");
		char* q = strtok(NULL, "=");

		printf("%s+%s=%s\n", p, q, seven_add(p, q));

		strcpy(input, "");
		scanf("%s", input);
	}

	return 0;
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
	for (int i = 0; i < strlen(seven); i += 3)
	{
		char temp[4] = "";
		memcpy(temp, seven + i, 3 * sizeof(char));

		decimal += single_seven_to_decimal(temp);
		decimal *= 10;
	}
	decimal /= 10;

	return decimal;
}

char* reverse_seven(char* seven, int len)
{
	static char reversed[10] = "";

	if (reversed[0] != 0)
	{
		for (int i = 0; i < 10; i++)
			reversed[i] = 0;
	}

	for (int i = 0; i < len; i++)
	{
		memcpy(reversed + 3 * i, seven + 3 * len - 3 * (i + 1), 3 * sizeof(char));
	}

	return reversed;
}

 char* single_decimal_to_seven(int decimal)
{
	return seven_seg[decimal];
}

 char* decimal_to_seven(int decimal)
{
	static char seven[10] = "";

	if (decimal == 0)
		return single_decimal_to_seven(0);

	if (seven[0] != 0)
	{
		for (int i = 0; i < 10; i++)
			seven[i] = 0;
	}

	int index = 0;
	while (decimal > 0)
	{
		char temp[4] = "";
		strcpy(temp, single_decimal_to_seven(decimal % 10));
		strcat(seven, temp);

		index += 3;
		decimal /= 10;
	}

	strcpy(seven, reverse_seven(seven, index / 3));

	return seven;
}

 char* seven_add(char* p, char* q)
{
	static char result[10] = "";

	if (result[0] != 0)
	{
		for (int i = 0; i < 10; i++)
			result[i] = 0;
	}
	
	int i = seven_to_decimal(p);
	int j = seven_to_decimal(q);
	strcpy(result, decimal_to_seven(i + j));

	return result;
}
