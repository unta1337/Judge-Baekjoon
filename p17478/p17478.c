// 17478: 재귀함구가 뭔가요?
/*
 * depth가 주어졌을 때, 재귀 관련 이야기를 하는 프로그램을 작성하시오.
 */
// https://www.acmicpc.net/problem/17478

#include <stdio.h>

char* phrases[8] =
{
	"어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.",
	"\"재귀함수가 뭔가요?\"",
	"\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.",
	"마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.",
	"그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"",
	"라고 답변하였지.",
	"\"재귀함수는 자기 자신을 호출하는 함수라네.\"",
	"____"
};
int pharses_size = sizeof(phrases) / sizeof(phrases[0]);

void print_phrases_with_indentation(int depth, char* phrase)
{
	for (int i = 0; i < depth; i++)
		printf("%s", phrases[7]);
	printf("%s\n", phrase);
}

void print_phrases(int depth, int max_depth)
{
	if (depth == max_depth)
	{
		print_phrases_with_indentation(depth, phrases[1]);
		print_phrases_with_indentation(depth, phrases[6]);
		print_phrases_with_indentation(depth, phrases[5]);
		return;
	}

	if (depth == 0)
		print_phrases_with_indentation(depth, phrases[0]);
	for (int i = 1; i <= 4; i++)
		print_phrases_with_indentation(depth, phrases[i]);
	print_phrases(depth + 1, max_depth);
	print_phrases_with_indentation(depth, phrases[5]);
}

int main(void)
{
	int depth;
	scanf("%d", &depth);

	print_phrases(0, depth);

	return 0;
}
