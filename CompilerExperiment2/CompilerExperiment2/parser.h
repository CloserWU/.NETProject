/*
 * parser.h
 * --------------
 * ��Ҫ�޸Ĵ��ļ�������ļ�������parser����Ҫ��һЩ�����ͱ�����
 parser_tab.h �� parser_tab.c������bison���ɵģ�����ѡ�����Ƕ��岢ʵ�ֵ�һЩ����������ʹ��
 * 
 */

#ifndef _H_parser
#define _H_parser

 
#include "parser_tab.h"        // use include generated header to get define
extern struct yyltype yylloc;    // global defined in generated parser_tab.c file
 
int yyparse();       // Defined in the generated parser_tab.c file
void Inityyparse();  // Defined in parser.y
struct ast* buildAST(char* rootKey, int n, ...); // ����ast�����ÿɱ���������parser.y
int isTermination(char* key); // �ж��ǲ����ս��

#endif
