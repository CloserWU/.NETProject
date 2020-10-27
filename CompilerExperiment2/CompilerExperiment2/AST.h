#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/*
 ����ast���ݽṹ������װһЩ��������
 һ��ast�ڵ����ast�ڵ�ֵ�����ӽڵ��ָ��
 �Զ��׼���ast�Ƕ����������ӽڵ�ָ��������������c�У�����һ����������ʾ
 ���������ǰ�ڵ��ֵ(Ҳ����ָ��һ��ast�ڵ��ָ��)����ָ��������һ���ڵ��ָ��
*/


// ����ȫ�ֳ���yyerror��(������lex.yy.c)
void yyerror(char* msg);



struct ast
{
	char* val; // ast�ڵ�ֵ
	struct list* childs;  //�ӽڵ��ָ��
};


struct list {
	struct ast* node; // ast�ڵ��ָ��
	struct list* next; // ��һ���ڵ��ָ��
};

// �½�ast�ڵ㣬��ʼ��val��childs
struct ast* newAST(char* val);
// �½�list�ڵ㣬��ʼ��node��next
struct list* initChild(struct ast* node);
// ��һ��list�ڵ���뵽һ��ast�ڵ��childs��
void addChild(struct ast* root, struct ast* child);
// �ļ�����ʽ��ӡast
void printAST(struct ast* root);
void printAST_R(struct ast* root, int level);
void print(struct ast* root, int level);
