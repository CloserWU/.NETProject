/*parser.y 详见readme.md
 *
 *bison输入文件，用于产生parser
 *
 *pp2:你的任务只是输出parser的规约动作，即只需要验证输入文件是否符合
 *decaf语言的文法，并把规约动作输出。
 *
*/
%{

/*
 *同flex一样，第一个%{ %}内部的程序将被直接copy到parser_tab.h/c中
 *所以可以将要include的头文件和全局变量放到这儿。
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <process.h>	
#include <stdarg.h>
#include "scanner.h"
#include "AST.h"
#include "hashtable.h"

// 定义ast root
extern struct ast* root;
// 声明map
map_t map;
// 声明buildAST(可变参)
struct ast* buildAST(char* rootKey, int n, ...);
// 声明判断终结符, c中没有bool，用0或非0表示
int isTermination(char* key);

%}

/*
 *在这儿，你可以定义tokens,types,precedence 和 associativity等。
*/

/*
 *从program开始规约
*/
%start Program

/*
 *yylval
 *------
 *这儿定义全局变量yylval，你可以添加自己的非终结符。
*/
%union {			/*bison可以从这个定义中产生yylval的定义 union表示在parser中，给每个节点都创造了一个这样的结构体，供用户使用*/
  int integerConstant;
  int boolConstant;
  const char *stringConstant;
  double doubleConstant;
  char identifier[128];
  struct ast* a;   /* 添加ast */
}

/*Tokens
 *------
 *这儿我们告诉bison所要用到的token类型。
 *bison可以给这些类型定义唯一的数字并输出#define 到parser_tab.h文件中。
*/
%token T_Void T_Bool T_Int T_Double T_String T_Class 
%token T_LessEqual T_GreaterEqual T_Equal T_NotEqual
%token T_And T_Or T_Null T_Extends T_This
%token T_While T_For T_If T_Else T_Return T_Break
%token T_Identifier
%token T_StringConstant T_IntConstant T_DoubleConstant T_BoolConstant
%token T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%left ','
%left T_Or
%left T_And
%left T_Equal T_NotEqual
%left T_LessEqual T_GreaterEqual '>' '<'
%left '+' '-'
%left '/' '*' '%'
%right '!' UMINUS
%left '[' ']' '(' ')' '.'

/*Precedence and Associativity
 *----------------------------
 *定义算符优先级和结合性
 *Note: NO SPACE between % and nonassoc, left, right!!!!!
*/



/*
 * %type <a> 表示：在哪些节点的union中，挑出来a这个参数名，赋值给默认参数$$（即$$是a代表的类型）
 * 要构建ast， 就把除了终结符外的全部token都用a来赋值
 * 在parser_tab.c中，可以看到如下语句 yyval.a = buildAST("DeclList", 2, "DeclList", "Decl");
 * 而yyval就是上述union定义的数据结构
 */
%type <a> Program DeclList Decl VariableDecl Variable Type FunctionDecl Formals 
%type <a> VariableList FunctionDefn ClassDefn OptExtends FieldList Field StmtBlock StmtList Stmt SimpleStmt
%type <a> LValue Call OptReceiver Actuals ExprList ForStmt WhileStmt IfStmt OptElse ReturnStmt PrintStmt
%type <a> BoolExpr Expr Constant
%%
/*
 *在这儿写出你的规则和动作
*/

Program      :  DeclList
				{ printf("Program -> DeclList\n");
				  /* $$ = func($1...)*/
				  $$ = buildAST("Program", 1, "DeclList");
				  root = $$;
				  @1
				}
             ;

DeclList     :  DeclList Decl
				{ printf("DeclList -> DeclList Decl\n");
				  $$ = buildAST("DeclList", 2, "DeclList", "Decl");
				}
             |  /* empty */
             	{ printf("DeclList ->\n"); 
				  $$ = buildAST("DeclList", 1, "null");
				}
             ;
	     
Decl         :  FunctionDecl
				{ printf("Decl -> FunctionDecl\n");
				  $$ = buildAST("Decl", 1, "FunctionDecl");
				}
             |  FunctionDefn
				{ printf("Decl -> FunctionDefn\n");
				  $$ = buildAST("Decl", 1, "FunctionDefn");
				}
             |  ClassDefn
				{ printf("Decl -> ClassDefn\n");
				  $$ = buildAST("Decl", 1, "ClassDefn");
				}
             |  VariableDecl
                { printf("Decl -> VaruableDecl\n");
				  $$ = buildAST("Decl", 1, "VariableDecl");
				}
             ;

VariableDecl :  Variable ';'
                { printf("VariableDecl -> Variable ;\n");
				  $$ = buildAST("VariableDecl", 2, "Variable", ";");
				}
             ;

Variable     :  Type T_Identifier
                { printf("Variable -> Type identifier\n");
				  $$ = buildAST("Variable", 2, "Type", "identifier");
				}
             ;

Type         :  T_Int
                { printf("Type -> int\n");
				  $$ = buildAST("Type", 1, "int");
				}
             |  T_Double
				{ printf("Type -> double\n");
				  $$ = buildAST("Type", 1, "double");
				}
			 |  T_Bool
				{ printf("Type -> bool\n");
				  $$ = buildAST("Type", 1, "bool");
				}
			 |  T_String
				{ printf("Type -> string\n");
				  $$ = buildAST("Type", 1, "string");
				}
			 |  T_Void
				{ printf("Type -> void\n");
				  $$ = buildAST("Type", 1, "void");
				}
			 |  T_Class T_Identifier
				{ printf("Type -> class identifier\n");
				  $$ = buildAST("Type", 2, "class", "identifier");
				}
			 |  Type '[' ']'
				{ printf("Type -> Type []\n");
				  $$ = buildAST("Type", 3, "Type", "[", "]");
				}
             ;

FunctionDecl :  Type T_Identifier '(' Formals ')' ';'
                { printf("FunctionDecl -> Type identifier ( Formals ) ;\n");
				  $$ = buildAST("FunctionDecl", 6, "Type", "identifier", "(", "Formals", ")", ";");
				}
             ;

Formals      :  VariableList
                { printf("Formals -> VariableList \n");
				  $$ = buildAST("Formals", 1, "VariableList");
				}
			 |  /* empty */
				{ printf("Formals -> \n");
				  $$ = buildAST("Formals", 1, "null");
				}
			 ;

VariableList :  VariableList ',' Variable
                { printf("VariableList -> VariableList , Variable\n");
				  $$ = buildAST("VariableList", 3, "VariableList", ",", "Variable");
				}
			 |  Variable
				{ printf("VariableList -> Variable\n");
				  $$ = buildAST("VariableList", 1, "Variable");
				}
             ;

FunctionDefn :  Type T_Identifier '(' Formals ')' StmtBlock
                { printf("FunctionDefn -> Type identifier ( Formals ) StmtBlock\n");
				  $$ = buildAST("FunctionDefn", 6, "Type", "identifier", "(", "Formals", ")", "StmtBlock");
				}
             ;

ClassDefn    :  T_Class T_Identifier OptExtends '{' FieldList '}'
                { printf("ClassDefn -> class identifier OptExtends { FieldList } \n");
				  $$ = buildAST("ClassDefn", 6, "class", "identifier", "OptExtends", "{", "FieldList", "}");
				}
             ;

OptExtends   :  T_Extends T_Identifier
			   { printf("OptExtends -> extends identifier\n");
			     $$ = buildAST("OptExtends", 2, "extends", "identifier");
			   }
			 | /* empty */
			   { printf("OptExtends -> \n");
			     $$ = buildAST("OptExtends", 1, "null");
			   }
			 ;

FieldList    :  FieldList Field
                { printf("FieldList -> FieldList Field\n");
				  $$ = buildAST("FieldList", 2, "FieldList", "Field");
				}
             |  /* empty */
			    { printf("FieldList -> \n");
				  $$ = buildAST("FieldList", 1, "null");
				}
             ;

Field        :  VariableDecl
                { printf("Field -> VariableDecl\n");
				  $$ = buildAST("Field", 1, "VariableDecl");
				}
             |  FunctionDecl
				{ printf("Field -> FunctionDecl\n");
				  $$ = buildAST("Field", 1, "FunctionDecl");
				}
			 |  FunctionDefn
				{ printf("Field -> FunctionDefn\n");
				  $$ = buildAST("Field", 1, "FunctionDefn");
				}
			 ;

StmtBlock    :  '{' StmtList '}'
                { printf("StmtBlock -> { StmtList } \n");
				  $$ = buildAST("StmtBlock", 3, "{", "StmtList", "}");
				}
			 ;

StmtList     :  StmtList Stmt
                { printf("StmtList -> StmtList Stmt\n");
				  $$ = buildAST("StmtList", 2, "StmtList", "Stmt");
				}
			 |  /* empty */
				{ printf("StmtList ->\n");
				  $$ = buildAST("StmtList", 1, "null");
				}
             ;

Stmt         :  VariableDecl
                { printf("Stmt -> VariableDecl\n");
				  $$ = buildAST("Stmt", 1, "VariableDecl");
				}
			 |  SimpleStmt ';'
				{ printf("Stmt -> SimpleStmt ;\n");
				  $$ = buildAST("Stmt", 2, "SimpleStmt", ";");
				}
			 |  IfStmt
				{ printf("Stmt -> IfStmt\n");
				  $$ = buildAST("Stmt", 1, "IfStmt");
				}
             |  WhileStmt
				{ printf("Stmt -> WhileStmt\n");
				  $$ = buildAST("Stmt", 1, "WhileStmt");
				}
             |  ForStmt
			    { printf("Stmt -> ForStmt\n");
				  $$ = buildAST("Stmt", 1, "ForStmt");
				}
             |  ReturnStmt ';'
				{ printf("Stmt -> ReturnStmt ;\n");
				  $$ = buildAST("Stmt", 2, "ReturnStmt", ";");
				}
			 |  PrintStmt ';'
				{ printf("Stmt -> PrintStmt ;\n");
				  $$ = buildAST("Stmt", 2, "PrintStmt", ";");
				}
			 |  StmtBlock 
				{ printf("Stmt -> StmtBlock\n");
				  $$ = buildAST("Stmt", 1, "StmtBlock");
				}
             ;

SimpleStmt   :  LValue '=' Expr
                { printf("SimpleStmt -> LValue = Expr\n");
				  $$ = buildAST("SimpleStmt", 3, "LValue", "=", "Expr");
				}
             |  Expr
				{ printf("SimpleStmt -> Expr\n");
				  $$ = buildAST("SimpleStmt", 1, "Expr");
				}
             |  /* empty */
				{ printf("SimpleStmt -> \n");
				  $$ = buildAST("SimpleStmt", 1, "null");
				}
             ;

LValue       :  OptReceiver T_Identifier
                { printf("LValue -> OptReceiver identifier\n");
				  $$ = buildAST("LValue", 2, "OptReceiver", "identifier");
				}
             |  Expr '[' Expr ']'
				{ printf("LValue -> Expr [ Expr ] \n");
				  $$ = buildAST("LValue", 4, "Expr", "[", "Expr", "]");
				}
             ;

Call         :  OptReceiver T_Identifier '(' Actuals ')'
                { printf("Call -> OptReceiver identifier ( Actuals )\n");
				  $$ = buildAST("Call", 5, "OptReceiver", "identifier", "(", "Actuals", ")");
				}
             ;

OptReceiver  : Expr '.'
				{ printf("OptReceiver -> Expr .\n");
				  $$ = buildAST("OptReceiver", 2, "Expr", ".");
				}
			 | /*empty*/
			   { printf("OptReceiver -> \n");
			     $$ = buildAST("OptReceiver", 1, "null");
			   }
			 ;

Actuals      :  ExprList
                { printf("Actuals -> ExprList\n");
				  $$ = buildAST("Actuals", 1, "ExprList");
				}
             |  /* empty */
				{ printf("Actuals -> \n");
				  $$ = buildAST("Actuals", 1, "null");
				}
             ;

ExprList     :  ExprList ',' Expr
                { printf("ExprList -> ExprList , Expr\n");
				  $$ = buildAST("ExprList", 3, "ExprList", ",", "Expr");
				}
			 |  Expr
				{ printf("ExprList -> Expr\n");
				  $$ = buildAST("ExprList", 1, "Expr");
				}
			 ;

ForStmt      :  T_For '(' SimpleStmt ';' BoolExpr ';' SimpleStmt ')' Stmt
                { printf("ForStmt -> for ( SimpleStmt ; BoolExpr ; SimpleStmt ) Stmt \n");
				  $$ = buildAST("ForStmt", 9, "for", "(", "SimpleStmt", ";", "BoolExpr", ";", "SimpleStmt", ")", "Stmt");
				}
             ;

WhileStmt    :  T_While '(' BoolExpr ')' Stmt
                { printf("WhileStmt -> while( BoolExpr ) Stmt \n");
				  $$ = buildAST("WhileStmt", 5, "while", "(", "BoolExpr", ")", "Stmt");
				}
             ;

IfStmt       :  T_If '(' BoolExpr ')' Stmt OptElse
                { printf("IfStmt -> if ( BoolExpr ) Stmt OptElse \n");
				  $$ = buildAST("IfStmt", 6, "if", "(", "BoolExpr", ")", "Stmt", "OptElse");
				}
             ;

OptElse      :  T_Else Stmt
                { printf("OptElse -> else Stmt\n");
				  $$ = buildAST("OptElse", 2, "else", "Stmt");
				}
			 |  /* empty */
				{ printf("OptElse -> \n");
				  $$ = buildAST("OptElse", 1, "null");
				}
			 ;

ReturnStmt   :  T_Return
                { printf("ReturnStmt -> return\n");
				  $$ = buildAST("ReturnStmt", 1, "retuen");
				}
             |  T_Return Expr
				{ printf("ReturnStmt -> return Expr \n");
				  $$ = buildAST("ReturnStmt", 2, "return", "Expr");
				}
			 ;

PrintStmt    :  T_Print '(' ExprList ')'
                { printf("PrintStmt -> print ( ExprList ) \n");
				  $$ = buildAST("PrintStmt", 4, "print", "(", "ExprList", ")");
				}
             ;

BoolExpr     :  Expr
                { printf("BoolExpr -> Expr\n");
				  $$ = buildAST("BoolExpr", 1, "Expr");
				}
             ;

Expr         :  Constant
                { printf("Expr -> Constant\n");
				  $$ = buildAST("Expr", 1, "Constant");
				}
             |  LValue
				{ printf("Expr -> LValue\n");
				 $$ = buildAST("Expr", 1, "LValue");
				}
             |  T_This
				{ printf("Expr -> this\n");
				  $$ = buildAST("Expr", 1, "this");
				}
             |  Call
				{ printf("Expr -> Call\n");
				  $$ = buildAST("Expr", 1, "Call");
				}
             |  '(' Expr ')'
				{ printf("Expr -> ( Expr ) \n");
				  $$ = buildAST("Expr", 3, "(", "Expr", ")");
				}
             |  Expr '+' Expr
				{ printf("Expr -> Expr + Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "+", "Expr");
				}
             |  Expr '-' Expr
				{ printf("Expr -> Expr - Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "-", "Expr");
				}
             |  Expr '*' Expr
				{ printf("Expr -> Expr * Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "*", "Expr");
				}
			 |  Expr '/' Expr
				{ printf("Expr -> Expr / Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "/", "Expr");
				}
             |  Expr '%' Expr
				{ printf("Expr -> Expr %% Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "%", "Expr");
				}
			 |  '-' Expr %prec UMINUS
				{ printf("Expr -> - Expr \n");
				  $$ = buildAST("Expr", 2, "-", "Expr");
				}
             |  Expr '<' Expr
				{ printf("Expr -> Expr < Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "<", "Expr");
				}
             |  Expr T_LessEqual Expr
				{ printf("Expr -> Expr <= Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "<=", "Expr");
				}
			 |  Expr '>' Expr
				{ printf("Expr -> Expr > Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", ">", "Expr");
				}
             |  Expr T_GreaterEqual Expr
				{ printf("Expr -> Expr >= Expr\n");
				  $$ = buildAST("Expr", 3, "Expr", ">=", "Expr");
				}
             |  Expr T_Equal Expr
				{ printf("Expr -> Expr == Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "==", "Expr");
				}
             |  Expr T_NotEqual Expr
				{ printf("Expr -> Expr != Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "!=", "Expr");
				}
			 |  Expr T_And Expr
				{ printf("Expr -> Expr && Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "&&", "Expr");
				}
			 |  Expr T_Or Expr
				{ printf("Expr -> Expr || Expr \n");
				  $$ = buildAST("Expr", 3, "Expr", "||", "Expr");
				}
		     |  '!' Expr
				{ printf("Expr -> ! Expr \n");
				  $$ = buildAST("Expr", 2, "!", "Expr");
				}
			 |  T_ReadInteger '(' ')'
				{ printf("Expr -> ReadInteger ( ) \n");
				  $$ = buildAST("Expr", 3, "readInteger", "(", ")");
				}
			 |  T_ReadLine '(' ')'
				{ printf("Expr -> ReadLine ( ) \n");
				  $$ = buildAST("Expr", 3, "readLine", "(", ")");
				}
			 |  T_New '(' T_Identifier ')'
				{ printf("Expr -> New ( identifier ) \n");
				  $$ = buildAST("Expr", 4, "new", "(", "identifier", ")");
				}
			 |  T_NewArray '(' Expr ',' Type ')'
				{ printf("Expr -> NewArray ( Expr , Type )\n");
				  $$ = buildAST("Expr", 6, "newArray", "(", "Expr", ",", "Type", ")");
				}
             ;

Constant     :  T_IntConstant
                { printf("Constant -> intConstant\n");
				  $$ = buildAST("Constant", 1, "intConstant");
				}
             |  T_DoubleConstant
				{ printf("Constant -> doubleConstant\n");
				  $$ = buildAST("Constant", 1, "doubleConstant");
				}
             |  T_BoolConstant
				{ printf("Constant -> boolConstant\n");
				  $$ = buildAST("Constant", 1, "boolConstant");
				}
			 |  T_StringConstant
				{ printf("Constant -> stringConstant\n");
				  $$ = buildAST("Constant", 1, "stringConstant");
				}
			 |  T_Null
				{ printf("Constant -> null\n");
				  $$ = buildAST("Constant", 1, "null");
				}
             ;

%% 
/*
 *语法规则到此为止。
 *以下是你自己定义的函数，这些函数将会直接被copy到parser_tab.c文件中，
 *如果你需要一些辅助的函数，可以写到这儿。
*/
void Inityyparse(void) {
}
/**
 * 构建ast，map存储最近使用过的标识
 * Variable -> Type identifier 的语句中， 每次在map中寻找 -> 右边 的记号，如果存在就remove，然后构建ast，并将 -> 左边的根put到map
 * 这样做的原因是， bison是LALR(1) 自底向上分析，因此右侧记号是先识别出来的
 */
struct ast* buildAST(char* rootKey, int n, ...) {
	struct ast* root = newAST(rootKey);
	va_list valist;
	va_start(valist, n);
	for (int i = 0; i < n; i++) {
		char* key = va_arg(valist, char*);
		if (!isTermination(key)) {
			struct ast* a = hashmap_get(map, key);
			if (a == NULL) {
				a = newAST(key);
				addChild(root, a);
			}
			else {
				addChild(root, a);
				hashmap_remove(map, key);
			}
		} else {
			struct ast* a = newAST(key);
			addChild(root, a);
		}
	}
	hashmap_put(map, rootKey, root);
	va_end(valist);
	return root;
}

int isTermination(char* key) {
	if (sizeof(key) > 3) {
		if (key[0] <= 'z' && key[0] >= 'a') return 1; 
		else return 0;
	}
	return 1;
}


