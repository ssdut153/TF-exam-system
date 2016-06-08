#ifndef JsonHelper__h
#define JsonHelper__h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"//cJSONͷ�ļ�������json����

int question_num = 0;//�����������
struct Question//���ṹ��
{
	int number;
	char question[1000];
	int answer;
};

struct Question* questions;//�������

// answer should be 1(true) or 0(false)
char* BuildJson(int* number, char** quest, int* answer, int num)//����ֱ�Ϊ ������飬������飬�����飬�����������ض�Ӧ��ʽ��json�ַ�������ֻ��Ϊ0��1
{
	int i = 0;
	cJSON *root, **dir;
	char *out;
	dir = (cJSON**)malloc(sizeof(cJSON*)*num);
	//����json�����ͽṹ��
	root = cJSON_CreateArray();
	for (i = 0; i < num; i++)
	{
		//��������������
		cJSON_AddItemToArray(root, dir[i] = cJSON_CreateObject());
		//Ϊ��������ַ�����ֵ��
		cJSON_AddNumberToObject(dir[i], "number", number[i]);
		cJSON_AddStringToObject(dir[i], "question", quest[i]);
		cJSON_AddNumberToObject(dir[i], "answer", answer[i]);
	}
	//��json�ṹ��ת��Ϊ�ַ���
	out = cJSON_PrintUnformatted(root);
	//�ͷ��ڴ�
	cJSON_Delete(root);
	return out;
}

void WriteToFile(char* filename, char* Json)//д���ļ�
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
		printf("����ɹ�\n");
	}
}

char* ReadFromFile(char* filename)//���ļ���ȡ
{
	FILE *fp;
	char read[1000000];
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("\nerror on open/create file:%s\n", filename);
		printf("�����ļ������ڣ����״����б���������Ըñ���\n\n");
		return "";
	}
	else
	{
		fgets(read, 1000000, fp);
		fclose(fp);
		return read;
	}
}

void CleanFile(char* filename)//����ļ���������û�õ�
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

void ImportJson(char* pJson)//����json����ṹ������
{
	cJSON * root = NULL, *item = NULL, *number, *question, *answer;
	char *pr = NULL;
	if (NULL == pJson)
	{
		printf("�����ݣ�\n\n");
		return;
	}
	if ((root = cJSON_Parse(pJson)) == NULL)
	{
		printf("�޷�������json���ݣ�\n\n");
		return;
	}
	free(questions);
	int iSize = cJSON_GetArraySize(root);
	question_num = iSize;
	questions = (struct Question*)malloc(sizeof(struct Question)*iSize);
	for (int iCnt = 0; iCnt < iSize; iCnt++)
	{
		//�ڴ����ж����������C++�÷�,�Դ�C�������������
		cJSON * pSub = cJSON_GetArrayItem(root, iCnt);
		pr = cJSON_Print(pSub);
		item = cJSON_Parse(pr);
		if (NULL == pSub)
		{
			continue;
		}
		number = cJSON_GetObjectItem(item, "number");
		question = cJSON_GetObjectItem(item, "question");
		answer = cJSON_GetObjectItem(item, "answer");
		questions[iCnt].number = atoi(cJSON_Print(number));
		strcpy(questions[iCnt].question, cJSON_Print(question));
		questions[iCnt].answer = atoi(cJSON_Print(answer));
	}
	cJSON_Delete(root);
	printf("Json���ݵ�����ɣ���⹲��%d����\n\n",question_num);
	return;
}

void AddQuestion(char* question, int answer)//������⵽����
{
	strcpy(questions[question_num].question, question);
	questions[question_num].answer = answer;
	questions[question_num].number = question_num + 1;
	question_num++;
	printf("¼��ɹ�\n");
}

void SaveToFile(char* filename)//�������ļ�
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

void LoadFromFile(char* filename)//���ļ�����
{
	ImportJson(ReadFromFile(filename));
}

void PrintAll()//ȫ�����
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