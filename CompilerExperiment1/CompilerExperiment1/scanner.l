/*
 *scanner.l
 *	
 *	Flex�����ļ�������scanner
*/

%{
/*
 *
 *���*{}*�еĳ��򽫱�ֱ��copy��lex.yy.c��ȥ�����Կ��Խ�Ҫ�õ���ͷ�ļ���
 *ȫ�ֱ���������ط����塣
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "hashtable.h"
#include "utility.h"

int lineno=0;
int mul1=10;
int mul2=16;
int n=mul1;
int ans=0;
int flag=0;
int number=0;//identifier�ڼ��γ���
int li=0; // identifier��һ�γ��ֵ�����
/*
 *Global variable: yylval
 *-----------------------
 *ȫ�ֱ��������ǿ��Դ�yylval�л��ÿ��token�����ԡ�
 *�Ժ����������bison/yacc�Զ����ɣ������ʵ�����棬�����ֶ����塣
*/
YYSTYPE yylval;

/*
 *Global variable: yylloc
 *-----------------------
 *ȫ�ֱ��������ǿ��Դ�yylloc�л��ÿ��token��λ�����ԡ�
 *�Ժ�Ҳ��bison/yacc�Զ����ɡ�
*/
struct yyltype yylloc={1,1,1};

/* 
 *Macro: YY_USER_ACTION 
 *---------------------
 *flex�Լ�����ĺ꣬�����������ÿ��rule��action֮ǰ���У����ԣ�������ÿ��rule��
 *Ҫִ�����Ƶ�action�Ļ������������action������������С�
*/
Declaration d = NULL;
htItem *item[101];
int fun1(char* yytext);
void fun2();
void fun3(unsigned int number);
static void DoBeforeEachAction(); 
#define YY_USER_ACTION DoBeforeEachAction();

%}


/*
 *�����ﶨ����ĸ�������Ϳ�ʼ����
*/

