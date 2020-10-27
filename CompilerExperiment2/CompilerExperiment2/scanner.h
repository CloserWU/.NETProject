/*
 * scanner.h
 * ---------------
 *��Ҫ�޸Ĵ��ļ�������ļ�������һЩlex.yy.c�õ��ĳ����ͺ���.
 lex.yy.c��flex����scanner.l���ɣ�����ʹ�������һЩ����
 */

#ifndef _H_scanner
#define _H_scanner


extern char *yytext;     // Text of lexeme just scanned

int yylex(void);         // Defined in the generated lex.yy.c file  lex.yy.c���ɺ���
void Inityylex();        // Defined in scanner.l user subroutine section    ������scanner.l�е��Զ��庯�������ڴ�������������main�п���ֱ��ʹ��
const char *GetLineNumbered(int number);  // lex.yy.c���ɺ���
void yyerror(char* msg);  // ������scanner.l�е��Զ��庯�������ڴ�������������main�п���ֱ��ʹ��
 
#endif
