/*
 *declaration.cpp
 *delcaration���ʵ�֡�
 *pp1��Ҫ����ʵ����
*/
#include "declaration.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

Declaration::Declaration(const char* str, int lineNum, int num) :name(str)
{
	numoccur = num;
	lineFound = lineNum;

}

const char* Declaration::GetName()
{
	return name;
}

int Declaration::GetLineFound()
{
	return lineFound;

}
int Declaration::GetOccurrences()
{
	return numoccur;
}

void Declaration::IncrementOccurrences()
{

}

/*
 *Print()
 *------
 *��main.c���ã�ע����������ʽ��ʹ���������������е��������һ�¡�
*/
void Declaration::Print()
{
	printf("(%s seen %d time(s), first on line %d)\n", name, numoccur, lineFound);
}