line "\n"
whitespace " "|"\t"
keyword void|int|double|bool|string|class|extends|this|null|while|if|else|return|public|private|New|NewArray|Print|ReadInteger|ReadLine|For
boolean false|true
intnum [0-9]+|((0x|0X)[0-9a-fA-F]+)
realnum [0-9]+("."[0-9]*)?((E|e)("+"|"-"))?[0-9]+
identifier ([a-z]|[A-Z])([a-z]|[A-Z]|[0-9]|_)*
char "."|"+"|"-"|"*"|"/"|"||"|"&&"|">="|"=="|"<="|"("|")"|"!"|"["|"]"|"{"|"}"|","|";"|"!"|"="|"<"|">"
badchar "@"|"#"|"$"|"^"|"&"|"~"|"`"|"?"
String "\""([a-zA-Z]|[0-9]|"."|"+"|"-"|"*"|"/"|"||"|"&&"|">="|"=="|"<="|"("|")"|"!"|"["|"]"|"{"|"}"|","|";"|"!"|"="|"<"|">"|"@"|"#"|"$"|"^"|"&"|"~"|"`"|"?"|" "|"\\")*"\""
badString ("\""([a-zA-Z]|[0-9]|"."|"+"|"-"|"*"|"/"|"||"|"&&"|">="|"=="|"<="|"("|")"|"!"|"["|"]"|"{"|"}"|","|";"|"!"|"="|"<"|">"|"@"|"#"|"$"|"^"|"&"|"~"|"`"|"?"|" "|"\\")*)|"\""
comment "/*"("."|"+"|"-"|"*"|"/"|"||"|"&&"|">="|"=="|"<="|"("|")"|"!"|"["|"]"|"{"|"}"|","|";"|"!"|"="|"<"|">"|"@"|"#"|"$"|"^"|"&"|"~"|"`"|"?"|[a-zA-Z]|[0-9]|"/*"|"*/"|" "|"\\"|"\"")*"*/"
comment1 [//]+("."|"+"|"-"|"*"|"/"|"||"|"&&"|">="|"=="|"<="|"("|")"|"!"|"["|"]"|"{"|"}"|","|";"|"!"|"="|"<"|">"|"@"|"#"|"$"|"^"|"&"|"~"|"`"|"?"|[a-zA-Z]|[0-9]|"/*"|"*/"|" "|"\\"|"\"")*
%%
{comment} {}
{comment1} {}
{whitespace} {yylloc.last_column += 1;}
{keyword} {fun2();
	   printf("%-12s line %d cols %d-%d is T_%c", yytext,yylloc.first_line, yylloc.first_column, yylloc.last_column, toupper(yytext[0]));
	   for(int i=1;yytext[i]!='\0';i++){printf("%c",yytext[i]);}printf("\n");
	   }
{line} {yylloc.last_column = 1;yylloc.first_column=1;yylloc.first_line+=1;lineno=0;}
{boolean} {fun2();
	   if(yytext[0] == 't') yylval.boolConstant=true;
	   else yylval.boolConstant=false;
	   return T_BoolConstant;}

{intnum} {fun2();yylval.integerConstant = atoi(yytext); 
	  yylval.integerConstant = fun1(yytext);
	  return T_IntConstant;}

{realnum} {fun2();yylval.doubleConstant = strtod(yytext,NULL);
	   return T_DoubleConstant;}

{identifier} {fun2();
	      if(flag==0) {htInit(item, 101);flag=1;}
	      unsigned int j=1;
	      char p[100];
	      strcpy(p,yytext);
	      number = htSet(p, 1, item, yylloc.first_line);
	      li = htSetl(p, item);
	      fun3(number);
	      return T_Identifier;}

{String} {fun2();strcpy(yylval.stringConstant, yytext);
	  return T_StringConstant;}

{badString} {fun2();
	     printf("\n*** Error line %d column %d \n*** Illegal newline in string constant %s\n\n",yylloc.first_line,yylloc.first_column,yytext);}

{char} {fun2();
	printf("%-12s line %d cols %d-%d is '%s' \n", yytext,yylloc.first_line, yylloc.first_column, yylloc.last_column, yytext);}

{badchar} {fun2();
	printf("*** Error line %d column %d \n*** Unrecognized char: '%s'\n\n",yylloc.first_line,yylloc.last_column,yytext);}

%%



/*
 *Function yyerror()
 *------------------
 *���������Ϣ�����ʵ����ʹ��ReportError���������������޸ġ�
*/void yyerror(char *msg)
{
  ReportError(&yylloc, "%s", msg);
}

/*
 *Function yywrap()
 *----------------
 *���ļ����˽�����ִ����������������޸ġ�
*/
int yywrap()
{
	return (1);
}

/*
 * Function: DoBeforeEachAction()
 * ------------------------------
 * ����ΪYY_USER_ACTION�ĺ�����
 */
static void DoBeforeEachAction()
{
}

int fun1(char* yytext){
	ans=0;
	for(int i=0;yytext[i]!='\0';i++){
		if(yytext[i] == 'X' || yytext[i] == 'x') 
			{n=mul2;continue;}
		if(yytext[i]<='9' && yytext[i]>='0')
			ans = ans*n+(yytext[i]-'0');
		else if(yytext[i]<='f' && yytext[i]>='a')
			ans = ans*n+(yytext[i]-'a')+10;
		else
			ans = ans*n+(yytext[i]-'A')+10;
	}
	return ans;
}
void fun2(){
	if(lineno==1) yylloc.last_column+=1;
	yylloc.first_column = yylloc.last_column; yylloc.last_column = yylloc.first_column + strlen(yytext) - 1;
	lineno=1;
}
void fun3(unsigned int number){
	if(number==1)
		d = Declaration(yytext, yylloc.first_line, number);
	else
		d = Declaration(yytext, li, number);
	yylval.decl = &d;
	number=0;
}
