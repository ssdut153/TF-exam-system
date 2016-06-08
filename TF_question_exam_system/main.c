/*
	(1)ϵͳ�Բ˵���ʽ����
	(2)������Ϣ¼�빦�ܣ�������Ϣ���ļ����棩��������
	(3)������Ϣ������ܡ������
	(4)������Ϣ׷�ӹ��ܡ���׷��
	(5)������Ϣ��ȡ���ܡ�������
	(6)�ش�����ȡ����Ŀ��������

	��ȡ�����ⲻ���ظ�
	�������Ϸ��ԣ��쳣����

	��֪���⣺
		1.��������ʱ��ɵ�Json�ᱻ�Ӷ��\"
		2.¼�����ⲻ֧�ֿո�
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "JsonHelper.h"
#define FILENAME "questions.dat"

int num = 0;//��¼���������
int* index;//��¼��������
int answer = 0;//��¼��õ����Ƿ񱻴���ˣ�0δ��1�Ѵ�
int isExist(int* array, int value, int num)//�ж��������Ƿ�����valueֵ����ֹ�����ظ�
{
	int i = 0;
	for (; i < num; i++)
		if (array[i] == value)
			return 1;
	return 0;
}
int* GetRandomIndex(int* index, int num)//ȡ�����ż���index����
{
	int finish_num = 0;
	int k;
	srand(time(NULL));
	while (finish_num < num)
	{
		//k = x + rand() % (y - x + 1) ������[x,y]��Χ�ڵ������
		//����Ϊ�˱����޷�ȡ���±�Ϊ0���������[1,num]�������
		k = 1 + rand() % (num + 1);
		if (isExist(index, k, num))
			continue;
		index[finish_num++] = k;
	}
}
void option1()//����¼�����⹦�ܣ���֧�ֿո�
{
	char question[1000];
	int answer = 0;
	printf("Ŀǰ�������%d��,����¼���%d����\n", question_num, question_num + 1);
	printf("��������ɣ���֧�ֿո񣩣�");
	scanf("%s", question);
	printf("������𰸣���ȷ����1����������0��");
	scanf("%d", &answer);
	while (answer != 1 && answer != 0)
	{
		printf("����������ȷ����1����������0�����������룺");
		scanf("%d", &answer);
	}
	AddQuestion(question, answer);//������⵽�ṹ������
	SaveToFile(FILENAME);//��Json��ʽ�������ļ�
}
void option2()//�����������
{
	PrintAll();
	printf("ȫ��%d����������\n", question_num);
}
void option3()//׷�ӹ��ܣ����幦�ܲ������û������
{
	printf("������δ����\n");
}
void option4()//���⹦��
{
	int i = 0;
	printf("������Ҫ��ȡ����Ŀ��(������%d)��", question_num);
	scanf("%d", &num);
	if (num<1 || num>question_num)//�ж����������Ƿ�Ϊ������0����������
	{
		printf("��������������1��%d������", question_num);
		scanf("%d", &num);
	}
	index = (int*)malloc(sizeof(int)*num);
	GetRandomIndex(index, num);//���ȡ���
	printf("������(���Ϊ���)��\n");
	for (i = 0; i < num; i++)
		printf("%d\t", index[i]);
	printf("\n");
}
void option5()//���⹦��
{
	int i = 0;
	int this_ans = 0;//��¼���������
	int right = 0;//��¼��Ը���
	if (num == 0 || answer == 1)//�ж��Ƿ������⡢�����Ƿ񱻴��һ��
		option4();
	for (; i < num; i++)
	{
		printf("\n\n��%d�⣨%d/%d��\n", i + 1, i + 1, num);
		printf("%s\n��ȷ������1������������0������⣺", questions[index[i] - 1].question);
		scanf("%d", &this_ans);
		while (this_ans != 0 && this_ans != 1)
		{
			printf("���������ȷ������1������������0������⣺");
			scanf("%d", &this_ans);
		}
		if (this_ans == questions[index[i] - 1].answer)//�жϴ��Ƿ���ȷ
			right++;
	}
	printf("\n\n������������%d����׼ȷ�ʣ�%5.2lf%%\n", right, 100.0*right / (double)num);
	answer = 1;
}
void error()//����1-5֮�������
{
	printf("�����������������\n");
}
int main(int argc, const char * argv[])
{
	int option = 0;
	LoadFromFile(FILENAME);//���ļ��������
	while (1)
	{
		printf("\n����1\t¼��������\n");
		printf("����2\t�鿴ȫ������\n");
		printf("����3\t׷��\n");
		printf("����4\t����\n");
		printf("����5\t����\n");
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
		default:
			error();
		}
	}
}
