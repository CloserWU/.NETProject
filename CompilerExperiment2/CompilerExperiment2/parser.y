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
				  $$ = $1;
				  root = $$;
				  @1
				}
             ;

DeclList     :  DeclList Decl
				{ printf("DeclList -> DeclList Decl\n");
				  $$ = buildAST("DeclList", 2, $1, $2);
				}
             |  /* empty */
             	{ printf("DeclList ->\n"); 
				  $$ = NULL;
				}
             ;
	     
Decl         :  FunctionDecl
				{ printf("Decl -> FunctionDecl\n");
				  $$ = $1;
				}
             |  FunctionDefn
				{ printf("Decl -> FunctionDefn\n");
				  $$ = $1;
				}
             |  ClassDefn
				{ printf("Decl -> ClassDefn\n");
				  $$ = $1;
				}
             |  VariableDecl
                { printf("Decl -> VaruableDecl\n");
				  $$ = $1;
				}
             ;

VariableDecl :  Variable ';'
                { printf("VariableDecl -> Variable ;\n");
				  $$ = buildAST("VariableDecl", 2, $1, newAST(";"));
				}
             ;

Variable     :  Type T_Identifier
                { printf("Variable -> Type identifier\n");
				  $$ = buildAST("Variable", 2, $1, newAST("identifier"));
				}
             ;

Type         :  T_Int
                { printf("Type -> int\n");
				  $$ = newAST("int");
				}
             |  T_Double
				{ printf("Type -> double\n");
				  $$ = newAST("double");
				}
			 |  T_Bool
				{ printf("Type -> bool\n");
				  $$ = newAST("bool");
				}
			 |  T_String
				{ printf("Type -> string\n");
				  $$ = newAST("string");
				}
			 |  T_Void
				{ printf("Type -> void\n");
				  $$ = newAST("void");
				}
			 |  T_Class T_Identifier
				{ printf("Type -> class identifier\n");
				  $$ = buildAST("Type", 2, newAST("class"), newAST("identifier"));
				}
			 |  Type '[' ']'
				{ printf("Type -> Type []\n");
				  $$ = buildAST("Type", 3, $1, newAST("["), newAST("]"));
				}
             ;

FunctionDecl :  Type T_Identifier '(' Formals ')' ';'
                { printf("FunctionDecl -> Type identifier ( Formals ) ;\n");
				  $$ = buildAST("FunctionDecl", 6, $1, newAST("identifier"), newAST("("), $4, newAST(")"), newAST(";"));
				}
             ;

Formals      :  VariableList
                { printf("Formals -> VariableList \n");
				  $$ = $1;
				}
			 |  /* empty */
				{ printf("Formals -> \n");
				  $$ = NULL;
				}
			 ;

VariableList :  VariableList ',' Variable
                { printf("VariableList -> VariableList , Variable\n");
				  $$ = buildAST("VariableList", 3, $1, newAST(","), $3);
				}
			 |  Variable
				{ printf("VariableList -> Variable\n");
				  $$ = $1;
				}
             ;

FunctionDefn :  Type T_Identifier '(' Formals ')' StmtBlock
                { printf("FunctionDefn -> Type identifier ( Formals ) StmtBlock\n");
				  $$ = buildAST("FunctionDefn", 6, $1, newAST("identifier"), newAST("("), $4, newAST(")"), $6);
				}
             ;

ClassDefn    :  T_Class T_Identifier OptExtends '{' FieldList '}'
                { printf("ClassDefn -> class identifier OptExtends { FieldList } \n");
				  $$ = buildAST("ClassDefn", 6, newAST("class"), newAST("identifier"), $3, newAST("{"), $5, newAST("}"));
				}
             ;

OptExtends   :  T_Extends T_Identifier
			   { printf("OptExtends -> extends identifier\n");
			     $$ = buildAST("OptExtends", 2, newAST("extends"), newAST("identifier"));
			   }
			 | /* empty */
			   { printf("OptExtends -> \n");
			     $$ = NULL;
			   }
			 ;

FieldList    :  FieldList Field
                { printf("FieldList -> FieldList Field\n");
				  $$ = buildAST("FieldList", 2, $1, $2);
				}
             |  /* empty */
			    { printf("FieldList -> \n");
				  $$ = NULL;
				}
             ;

Field        :  VariableDecl
                { printf("Field -> VariableDecl\n");
				  $$ = $1;
				}
             |  FunctionDecl
				{ printf("Field -> FunctionDecl\n");
				  $$ = $1;
				}
			 |  FunctionDefn
				{ printf("Field -> FunctionDefn\n");
				  $$ = $1;
				}
			 ;

StmtBlock    :  '{' StmtList '}'
                { printf("StmtBlock -> { StmtList } \n");
				  $$ = buildAST("StmtBlock", 3, newAST("{"), $2, newAST("}"));
				}
			 ;

