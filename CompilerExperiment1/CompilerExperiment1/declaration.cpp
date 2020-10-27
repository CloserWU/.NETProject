/*
 *declaration.cpp
 *delcaration类的实现。
 *pp1需要你来实现它
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
 *由main.c调用，注意控制输出格式，使得你的输出和例子中的输出保持一致。
*/
void Declaration::Print()
{
	printf("(%s seen %d time(s), first on line %d)\n", name, numoccur, lineFound);
}