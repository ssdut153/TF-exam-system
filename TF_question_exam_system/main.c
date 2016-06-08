/*
	(1)系统以菜单方式工作
	(2)试题信息录入功能（试题信息用文件保存）——输入
	(3)试题信息浏览功能——输出
	(4)试题信息追加功能——追加
	(5)试题信息抽取功能——组题
	(6)回答所抽取的题目——答题

	抽取的试题不能重复
	检查输入合法性，异常处理

	已知问题：
		1.反复保存时题干的Json会被加多次\"
		2.录入新题不支持空格
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "JsonHelper.h"
#define FILENAME "questions.dat"
#define MAXSIZE 1000

int num = 0;//记录组题的总数
int* index;//记录组题的题号
int answer = 0;//记录组好的题是否被答过了，0未答，1已答
int isExist(int* array, int value, int num)//判断数组中是否已有value值，防止组题重复
{
	int i = 0;
	for (; i < num; i++)
		if (array[i] == value)
			return 1;
	return 0;
}
int* GetRandomIndex(int* index, int num)//取随机题号加入index数组
{
	int finish_num = 0;
	int k;
	srand(time(NULL));
	while (finish_num < num)
	{
		//k = x + rand() % (y - x + 1) 可生成[x,y]范围内的随机数
		//这里为了避免无法取到下表为0的情况生成[1,num]的随机数
		k = 1 + rand() % (num + 1);
		if (isExist(index, k, num))
			continue;
		index[finish_num++] = k;
	}
}
void option1()//处理录入新题功能，不支持空格
{
	char question[1000];
	int answer = 0;
	printf("目前题库已有%d题,现在录入第%d道题\n", question_num, question_num + 1);
	printf("请输入题干（不支持空格）：");
	scanf("%s", question);
	printf("请输入答案，正确输入1，错误输入0：");
	scanf("%d", &answer);
	while (answer != 1 && answer != 0)
	{
		printf("输入有误，正确输入1，错误输入0，请重新输入：");
		scanf("%d", &answer);
	}
	AddQuestion(question, answer);//添加问题到结构体数组
	SaveToFile(FILENAME);//以Json格式保存至文件
}
void option2()//处理输出功能
{
	PrintAll();
	printf("全部%d道题输出完毕\n", question_num);
}
void option3()//追加功能，具体功能不清楚，没有制作
{
	printf("功能尚未制作\n");
}
void option4()//组题功能
{
	int i = 0;
	printf("请输入要抽取的题目数(不大于%d)：", question_num);
	scanf("%d", &num);
	if (num<1 || num>question_num)//判断输入题数是否为负数、0或大于题库数
	{
		printf("输入有误，请输入1至%d的数：", question_num);
		scanf("%d", &num);
	}
	index = (int*)malloc(sizeof(int)*num);
	GetRandomIndex(index, num);//随机取题库
	printf("组题结果(输出为题号)：\n");
	for (i = 0; i < num; i++)
		printf("%d\t", index[i]);
	printf("\n");
}
void option5()//答题功能
{
	int i = 0;
	int this_ans = 0;//记录本题的作答
	int right = 0;//记录答对个数
	if (num == 0 || answer == 1)//判断是否已组题、组题是否被答过一遍
		option4();
	for (; i < num; i++)
	{
		printf("\n\n第%d题（%d/%d）\n", i + 1, i + 1, num);
		printf("%s\n正确请输入1，错误请输入0，请答题：", questions[index[i] - 1].question);
		scanf("%d", &this_ans);
		while (this_ans != 0 && this_ans != 1)
		{
			printf("输入错误，正确请输入1，错误请输入0，请答题：");
			scanf("%d", &this_ans);
		}
		if (this_ans == questions[index[i] - 1].answer)//判断答案是否正确
			right++;
	}
	printf("\n\n答题结束，答对%d道，准确率：%5.2lf%%\n", right, 100.0*right / (double)num);
	answer = 1;
}
void option6()
{
	CleanFile(FILENAME);
	free(questions);
	questions = (struct Question*)malloc(sizeof(struct Question) * MAXSIZE);
	question_num = 0;
}
void option7()
{
	WriteToFile(FILENAME, "[{\"number\":1,\"question\":\"中国建国于1949年\",\"answer\":1},{\"number\":2,\"question\":\"王浩宇特别白\",\"answer\":0},{\"number\":3,\"question\":\"报警电话是110\",\"answer\":1}]");
	free(questions);
	questions = (struct Question*)malloc(sizeof(struct Question) * MAXSIZE);
	question_num = 0;
	LoadFromFile(FILENAME);
}
void error()//处理1-5之外的输入
{
	printf("输入错误，请重新输入\n");
}
int main(int argc, const char * argv[])
{
	int option = 0;
	questions = (struct Question*)malloc(sizeof(struct Question) * MAXSIZE);
	LoadFromFile(FILENAME);//从文件读入题库
	while (1)
	{
		printf("\n输入1\t录入新试题\n");
		printf("输入2\t查看全部试题\n");
		printf("输入3\t追加\n");
		printf("输入4\t组题\n");
		printf("输入5\t答题\n");
		printf("输入6\t清空题库\n");
		printf("输入7\t重置默认题库\n");
		scanf("%d", &option);
		printf("\n");
		switch (option)
		{
		case 1:
			option1();
			break;
		case 2:
			option2();
			break;
		case 3:
			option3();
			break;
		case 4:
			option4();
			break;
		case 5:
			option5();
			break;
		case 6:
			option6();
			break;
		case 7:
			option7();
			break;
		default:
			error();
		}
	}
}
