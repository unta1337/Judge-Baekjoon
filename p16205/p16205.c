// 16205: 변수명
/*
 * 첫째 줄에 사용한 표기법의 번호와 변수명이 주어진다.
 * 번호가 1인 경우는 카멜 표기법, 2인 경우는 스네이크 표기법, 3인 경우는 파스칼 표기법이다.
 * 입력으로 주어지는 변수명의 길이는 100을 넘지 않는다.
 * 카멜 표기법, 파스칼 표기법을 사용한 변수명은 알파벳 소문자와 대문자로만 이루어져 있고, 스네이크 표기법을 사용한 변수명은 알파벳 소문자와 언더바(_)로만 이루어져 있다.
 * 또, 스네이크 표기법을 사용한 변수명의 첫 글자와 마지막 글자는 언더바가 아니고, 언더바가 연속해서 두 개 이상 사용하는 경우는 없다.
 */
// URL: https://www.acmicpc.net/problem/16205

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 2718 bytes
// http://boj.kr/b82f0ccd77d948b1b1d709db77c345cd

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum VARIABLE_CASES { CAMEL, SNAKE, PASCAL };

struct VariableName
{
	char* camel;
	char* snake;
	char* pascal;
};

char* camelToSnake(char* camel, size_t size)
char* pascalToSnake(char* pascal, size_t size)
char* snakeToCamel(char* snake, size_t size)
char* snakeToPascal(char* snake, size_t size)

int main(void)
{
	struct VariableName input = { NULL, NULL, NULL };

	enum VARIABLE_CASES variableCase;
	char rawInput[101] = "";
	scanf("%u %s", &variableCase, rawInput);

	size_t size = strlen(rawInput);

	switch (variableCase)
	{
		case CAMEL:
			input.camel = rawInput;
			input.snake = camelToSnake(rawInput, size);
			input.pascal = snakeToPascal(input.snake, strlen(input.snake));
			break;
		case SNAKE:
			input.camel = snakeToCamel(rawInput, size);
			input.snake = rawInput;
			input.pascal = snakeToPascal(rawInput, size);
			break;
		case PASCAL:
			input.snake = pascalToSnake(rawInput, size);
			input.pascal = rawInput;
			input.camel = snakeToCamel(input.snake, strlen(input.snake));
			break;
	}

	printf("%s\n%s\n%s\n", input.camel, input.snake, input.pascal);
	
	return 0;
}

char* camelToSnake(char* camel, size_t size)
{
	static char result[101] = "";
	int index = 0;

	for (size_t i = 0; i < size; i++)
	{
		result[index++] = camel[i];
		if ('A' <= camel[i] && camel[i] <= 'Z')
		{
			result[index - 1] = '_';
			result[index++] = tolower(camel[i]);
		}
	}
	result[index] = '\0';

	return result;
}

char* pascalToSnake(char* pascal, size_t size)
{
	char camel[101] = "";
	strcpy(camel, pascal);
	camel[0] = tolower(camel[0]);

	static char result[101] = "";
	strcpy(result, camelToSnake(camel, size));

	return result;
}

char* snakeToCamel(char* snake, size_t size)
{
	static char result[101] = "";
	int index = 0;

	for (size_t i = 0; i < size; i++)
	{
		result[index++] = snake[i];
		if (snake[i] == '_')
		{
			result[index - 1] = toupper(snake[++i]);
		}
	}

	return result;
}

char* snakeToPascal(char* snake, size_t size)
{
	static char result[101] = "";
	strcpy(result, snakeToCamel(snake, size));
	result[0] = toupper(result[0]);

	return result;
}
