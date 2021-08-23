// 1018: 체스판 다시 칠하기
/*
 * rows * cols의 임의로 채색된 채스판 배열이 주어졌을 때, 이 체스판을 완성하기 위해 다시 칠해야 하는 최소한의 칸수를 구하여라.
 */
// https://www.acmicpc.net/problem/1018

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 2853 bytes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** createStringArray(int rows, int cols);
void deleteStringArray(char** stringArray, int rows, int cols);

int countTargetInRange(char* array, int start, int length, char target);
int countTargetInSquare(char** array, int row, int col, int rows, int cols, char target, int place);
int getLeastChangeInSquare(char** array, int row, int col, int rows, int cols);

int arrayMin(int* array, int size);

int main(void)
{
	int rows, cols;
	scanf("%d %d", &rows, &cols);

	char** checkerboard = createStringArray(rows, cols);
	for (int i = 0; i < rows; i++)
		scanf("%s", checkerboard[i]);

	int countSize = (rows - 7) * (cols - 7);
	int* changeCounts = (int*)calloc(countSize, sizeof(int));
	int changeIndex = 0;

	for (int i = 0; i < rows - 7; i++)
	{
		for (int j = 0; j < cols - 7; j++)
			changeCounts[changeIndex++] = getLeastChangeInSquare(checkerboard, i, j, 8, 8);
	}

	int leastChange = arrayMin(changeCounts, countSize);
	printf("%d\n", leastChange);

	deleteStringArray(checkerboard, rows, cols);
	free(changeCounts);

	return 0;
}

char** createStringArray(int rows, int cols)
{
	char** stringArray = (char**)malloc(rows * sizeof(char*));
	for (int i = 0; i < rows; i++)
		stringArray[i] = (char*)calloc(cols + 1, sizeof(char));

	return stringArray;
}

void deleteStringArray(char** stringArray, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		free(stringArray[i]);
	free(stringArray);
}

int countTargetInRange(char* array, int start, int length, char target)
{
	int count = 0;
	for (int i = start; i < start + length; i += 2)
		count += array[i] == target;

	return count;
}

int countTargetInSquare(char** array, int row, int col, int rows, int cols, char target, int place)
{
	int count = 0;
	for (int i = row; i < row + rows; i++)
		count += countTargetInRange(array[i], col + (place + i) % 2, cols, target);

	return count;
}

int getLeastChangeInSquare(char** array, int row, int col, int rows, int cols)
{
	int total = rows * cols;
	int totalEven = total / 2;
	int totalOdd = totalEven + total % 2;

	int blackOdd = countTargetInSquare(array, row, col, rows, cols, 'B', 0);
	int blackEven = countTargetInSquare(array, row, col, rows, cols, 'B', 1);
	int whiteOdd = totalOdd - blackOdd;
	int whiteEven = totalEven - blackEven;

	int bw = whiteOdd + blackEven;
	int wb = blackOdd + whiteEven;;

	int leastChange = bw < wb ? bw : wb;

	return leastChange;
}

int arrayMin(int* array, int size)
{
	int min = array[0];
	for (int i = 1; i < size; i++)
	{
		if (array[i] < min)
			min = array[i];
	}

	return min;
}
