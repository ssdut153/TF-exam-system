#ifndef JsonHelper__h
#define JsonHelper__h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"//cJSON头文件，处理json数据

int question_num = 0;//题库已有题数
struct Question//题库结构体
{
	int number;
	char question[1000];
	int answer;
};

struct Question* questions;//题库数组

// answer should be 1(true) or 0(false)
char* BuildJson(int* number, char** quest, int* answer, int num)//输入分别为 题号数组，题干数组，答案数组，总题数；返回对应格式的json字符串，答案只能为0或1
{
	int i = 0;
	cJSON *root, **dir;
	char *out;
	dir = (cJSON**)malloc(sizeof(cJSON*)*num);
	//创建json数组型结构体
	root = cJSON_CreateArray();
	for (i = 0; i < num; i++)
	{
		//创建对象至数组
		cJSON_AddItemToArray(root, dir[i] = cJSON_CreateObject());
		//为对象添加字符串键值对
		cJSON_AddNumberToObject(dir[i], "number", number[i]);
		cJSON_AddStringToObject(dir[i], "question", quest[i]);
		cJSON_AddNumberToObject(dir[i], "answer", answer[i]);
	}
	//将json结构体转换为字符串
	out = cJSON_PrintUnformatted(root);
	//释放内存
	cJSON_Delete(root);
	return out;
}

void WriteToFile(char* filename, char* Json)//写到文件
{
	FILE *fp;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("\nerror on open/create file:%s\n\n", filename);
		return;
	}
	else
	{
		fprintf(fp, "%s", Json);
		fclose(fp);
		printf("保存成功\n");
	}
}

char* ReadFromFile(char* filename)//从文件读取
{
	FILE *fp;
	char read[1000000];
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("\nerror on open/create file:%s\n", filename);
		printf("可能文件不存在，若首次运行本程序请忽略该报错\n\n");
		return "";
	}
	else
	{
		fgets(read, 1000000, fp);
		fclose(fp);
		return read;
	}
}

void CleanFile(char* filename)//清空文件，本程序没用到
{
	FILE *fp;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("\nerror on clean file:%s\n\n", filename);
		return;
	}
	else
	{
		fclose(fp);
	}
}

void ImportJson(char* pJson)//解析json导入结构体数组
{
	cJSON * root = NULL, *item = NULL, *number, *question, *answer;
	char *pr = NULL;
	if (NULL == pJson)
	{
		printf("无数据！\n\n");
		return;
	}
	if ((root = cJSON_Parse(pJson)) == NULL)
	{
		printf("无法解析该json数据！\n\n");
		return;
	}
	free(questions);
	int iSize = cJSON_GetArraySize(root);
	question_num = iSize;
	questions = (struct Question*)malloc(sizeof(struct Question)*iSize);
	for (int iCnt = 0; iCnt < iSize; iCnt++)
	{
		//在代码中定义变量属于C++用法,对纯C代码可能有问题
		cJSON * pSub = cJSON_GetArrayItem(root, iCnt);
		pr = cJSON_Print(pSub);
		item = cJSON_Parse(pr);
		if (NULL == pSub)
			continue;
		//将键值item从json节点中取出
		number = cJSON_GetObjectItem(item, "number");
		question = cJSON_GetObjectItem(item, "question");
		answer = cJSON_GetObjectItem(item, "answer");
		//加入到题库结构体数组
		questions[iCnt].number = atoi(cJSON_Print(number));
		strcpy(questions[iCnt].question, question->valuestring);
		questions[iCnt].answer = atoi(cJSON_Print(answer));
	}
	cJSON_Delete(root);
	printf("Json数据导入完成，题库共有%d道题\n\n",question_num);
	return;
}

void AddQuestion(char* question, int answer)//添加问题到数组
{
	strcpy(questions[question_num].question, question);
	questions[question_num].answer = answer;
	questions[question_num].number = question_num + 1;
	question_num++;
	printf("录入成功\n");
}

void SaveToFile(char* filename)//保存至文件
{
	int i = 0;
	int* number = (int*)malloc(sizeof(int)*question_num);
	char** quest = (char**)malloc(sizeof(char*)*question_num);
	int* answer = (int*)malloc(sizeof(int)*question_num);
	for (i = 0; i < question_num; i++)
	{
		number[i] = questions[i].number;
		quest[i] = (char*)malloc(sizeof(char) * 1000);
		strcpy(quest[i], questions[i].question);
		answer[i] = questions[i].answer;
	}
	//CleanFile(filename);
	WriteToFile(filename, BuildJson(number, quest, answer, question_num));
}

void LoadFromFile(char* filename)//从文件载入
{
	ImportJson(ReadFromFile(filename));
}

void PrintAll()//全部输出
{
	int i = 0;
	for (i = 0; i < question_num; i++)
	{
		printf("No.%d\n%s\nAnswer:", questions[i].number, questions[i].question);
		if (questions[i].answer == 1)
			printf("True\n");
		else
			printf("False\n");
		printf("\n");
	}
}

#endif