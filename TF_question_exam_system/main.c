/*
	(1)系统以菜单方式工作
	(2)试题信息录入功能（试题信息用文件保存）——输入
	(3)试题信息浏览功能——输出
	(4)试题信息追加功能——追加
	(5)试题信息抽取功能——组题
	(6)回答所抽取的题目——答题

	抽取的试题不能重复
	检查输入合法性，异常处理
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
