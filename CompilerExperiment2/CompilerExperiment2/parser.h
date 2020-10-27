/*
 * parser.h
 * --------------
 * 不要修改此文件，这个文件定义了parser所需要的一些函数和变量。
 parser_tab.h 和 parser_tab.c都是由bison生成的，这里选择他们定义并实现的一些函数，拿来使用
 * 
 */

#ifndef _H_parser
#define _H_parser

 
#include "parser_tab.h"        // use include generated header to get define
extern struct yyltype yylloc;    // global defined in generated parser_tab.c file
 
int yyparse();       // Defined in the generated parser_tab.c file
void Inityyparse();  // Defined in parser.y
struct ast* buildAST(char* rootKey, int n, ...); // 构建ast，采用可变参数，详见parser.y
int isTermination(char* key); // 判断是不是终结符

#endif
