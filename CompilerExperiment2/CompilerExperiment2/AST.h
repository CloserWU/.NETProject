#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/*
 定义ast数据结构，并包装一些操作方法
 一个ast节点包括ast节点值，和子节点的指针
 显而易见，ast是多叉树，因此子节点指针用数组来表达，在c中，定义一个链表，来表示
 链表包括当前节点的值(也就是指向一个ast节点的指针)，和指向链表下一个节点的指针
*/


// 引用全局常量yyerror，(定义在lex.yy.c)
void yyerror(char* msg);



struct ast
{
	char* val; // ast节点值
	struct list* childs;  //子节点的指针
};


struct list {
	struct ast* node; // ast节点的指针
	struct list* next; // 下一个节点的指针
};

// 新建ast节点，初始化val和childs
struct ast* newAST(char* val);
// 新建list节点，初始化node和next
struct list* initChild(struct ast* node);
// 将一个list节点加入到一个ast节点的childs中
void addChild(struct ast* root, struct ast* child);
// 文件树格式打印ast
void printAST(struct ast* root);
void printAST_R(struct ast* root, int level);
void print(struct ast* root, int level);
