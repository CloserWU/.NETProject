/*
 * scanner.h
 * ---------------
 *不要修改此文件，这个文件定义了一些lex.yy.c用到的常量和函数.
 lex.yy.c由flex根据scanner.l生成，这里使用里面的一些函数
 */

#ifndef _H_scanner
#define _H_scanner


extern char *yytext;     // Text of lexeme just scanned

int yylex(void);         // Defined in the generated lex.yy.c file  lex.yy.c生成函数
void Inityylex();        // Defined in scanner.l user subroutine section    定义在scanner.l中的自定义函数，先在此声明。声明后，main中可以直接使用
const char *GetLineNumbered(int number);  // lex.yy.c生成函数
void yyerror(char* msg);  // 定义在scanner.l中的自定义函数，先在此声明。声明后，main中可以直接使用
 
#endif
