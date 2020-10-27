/*parser.y ���readme.md
 *
 *bison�����ļ������ڲ���parser
 *
 *pp2:�������ֻ�����parser�Ĺ�Լ��������ֻ��Ҫ��֤�����ļ��Ƿ����
 *decaf���Ե��ķ������ѹ�Լ���������
 *
*/
%{

/*
 *ͬflexһ������һ��%{ %}�ڲ��ĳ��򽫱�ֱ��copy��parser_tab.h/c��
 *���Կ��Խ�Ҫinclude��ͷ�ļ���ȫ�ֱ����ŵ������
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <process.h>	
#include <stdarg.h>
#include "scanner.h"
#include "AST.h"
#include "hashtable.h"

// ����ast root
extern struct ast* root;
// ����map
map_t map;
// ����buildAST(�ɱ��)
struct ast* buildAST(char* rootKey, int n, ...);
// �����ж��ս��, c��û��bool����0���0��ʾ
int isTermination(char* key);

%}

/*
 *�����������Զ���tokens,types,precedence �� associativity�ȡ�
*/

/*
 *��program��ʼ��Լ
*/
%start Program

/*
 *yylval
 *------
 *�������ȫ�ֱ���yylval�����������Լ��ķ��ս����
*/
%union {			/*bison���Դ���������в���yylval�Ķ��� union��ʾ��parser�У���ÿ���ڵ㶼������һ�������Ľṹ�壬���û�ʹ��*/
  int integerConstant;
  int boolConstant;
  const char *stringConstant;
  double doubleConstant;
  char identifier[128];
  struct ast* a;   /* ���ast */
}

/*Tokens
 *------
 *������Ǹ���bison��Ҫ�õ���token���͡�
 *bison���Ը���Щ���Ͷ���Ψһ�����ֲ����#define ��parser_tab.h�ļ��С�
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
 *����������ȼ��ͽ����
 *Note: NO SPACE between % and nonassoc, left, right!!!!!
*/



/*
 * %type <a> ��ʾ������Щ�ڵ��union�У�������a�������������ֵ��Ĭ�ϲ���$$����$$��a��������ͣ�
 * Ҫ����ast�� �Ͱѳ����ս�����ȫ��token����a����ֵ
 * ��parser_tab.c�У����Կ���������� yyval.a = buildAST("DeclList", 2, "DeclList", "Decl");
 * ��yyval��������union��������ݽṹ
 */
%type <a> Program DeclList Decl VariableDecl Variable Type FunctionDecl Formals 
%type <a> VariableList FunctionDefn ClassDefn OptExtends FieldList Field StmtBlock StmtList Stmt SimpleStmt
%type <a> LValue Call OptReceiver Actuals ExprList ForStmt WhileStmt IfStmt OptElse ReturnStmt PrintStmt
%type <a> BoolExpr Expr Constant
%%
/*
 *�����д����Ĺ���Ͷ���
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
 *�﷨���򵽴�Ϊֹ��
 *���������Լ�����ĺ�������Щ��������ֱ�ӱ�copy��parser_tab.c�ļ��У�
 *�������ҪһЩ�����ĺ���������д�������
*/
void Inityyparse(void) {
}
/**
 * ����ast��map�洢���ʹ�ù��ı�ʶ
 * Variable -> Type identifier ������У� ÿ����map��Ѱ�� -> �ұ� �ļǺţ�������ھ�remove��Ȼ�󹹽�ast������ -> ��ߵĸ�put��map
 * ��������ԭ���ǣ� bison��LALR(1) �Ե����Ϸ���������Ҳ�Ǻ�����ʶ�������
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


