/*
	(1)ϵͳ�Բ˵���ʽ����
	(2)������Ϣ¼�빦�ܣ�������Ϣ���ļ����棩��������
	(3)������Ϣ������ܡ������
	(4)������Ϣ׷�ӹ��ܡ���׷��
	(5)������Ϣ��ȡ���ܡ�������
	(6)�ش�����ȡ����Ŀ��������

	��ȡ�����ⲻ���ظ�
	�������Ϸ��ԣ��쳣����
*/

#include <stdio.h>
#include <stdlib.h>
#include "JsonHelper.h"
#define FILENAME "questions.dat"
int main(int argc, const char * argv[]) 
{
	LoadFromFile(FILENAME);
	PrintAll();
	AddQuestion("Is caomai smart?", 0);
	PrintAll();
	SaveToFile(FILENAME);
}