StmtList     :  StmtList Stmt
                { printf("StmtList -> StmtList Stmt\n");
				  $$ = buildAST("StmtList", 2, $1, $2);
				}
			 |  /* empty */
				{ printf("StmtList ->\n");
				  $$ = NULL;
				}
             ;

Stmt         :  VariableDecl
                { printf("Stmt -> VariableDecl\n");
				  $$ = $1;
				}
			 |  SimpleStmt ';'
				{ printf("Stmt -> SimpleStmt ;\n");
				  $$ = $1;
				}
			 |  IfStmt
				{ printf("Stmt -> IfStmt\n");
				  $$ = $1;
				}
             |  WhileStmt
				{ printf("Stmt -> WhileStmt\n");
				  $$ = $1;
				}
             |  ForStmt
			    { printf("Stmt -> ForStmt\n");
				  $$ = $1;
				}
             |  ReturnStmt ';'
				{ printf("Stmt -> ReturnStmt ;\n");
				  $$ = buildAST("Stmt", 2, $1, newAST(";"));
				}
			 |  PrintStmt ';'
				{ printf("Stmt -> PrintStmt ;\n");
				  $$ = buildAST("Stmt", 2, $1, newAST(";"));
				}
			 |  StmtBlock 
				{ printf("Stmt -> StmtBlock\n");
				  $$ = $1;
				}
             ;

SimpleStmt   :  LValue '=' Expr
                { printf("SimpleStmt -> LValue = Expr\n");
				  $$ = buildAST("SimpleStmt", 3, $1, newAST("="), $3);
				}
             |  Expr
				{ printf("SimpleStmt -> Expr\n");
				  $$ = $1;
				}
             |  /* empty */
				{ printf("SimpleStmt -> \n");
				  $$ = NULL;
				}
             ;

LValue       :  OptReceiver T_Identifier
                { printf("LValue -> OptReceiver identifier\n");
				  $$ = buildAST("LValue", 2, $1, newAST("identifier"));
				}
             |  Expr '[' Expr ']'
				{ printf("LValue -> Expr [ Expr ] \n");
				  $$ = buildAST("LValue", 4, $1, newAST("["), $3, newAST("]"));
				}
             ;

Call         :  OptReceiver T_Identifier '(' Actuals ')'
                { printf("Call -> OptReceiver identifier ( Actuals )\n");
				  $$ = buildAST("Call", 5, $1, newAST("identifier"), newAST("("), $4, newAST(")"));
				}
             ;

OptReceiver  : Expr '.'
				{ printf("OptReceiver -> Expr .\n");
				  $$ = buildAST("OptReceiver", 2, $1, newAST("."));
				}
			 | /*empty*/
			   { printf("OptReceiver -> \n");
			     $$ = NULL;
			   }
			 ;

Actuals      :  ExprList
                { printf("Actuals -> ExprList\n");
				  $$ = $1;
				}
             |  /* empty */
				{ printf("Actuals -> \n");
				  $$ = NULL;
				}
             ;

ExprList     :  ExprList ',' Expr
                { printf("ExprList -> ExprList , Expr\n");
				  $$ = buildAST("ExprList", 3, $1, newAST(","), $3);
				}
			 |  Expr
				{ printf("ExprList -> Expr\n");
				  $$ = $1;
				}
			 ;

ForStmt      :  T_For '(' SimpleStmt ';' BoolExpr ';' SimpleStmt ')' Stmt
                { printf("ForStmt -> for ( SimpleStmt ; BoolExpr ; SimpleStmt ) Stmt \n");
				  $$ = buildAST("ForStmt", 9, newAST("for"), newAST("("), $3, newAST(";"), $5, newAST(";"), $7, newAST(")"), $9);
				}
             ;

WhileStmt    :  T_While '(' BoolExpr ')' Stmt
                { printf("WhileStmt -> while( BoolExpr ) Stmt \n");
				  $$ = buildAST("WhileStmt", 5, newAST("while"), newAST("("), $3, newAST(")"), $5);
				}
             ;

IfStmt       :  T_If '(' BoolExpr ')' Stmt OptElse
                { printf("IfStmt -> if ( BoolExpr ) Stmt OptElse \n");
				  $$ = buildAST("IfStmt", 6, newAST("if"), newAST("("), $3, newAST(")"), $5, $6);
				}
             ;

OptElse      :  T_Else Stmt
                { printf("OptElse -> else Stmt\n");
				  $$ = buildAST("OptElse", 2, newAST("else"), $2);
				}
			 |  /* empty */
				{ printf("OptElse -> \n");
				  $$ = NULL;
				}
			 ;

ReturnStmt   :  T_Return
                { printf("ReturnStmt -> return\n");
				  $$ = newAST("return");
				}
             |  T_Return Expr
				{ printf("ReturnStmt -> return Expr \n");
				  $$ = buildAST("ReturnStmt", 2, newAST("return"), $2);
				}
			 ;

PrintStmt    :  T_Print '(' ExprList ')'
                { printf("PrintStmt -> print ( ExprList ) \n");
				  $$ = buildAST("PrintStmt", 4, newAST("print"), newAST("("), $3, newAST(")"));
				}
             ;

BoolExpr     :  Expr
                { printf("BoolExpr -> Expr\n");
				  $$ = $1;
				}
             ;

Expr         :  Constant
                { printf("Expr -> Constant\n");
				  $$ = $1;
				}
             |  LValue
				{ printf("Expr -> LValue\n");
				  $$ = $1;
				}
             |  T_This
				{ printf("Expr -> this\n");
				  $$ = newAST("this");
				}
             |  Call
				{ printf("Expr -> Call\n");
				  $$ = $1;
				}
             |  '(' Expr ')'
				{ printf("Expr -> ( Expr ) \n");
				  $$ = buildAST("Expr", 3, newAST("("), $2, newAST(")"));
				}
             |  Expr '+' Expr
				{ printf("Expr -> Expr + Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("+"), $3);
				}
             |  Expr '-' Expr
				{ printf("Expr -> Expr - Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("-"), $3);
				}
             |  Expr '*' Expr
				{ printf("Expr -> Expr * Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("*"), $3);
				}
			 |  Expr '/' Expr
				{ printf("Expr -> Expr / Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("/"), $3);
				}
             |  Expr '%' Expr
				{ printf("Expr -> Expr %% Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("%"), $3);
				}
			 |  '-' Expr %prec UMINUS
				{ printf("Expr -> - Expr \n");
				  $$ = buildAST("Expr", 2, newAST("-"), $2);
				}
             |  Expr '<' Expr
				{ printf("Expr -> Expr < Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("<"), $3);
				}
             |  Expr T_LessEqual Expr
				{ printf("Expr -> Expr <= Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("<="), $3);
				}
			 |  Expr '>' Expr
				{ printf("Expr -> Expr > Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST(">"), $3);
				}
             |  Expr T_GreaterEqual Expr
				{ printf("Expr -> Expr >= Expr\n");
				  $$ = buildAST("Expr", 3, $1, newAST(">="), $3);
				}
             |  Expr T_Equal Expr
				{ printf("Expr -> Expr == Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("=="), $3);
				}
             |  Expr T_NotEqual Expr
				{ printf("Expr -> Expr != Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("!="), $3);
				}
			 |  Expr T_And Expr
				{ printf("Expr -> Expr && Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("&&"), $3);
				}
			 |  Expr T_Or Expr
				{ printf("Expr -> Expr || Expr \n");
				  $$ = buildAST("Expr", 3, $1, newAST("||"), $3);
				}
		     |  '!' Expr
				{ printf("Expr -> ! Expr \n");
				  $$ = buildAST("Expr", 2, newAST("!"), $2);
				}
			 |  T_ReadInteger '(' ')'
				{ printf("Expr -> ReadInteger ( ) \n");
				  $$ = buildAST("Expr", 3, newAST("readInteger"), newAST("("), newAST(")"));
				}
			 |  T_ReadLine '(' ')'
				{ printf("Expr -> ReadLine ( ) \n");
				  $$ = buildAST("Expr", 3, newAST("readLine"), newAST("("), newAST(")"));
				}
			 |  T_New '(' T_Identifier ')'
				{ printf("Expr -> New ( identifier ) \n");
				  $$ = buildAST("Expr", 4, newAST("new"), newAST("("), newAST("identifier"), newAST(")"));
				}
			 |  T_NewArray '(' Expr ',' Type ')'
				{ printf("Expr -> NewArray ( Expr , Type )\n");
				  $$ = buildAST("Expr", 6, newAST("newArray"), newAST("("), $3, newAST(","), $5, newAST(")"));
				}
             ;

Constant     :  T_IntConstant
                { printf("Constant -> intConstant\n");
				  $$ = newAST("intConstant");
				}
             |  T_DoubleConstant
				{ printf("Constant -> doubleConstant\n");
				  $$ = newAST("doubleConstant")
				}
             |  T_BoolConstant
				{ printf("Constant -> boolConstant\n");
				  $$ = newAST("boolConstant")
				}
			 |  T_StringConstant
				{ printf("Constant -> stringConstant\n");
				  $$ = newAST("stringConstant")
				}
			 |  T_Null
				{ printf("Constant -> null\n");
				  $$ = newAST("")
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
		struct ast* child = va_arg(valist, struct ast*);
		addChild(root, child);
	}
	va_end(valist);
	return root;
}

struct ast* buildRaw(char* rootKey, int n, ...) {
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


