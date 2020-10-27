
/*  A Bison parser, made from parser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define YYLSP_NEEDED

#define	T_Void	258
#define	T_Bool	259
#define	T_Int	260
#define	T_Double	261
#define	T_String	262
#define	T_Class	263
#define	T_LessEqual	264
#define	T_GreaterEqual	265
#define	T_Equal	266
#define	T_NotEqual	267
#define	T_And	268
#define	T_Or	269
#define	T_Null	270
#define	T_Extends	271
#define	T_This	272
#define	T_While	273
#define	T_For	274
#define	T_If	275
#define	T_Else	276
#define	T_Return	277
#define	T_Break	278
#define	T_Identifier	279
#define	T_StringConstant	280
#define	T_IntConstant	281
#define	T_DoubleConstant	282
#define	T_BoolConstant	283
#define	T_New	284
#define	T_NewArray	285
#define	T_Print	286
#define	T_ReadInteger	287
#define	T_ReadLine	288
#define	UMINUS	289

#line 9 "parser.y"


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


#line 49 "parser.y"
typedef union {			/*bison可以从这个定义中产生yylval的定义 union表示在parser中，给每个节点都创造了一个这样的结构体，供用户使用*/
  int integerConstant;
  int boolConstant;
  const char *stringConstant;
  double doubleConstant;
  char identifier[128];
  struct ast* a;   /* 添加ast */
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		164
#define	YYFLAG		-32768
#define	YYNTBASE	53

#define YYTRANSLATE(x) ((unsigned)(x) <= 289 ? yytranslate[x] : 85)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    42,     2,     2,     2,    41,     2,     2,    46,
    47,    40,    37,    34,    38,    48,    39,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    49,    36,
    52,    35,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    44,     2,    45,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    50,     2,    51,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    43
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     6,     8,    10,    12,    14,    17,    20,
    22,    24,    26,    28,    30,    33,    37,    44,    46,    47,
    51,    53,    60,    67,    70,    71,    74,    75,    77,    79,
    81,    85,    88,    89,    91,    94,    96,    98,   100,   103,
   106,   108,   112,   114,   115,   118,   123,   129,   132,   133,
   135,   136,   140,   142,   152,   158,   165,   168,   169,   171,
   174,   179,   181,   183,   185,   187,   189,   193,   197,   201,
   205,   209,   213,   216,   220,   224,   228,   232,   236,   240,
   244,   248,   251,   255,   259,   264,   271,   273,   275,   277,
   279
};

static const short yyrhs[] = {    54,
     0,    54,    55,     0,     0,    59,     0,    62,     0,    63,
     0,    56,     0,    57,    49,     0,    58,    24,     0,     5,
     0,     6,     0,     4,     0,     7,     0,     3,     0,     8,
    24,     0,    58,    44,    45,     0,    58,    24,    46,    60,
    47,    49,     0,    61,     0,     0,    61,    34,    57,     0,
    57,     0,    58,    24,    46,    60,    47,    67,     0,     8,
    24,    64,    50,    65,    51,     0,    16,    24,     0,     0,
    65,    66,     0,     0,    56,     0,    59,     0,    62,     0,
    50,    68,    51,     0,    68,    69,     0,     0,    56,     0,
    70,    49,     0,    78,     0,    77,     0,    76,     0,    80,
    49,     0,    81,    49,     0,    67,     0,    71,    52,    83,
     0,    83,     0,     0,    73,    24,     0,    83,    44,    83,
    45,     0,    73,    24,    46,    74,    47,     0,    83,    48,
     0,     0,    75,     0,     0,    75,    34,    83,     0,    83,
     0,    19,    46,    70,    49,    82,    49,    70,    47,    69,
     0,    18,    46,    82,    47,    69,     0,    20,    46,    82,
    47,    69,    79,     0,    21,    69,     0,     0,    22,     0,
    22,    83,     0,    31,    46,    75,    47,     0,    83,     0,
    84,     0,    71,     0,    17,     0,    72,     0,    46,    83,
    47,     0,    83,    37,    83,     0,    83,    38,    83,     0,
    83,    40,    83,     0,    83,    39,    83,     0,    83,    41,
    83,     0,    38,    83,     0,    83,    36,    83,     0,    83,
     9,    83,     0,    83,    35,    83,     0,    83,    10,    83,
     0,    83,    11,    83,     0,    83,    12,    83,     0,    83,
    13,    83,     0,    83,    14,    83,     0,    42,    83,     0,
    32,    46,    47,     0,    33,    46,    47,     0,    29,    46,
    24,    47,     0,    30,    46,    83,    34,    58,    47,     0,
    26,     0,    27,     0,    28,     0,    25,     0,    15,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   104,   113,   117,   123,   127,   131,   135,   141,   147,   153,
   157,   161,   165,   169,   173,   177,   183,   189,   193,   199,
   203,   209,   215,   221,   225,   231,   235,   241,   245,   249,
   255,   261,   265,   271,   275,   279,   283,   287,   291,   295,
   299,   305,   309,   313,   319,   323,   329,   335,   339,   345,
   349,   355,   359,   365,   371,   377,   383,   387,   393,   397,
   403,   409,   415,   419,   423,   427,   431,   435,   439,   443,
   447,   451,   455,   459,   463,   467,   471,   475,   479,   483,
   487,   491,   495,   499,   503,   507,   513,   517,   521,   525,
   529
};

static const char * const yytname[] = {   "$","error","$undefined.","T_Void",
"T_Bool","T_Int","T_Double","T_String","T_Class","T_LessEqual","T_GreaterEqual",
"T_Equal","T_NotEqual","T_And","T_Or","T_Null","T_Extends","T_This","T_While",
"T_For","T_If","T_Else","T_Return","T_Break","T_Identifier","T_StringConstant",
"T_IntConstant","T_DoubleConstant","T_BoolConstant","T_New","T_NewArray","T_Print",
"T_ReadInteger","T_ReadLine","','","'>'","'<'","'+'","'-'","'/'","'*'","'%'",
"'!'","UMINUS","'['","']'","'('","')'","'.'","';'","'{'","'}'","'='","Program",
"DeclList","Decl","VariableDecl","Variable","Type","FunctionDecl","Formals",
"VariableList","FunctionDefn","ClassDefn","OptExtends","FieldList","Field","StmtBlock",
"StmtList","Stmt","SimpleStmt","LValue","Call","OptReceiver","Actuals","ExprList",
"ForStmt","WhileStmt","IfStmt","OptElse","ReturnStmt","PrintStmt","BoolExpr",
"Expr","Constant",""
};
#endif

static const short yyr1[] = {     0,
    53,    54,    54,    55,    55,    55,    55,    56,    57,    58,
    58,    58,    58,    58,    58,    58,    59,    60,    60,    61,
    61,    62,    63,    64,    64,    65,    65,    66,    66,    66,
    67,    68,    68,    69,    69,    69,    69,    69,    69,    69,
    69,    70,    70,    70,    71,    71,    72,    73,    73,    74,
    74,    75,    75,    76,    77,    78,    79,    79,    80,    80,
    81,    82,    83,    83,    83,    83,    83,    83,    83,    83,
    83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
    83,    83,    83,    83,    83,    83,    84,    84,    84,    84,
    84
};

static const short yyr2[] = {     0,
     1,     2,     0,     1,     1,     1,     1,     2,     2,     1,
     1,     1,     1,     1,     2,     3,     6,     1,     0,     3,
     1,     6,     6,     2,     0,     2,     0,     1,     1,     1,
     3,     2,     0,     1,     2,     1,     1,     1,     2,     2,
     1,     3,     1,     0,     2,     4,     5,     2,     0,     1,
     0,     3,     1,     9,     5,     6,     2,     0,     1,     2,
     4,     1,     1,     1,     1,     1,     3,     3,     3,     3,
     3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
     3,     2,     3,     3,     4,     6,     1,     1,     1,     1,
     1
};

static const short yydefact[] = {     3,
     1,    14,    12,    10,    11,    13,     0,     2,     7,     0,
     0,     4,     5,     6,    15,     8,     9,     0,     0,     0,
    19,    16,    24,    27,     0,    21,     0,     0,    18,     0,
    15,     9,     0,     0,    23,    28,    29,    30,    26,    17,
    33,    22,    20,    44,    91,    65,     0,     0,     0,    49,
    90,    87,    88,    89,     0,     0,     0,     0,     0,    49,
    49,    49,    31,    34,    41,    32,     0,    64,    66,     0,
    38,    37,    36,     0,     0,    43,    63,    49,    44,    49,
    64,    60,     0,    49,    49,     0,     0,    73,    82,     0,
    35,    49,    45,    39,    40,    49,    49,    49,    49,    49,
    49,    49,    49,    49,    49,    49,    49,    49,    49,    48,
     0,    62,     0,     0,     0,     0,     0,    53,    83,    84,
    67,    42,    49,    75,    77,    78,    79,    80,    81,    76,
    74,    68,    69,    71,    70,    72,     0,    44,    49,    44,
    85,     0,    49,    61,     0,    50,    46,    55,     0,    58,
     0,    52,    47,    44,    44,    56,    86,     0,    57,    44,
    54,     0,     0,     0
};

static const short yydefgoto[] = {   162,
     1,     8,    64,    10,    27,    12,    28,    29,    13,    14,
    20,    30,    39,    65,    44,    66,    67,    81,    69,    70,
   145,   117,    71,    72,    73,   156,    74,    75,   111,    76,
    77
};

static const short yypact[] = {-32768,
    95,-32768,-32768,-32768,-32768,-32768,    23,-32768,-32768,    24,
   -17,-32768,-32768,-32768,    -4,-32768,     2,    27,    61,    37,
   156,-32768,-32768,-32768,    65,-32768,   -14,    44,    59,    13,
-32768,-32768,   -24,   156,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   101,-32768,-32768,    48,    64,    67,   329,
-32768,-32768,-32768,-32768,    68,    69,    76,    78,    92,   401,
   401,   401,-32768,-32768,-32768,-32768,    93,    94,-32768,   121,
-32768,-32768,-32768,    99,   100,   247,-32768,   401,   379,   401,
-32768,   247,   126,   401,   401,   119,   124,    40,    40,   192,
-32768,   401,   127,-32768,-32768,   401,   401,   401,   401,   401,
   401,   401,   401,   401,   401,   401,   401,   401,   401,-32768,
   137,   247,   136,   139,   140,   207,   -25,   247,-32768,-32768,
-32768,   247,   355,    42,    42,   280,   280,   301,   261,    42,
    42,    96,    96,    40,    40,    40,    30,   150,   401,   150,
-32768,   156,   401,-32768,   142,   157,-32768,-32768,   141,   172,
   -12,   247,-32768,   379,   150,-32768,-32768,   147,-32768,   150,
-32768,   195,   197,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,     4,   -10,    -1,   168,-32768,-32768,   169,-32768,
-32768,-32768,-32768,   174,-32768,  -132,   -77,   -43,-32768,-32768,
-32768,    85,-32768,-32768,-32768,-32768,-32768,-32768,   -76,   -47,
-32768
};


#define	YYLAST		447


static const short yytable[] = {    11,
    68,   113,    82,   114,     9,   148,    17,   150,   143,    32,
    26,    19,    88,    89,    90,     2,     3,     4,     5,     6,
    25,   144,   159,    43,    40,    41,    18,   161,    11,    18,
   112,    18,   112,    36,   157,    68,   116,   118,    96,    97,
    98,    99,   100,   101,   122,   -25,    15,    21,   124,   125,
   126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   149,    35,   102,   103,   104,   105,   106,   107,
   108,    22,    16,   109,   147,   118,   158,   110,   104,   105,
   106,   107,   108,   109,    23,   109,    24,   110,    31,   110,
    33,   112,    34,    78,    68,   152,    68,     2,     3,     4,
     5,     6,     7,     2,     3,     4,     5,     6,    25,    79,
    68,    68,    80,    83,    84,    45,    68,    46,    47,    48,
    49,    85,    50,    86,   -49,    51,    52,    53,    54,    55,
    56,    57,    58,    59,   106,   107,   108,    87,    60,   109,
   151,    91,    61,   110,    93,    92,    62,    94,    95,   115,
    41,    63,     2,     3,     4,     5,     6,    25,     2,     3,
     4,     5,     6,    25,    45,   119,    46,    47,    48,    49,
   120,    50,   123,   -49,    51,    52,    53,    54,    55,    56,
    57,    58,    59,   138,   139,   140,   141,    60,   153,   154,
   143,    61,   155,   160,   163,    62,   164,    37,    38,    41,
    96,    97,    98,    99,   100,   101,    42,   146,     0,     0,
     0,     0,     0,     0,     0,    96,    97,    98,    99,   100,
   101,     0,     0,     0,     0,     0,   102,   103,   104,   105,
   106,   107,   108,     0,     0,   109,     0,     0,   121,   110,
   142,   102,   103,   104,   105,   106,   107,   108,     0,     0,
   109,     0,     0,     0,   110,    96,    97,    98,    99,   100,
   101,     0,     0,     0,     0,     0,     0,     0,     0,    96,
    97,    98,    99,   100,     0,     0,     0,     0,     0,     0,
     0,   102,   103,   104,   105,   106,   107,   108,    96,    97,
   109,     0,     0,     0,   110,   102,   103,   104,   105,   106,
   107,   108,     0,     0,   109,     0,     0,     0,   110,    96,
    97,    98,    99,     0,   102,   103,   104,   105,   106,   107,
   108,     0,     0,   109,     0,     0,     0,   110,     0,     0,
     0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
   107,   108,     0,    45,   109,    46,     0,     0,   110,     0,
     0,     0,     0,    51,    52,    53,    54,    55,    56,     0,
    58,    59,     0,     0,     0,     0,    60,     0,     0,    45,
    61,    46,     0,     0,    62,     0,     0,   -59,     0,    51,
    52,    53,    54,    55,    56,     0,    58,    59,     0,     0,
     0,     0,    60,    45,     0,    46,    61,     0,     0,     0,
    62,   -51,   -49,    51,    52,    53,    54,    55,    56,     0,
    58,    59,     0,     0,     0,    45,    60,    46,     0,     0,
    61,     0,     0,     0,    62,    51,    52,    53,    54,    55,
    56,     0,    58,    59,     0,     0,     0,     0,    60,     0,
     0,     0,    61,     0,     0,     0,    62
};

static const short yycheck[] = {     1,
    44,    79,    50,    80,     1,   138,    24,   140,    34,    24,
    21,    16,    60,    61,    62,     3,     4,     5,     6,     7,
     8,    47,   155,    34,    49,    50,    44,   160,    30,    44,
    78,    44,    80,    30,    47,    79,    84,    85,     9,    10,
    11,    12,    13,    14,    92,    50,    24,    46,    96,    97,
    98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
   108,   109,   139,    51,    35,    36,    37,    38,    39,    40,
    41,    45,    49,    44,    45,   123,   154,    48,    37,    38,
    39,    40,    41,    44,    24,    44,    50,    48,    24,    48,
    47,   139,    34,    46,   138,   143,   140,     3,     4,     5,
     6,     7,     8,     3,     4,     5,     6,     7,     8,    46,
   154,   155,    46,    46,    46,    15,   160,    17,    18,    19,
    20,    46,    22,    46,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    39,    40,    41,    46,    38,    44,
   142,    49,    42,    48,    24,    52,    46,    49,    49,    24,
    50,    51,     3,     4,     5,     6,     7,     8,     3,     4,
     5,     6,     7,     8,    15,    47,    17,    18,    19,    20,
    47,    22,    46,    24,    25,    26,    27,    28,    29,    30,
    31,    32,    33,    47,    49,    47,    47,    38,    47,    49,
    34,    42,    21,    47,     0,    46,     0,    30,    30,    50,
     9,    10,    11,    12,    13,    14,    33,   123,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
    14,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
    39,    40,    41,    -1,    -1,    44,    -1,    -1,    47,    48,
    34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
    44,    -1,    -1,    -1,    48,     9,    10,    11,    12,    13,
    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
    10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    35,    36,    37,    38,    39,    40,    41,     9,    10,
    44,    -1,    -1,    -1,    48,    35,    36,    37,    38,    39,
    40,    41,    -1,    -1,    44,    -1,    -1,    -1,    48,     9,
    10,    11,    12,    -1,    35,    36,    37,    38,    39,    40,
    41,    -1,    -1,    44,    -1,    -1,    -1,    48,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
    40,    41,    -1,    15,    44,    17,    -1,    -1,    48,    -1,
    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    -1,
    32,    33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    15,
    42,    17,    -1,    -1,    46,    -1,    -1,    49,    -1,    25,
    26,    27,    28,    29,    30,    -1,    32,    33,    -1,    -1,
    -1,    -1,    38,    15,    -1,    17,    42,    -1,    -1,    -1,
    46,    47,    24,    25,    26,    27,    28,    29,    30,    -1,
    32,    33,    -1,    -1,    -1,    15,    38,    17,    -1,    -1,
    42,    -1,    -1,    -1,    46,    25,    26,    27,    28,    29,
    30,    -1,    32,    33,    -1,    -1,    -1,    -1,    38,    -1,
    -1,    -1,    42,    -1,    -1,    -1,    46
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)
#include <alloca.h>
#else /* not sparc */
#if (defined (MSDOS) || defined(WIN32)) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


#line 169 "bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 105 "parser.y"
{ printf("Program -> DeclList\n");
				  /* $$ = func($1...)*/
				  yyval.a = buildAST("Program", 1, "DeclList");
				  root = yyval.a;
				  yylsp[0]
				;
    break;}
case 2:
#line 114 "parser.y"
{ printf("DeclList -> DeclList Decl\n");
				  yyval.a = buildAST("DeclList", 2, "DeclList", "Decl");
				;
    break;}
case 3:
#line 118 "parser.y"
{ printf("DeclList ->\n"); 
				  yyval.a = buildAST("DeclList", 1, "null");
				;
    break;}
case 4:
#line 124 "parser.y"
{ printf("Decl -> FunctionDecl\n");
				  yyval.a = buildAST("Decl", 1, "FunctionDecl");
				;
    break;}
case 5:
#line 128 "parser.y"
{ printf("Decl -> FunctionDefn\n");
				  yyval.a = buildAST("Decl", 1, "FunctionDefn");
				;
    break;}
case 6:
#line 132 "parser.y"
{ printf("Decl -> ClassDefn\n");
				  yyval.a = buildAST("Decl", 1, "ClassDefn");
				;
    break;}
case 7:
#line 136 "parser.y"
{ printf("Decl -> VaruableDecl\n");
				  yyval.a = buildAST("Decl", 1, "VariableDecl");
				;
    break;}
case 8:
#line 142 "parser.y"
{ printf("VariableDecl -> Variable ;\n");
				  yyval.a = buildAST("VariableDecl", 2, "Variable", ";");
				;
    break;}
case 9:
#line 148 "parser.y"
{ printf("Variable -> Type identifier\n");
				  yyval.a = buildAST("Variable", 2, "Type", "identifier");
				;
    break;}
case 10:
#line 154 "parser.y"
{ printf("Type -> int\n");
				  yyval.a = buildAST("Type", 1, "int");
				;
    break;}
case 11:
#line 158 "parser.y"
{ printf("Type -> double\n");
				  yyval.a = buildAST("Type", 1, "double");
				;
    break;}
case 12:
#line 162 "parser.y"
{ printf("Type -> bool\n");
				  yyval.a = buildAST("Type", 1, "bool");
				;
    break;}
case 13:
#line 166 "parser.y"
{ printf("Type -> string\n");
				  yyval.a = buildAST("Type", 1, "string");
				;
    break;}
case 14:
#line 170 "parser.y"
{ printf("Type -> void\n");
				  yyval.a = buildAST("Type", 1, "void");
				;
    break;}
case 15:
#line 174 "parser.y"
{ printf("Type -> class identifier\n");
				  yyval.a = buildAST("Type", 2, "class", "identifier");
				;
    break;}
case 16:
#line 178 "parser.y"
{ printf("Type -> Type []\n");
				  yyval.a = buildAST("Type", 3, "Type", "[", "]");
				;
    break;}
case 17:
#line 184 "parser.y"
{ printf("FunctionDecl -> Type identifier ( Formals ) ;\n");
				  yyval.a = buildAST("FunctionDecl", 6, "Type", "identifier", "(", "Formals", ")", ";");
				;
    break;}
case 18:
#line 190 "parser.y"
{ printf("Formals -> VariableList \n");
				  yyval.a = buildAST("Formals", 1, "VariableList");
				;
    break;}
case 19:
#line 194 "parser.y"
{ printf("Formals -> \n");
				  yyval.a = buildAST("Formals", 1, "null");
				;
    break;}
case 20:
#line 200 "parser.y"
{ printf("VariableList -> VariableList , Variable\n");
				  yyval.a = buildAST("VariableList", 3, "VariableList", ",", "Variable");
				;
    break;}
case 21:
#line 204 "parser.y"
{ printf("VariableList -> Variable\n");
				  yyval.a = buildAST("VariableList", 1, "Variable");
				;
    break;}
case 22:
#line 210 "parser.y"
{ printf("FunctionDefn -> Type identifier ( Formals ) StmtBlock\n");
				  yyval.a = buildAST("FunctionDefn", 6, "Type", "identifier", "(", "Formals", ")", "StmtBlock");
				;
    break;}
case 23:
#line 216 "parser.y"
{ printf("ClassDefn -> class identifier OptExtends { FieldList } \n");
				  yyval.a = buildAST("ClassDefn", 6, "class", "identifier", "OptExtends", "{", "FieldList", "}");
				;
    break;}
case 24:
#line 222 "parser.y"
{ printf("OptExtends -> extends identifier\n");
			     yyval.a = buildAST("OptExtends", 2, "extends", "identifier");
			   ;
    break;}
case 25:
#line 226 "parser.y"
{ printf("OptExtends -> \n");
			     yyval.a = buildAST("OptExtends", 1, "null");
			   ;
    break;}
case 26:
#line 232 "parser.y"
{ printf("FieldList -> FieldList Field\n");
				  yyval.a = buildAST("FieldList", 2, "FieldList", "Field");
				;
    break;}
case 27:
#line 236 "parser.y"
{ printf("FieldList -> \n");
				  yyval.a = buildAST("FieldList", 1, "null");
				;
    break;}
case 28:
#line 242 "parser.y"
{ printf("Field -> VariableDecl\n");
				  yyval.a = buildAST("Field", 1, "VariableDecl");
				;
    break;}
case 29:
#line 246 "parser.y"
{ printf("Field -> FunctionDecl\n");
				  yyval.a = buildAST("Field", 1, "FunctionDecl");
				;
    break;}
case 30:
#line 250 "parser.y"
{ printf("Field -> FunctionDefn\n");
				  yyval.a = buildAST("Field", 1, "FunctionDefn");
				;
    break;}
case 31:
#line 256 "parser.y"
{ printf("StmtBlock -> { StmtList } \n");
				  yyval.a = buildAST("StmtBlock", 3, "{", "StmtList", "}");
				;
    break;}
case 32:
#line 262 "parser.y"
{ printf("StmtList -> StmtList Stmt\n");
				  yyval.a = buildAST("StmtList", 2, "StmtList", "Stmt");
				;
    break;}
case 33:
#line 266 "parser.y"
{ printf("StmtList ->\n");
				  yyval.a = buildAST("StmtList", 1, "null");
				;
    break;}
case 34:
#line 272 "parser.y"
{ printf("Stmt -> VariableDecl\n");
				  yyval.a = buildAST("Stmt", 1, "VariableDecl");
				;
    break;}
case 35:
#line 276 "parser.y"
{ printf("Stmt -> SimpleStmt ;\n");
				  yyval.a = buildAST("Stmt", 2, "SimpleStmt", ";");
				;
    break;}
case 36:
#line 280 "parser.y"
{ printf("Stmt -> IfStmt\n");
				  yyval.a = buildAST("Stmt", 1, "IfStmt");
				;
    break;}
case 37:
#line 284 "parser.y"
{ printf("Stmt -> WhileStmt\n");
				  yyval.a = buildAST("Stmt", 1, "WhileStmt");
				;
    break;}
case 38:
#line 288 "parser.y"
{ printf("Stmt -> ForStmt\n");
				  yyval.a = buildAST("Stmt", 1, "ForStmt");
				;
    break;}
case 39:
#line 292 "parser.y"
{ printf("Stmt -> ReturnStmt ;\n");
				  yyval.a = buildAST("Stmt", 2, "ReturnStmt", ";");
				;
    break;}
case 40:
#line 296 "parser.y"
{ printf("Stmt -> PrintStmt ;\n");
				  yyval.a = buildAST("Stmt", 2, "PrintStmt", ";");
				;
    break;}
case 41:
#line 300 "parser.y"
{ printf("Stmt -> StmtBlock\n");
				  yyval.a = buildAST("Stmt", 1, "StmtBlock");
				;
    break;}
case 42:
#line 306 "parser.y"
{ printf("SimpleStmt -> LValue = Expr\n");
				  yyval.a = buildAST("SimpleStmt", 3, "LValue", "=", "Expr");
				;
    break;}
case 43:
#line 310 "parser.y"
{ printf("SimpleStmt -> Expr\n");
				  yyval.a = buildAST("SimpleStmt", 1, "Expr");
				;
    break;}
case 44:
#line 314 "parser.y"
{ printf("SimpleStmt -> \n");
				  yyval.a = buildAST("SimpleStmt", 1, "null");
				;
    break;}
case 45:
#line 320 "parser.y"
{ printf("LValue -> OptReceiver identifier\n");
				  yyval.a = buildAST("LValue", 2, "OptReceiver", "identifier");
				;
    break;}
case 46:
#line 324 "parser.y"
{ printf("LValue -> Expr [ Expr ] \n");
				  yyval.a = buildAST("LValue", 4, "Expr", "[", "Expr", "]");
				;
    break;}
case 47:
#line 330 "parser.y"
{ printf("Call -> OptReceiver identifier ( Actuals )\n");
				  yyval.a = buildAST("Call", 5, "OptReceiver", "identifier", "(", "Actuals", ")");
				;
    break;}
case 48:
#line 336 "parser.y"
{ printf("OptReceiver -> Expr .\n");
				  yyval.a = buildAST("OptReceiver", 2, "Expr", ".");
				;
    break;}
case 49:
#line 340 "parser.y"
{ printf("OptReceiver -> \n");
			     yyval.a = buildAST("OptReceiver", 1, "null");
			   ;
    break;}
case 50:
#line 346 "parser.y"
{ printf("Actuals -> ExprList\n");
				  yyval.a = buildAST("Actuals", 1, "ExprList");
				;
    break;}
case 51:
#line 350 "parser.y"
{ printf("Actuals -> \n");
				  yyval.a = buildAST("Actuals", 1, "null");
				;
    break;}
case 52:
#line 356 "parser.y"
{ printf("ExprList -> ExprList , Expr\n");
				  yyval.a = buildAST("ExprList", 3, "ExprList", ",", "Expr");
				;
    break;}
case 53:
#line 360 "parser.y"
{ printf("ExprList -> Expr\n");
				  yyval.a = buildAST("ExprList", 1, "Expr");
				;
    break;}
case 54:
#line 366 "parser.y"
{ printf("ForStmt -> for ( SimpleStmt ; BoolExpr ; SimpleStmt ) Stmt \n");
				  yyval.a = buildAST("ForStmt", 9, "for", "(", "SimpleStmt", ";", "BoolExpr", ";", "SimpleStmt", ")", "Stmt");
				;
    break;}
case 55:
#line 372 "parser.y"
{ printf("WhileStmt -> while( BoolExpr ) Stmt \n");
				  yyval.a = buildAST("WhileStmt", 5, "while", "(", "BoolExpr", ")", "Stmt");
				;
    break;}
case 56:
#line 378 "parser.y"
{ printf("IfStmt -> if ( BoolExpr ) Stmt OptElse \n");
				  yyval.a = buildAST("IfStmt", 6, "if", "(", "BoolExpr", ")", "Stmt", "OptElse");
				;
    break;}
case 57:
#line 384 "parser.y"
{ printf("OptElse -> else Stmt\n");
				  yyval.a = buildAST("OptElse", 2, "else", "Stmt");
				;
    break;}
case 58:
#line 388 "parser.y"
{ printf("OptElse -> \n");
				  yyval.a = buildAST("OptElse", 1, "null");
				;
    break;}
case 59:
#line 394 "parser.y"
{ printf("ReturnStmt -> return\n");
				  yyval.a = buildAST("ReturnStmt", 1, "retuen");
				;
    break;}
case 60:
#line 398 "parser.y"
{ printf("ReturnStmt -> return Expr \n");
				  yyval.a = buildAST("ReturnStmt", 2, "return", "Expr");
				;
    break;}
case 61:
#line 404 "parser.y"
{ printf("PrintStmt -> print ( ExprList ) \n");
				  yyval.a = buildAST("PrintStmt", 4, "print", "(", "ExprList", ")");
				;
    break;}
case 62:
#line 410 "parser.y"
{ printf("BoolExpr -> Expr\n");
				  yyval.a = buildAST("BoolExpr", 1, "Expr");
				;
    break;}
case 63:
#line 416 "parser.y"
{ printf("Expr -> Constant\n");
				  yyval.a = buildAST("Expr", 1, "Constant");
				;
    break;}
case 64:
#line 420 "parser.y"
{ printf("Expr -> LValue\n");
				 yyval.a = buildAST("Expr", 1, "LValue");
				;
    break;}
case 65:
#line 424 "parser.y"
{ printf("Expr -> this\n");
				  yyval.a = buildAST("Expr", 1, "this");
				;
    break;}
case 66:
#line 428 "parser.y"
{ printf("Expr -> Call\n");
				  yyval.a = buildAST("Expr", 1, "Call");
				;
    break;}
case 67:
#line 432 "parser.y"
{ printf("Expr -> ( Expr ) \n");
				  yyval.a = buildAST("Expr", 3, "(", "Expr", ")");
				;
    break;}
case 68:
#line 436 "parser.y"
{ printf("Expr -> Expr + Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "+", "Expr");
				;
    break;}
case 69:
#line 440 "parser.y"
{ printf("Expr -> Expr - Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "-", "Expr");
				;
    break;}
case 70:
#line 444 "parser.y"
{ printf("Expr -> Expr * Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "*", "Expr");
				;
    break;}
case 71:
#line 448 "parser.y"
{ printf("Expr -> Expr / Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "/", "Expr");
				;
    break;}
case 72:
#line 452 "parser.y"
{ printf("Expr -> Expr %% Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "%", "Expr");
				;
    break;}
case 73:
#line 456 "parser.y"
{ printf("Expr -> - Expr \n");
				  yyval.a = buildAST("Expr", 2, "-", "Expr");
				;
    break;}
case 74:
#line 460 "parser.y"
{ printf("Expr -> Expr < Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "<", "Expr");
				;
    break;}
case 75:
#line 464 "parser.y"
{ printf("Expr -> Expr <= Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "<=", "Expr");
				;
    break;}
case 76:
#line 468 "parser.y"
{ printf("Expr -> Expr > Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", ">", "Expr");
				;
    break;}
case 77:
#line 472 "parser.y"
{ printf("Expr -> Expr >= Expr\n");
				  yyval.a = buildAST("Expr", 3, "Expr", ">=", "Expr");
				;
    break;}
case 78:
#line 476 "parser.y"
{ printf("Expr -> Expr == Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "==", "Expr");
				;
    break;}
case 79:
#line 480 "parser.y"
{ printf("Expr -> Expr != Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "!=", "Expr");
				;
    break;}
case 80:
#line 484 "parser.y"
{ printf("Expr -> Expr && Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "&&", "Expr");
				;
    break;}
case 81:
#line 488 "parser.y"
{ printf("Expr -> Expr || Expr \n");
				  yyval.a = buildAST("Expr", 3, "Expr", "||", "Expr");
				;
    break;}
case 82:
#line 492 "parser.y"
{ printf("Expr -> ! Expr \n");
				  yyval.a = buildAST("Expr", 2, "!", "Expr");
				;
    break;}
case 83:
#line 496 "parser.y"
{ printf("Expr -> ReadInteger ( ) \n");
				  yyval.a = buildAST("Expr", 3, "readInteger", "(", ")");
				;
    break;}
case 84:
#line 500 "parser.y"
{ printf("Expr -> ReadLine ( ) \n");
				  yyval.a = buildAST("Expr", 3, "readLine", "(", ")");
				;
    break;}
case 85:
#line 504 "parser.y"
{ printf("Expr -> New ( identifier ) \n");
				  yyval.a = buildAST("Expr", 4, "new", "(", "identifier", ")");
				;
    break;}
case 86:
#line 508 "parser.y"
{ printf("Expr -> NewArray ( Expr , Type )\n");
				  yyval.a = buildAST("Expr", 6, "newArray", "(", "Expr", ",", "Type", ")");
				;
    break;}
case 87:
#line 514 "parser.y"
{ printf("Constant -> intConstant\n");
				  yyval.a = buildAST("Constant", 1, "intConstant");
				;
    break;}
case 88:
#line 518 "parser.y"
{ printf("Constant -> doubleConstant\n");
				  yyval.a = buildAST("Constant", 1, "doubleConstant");
				;
    break;}
case 89:
#line 522 "parser.y"
{ printf("Constant -> boolConstant\n");
				  yyval.a = buildAST("Constant", 1, "boolConstant");
				;
    break;}
case 90:
#line 526 "parser.y"
{ printf("Constant -> stringConstant\n");
				  yyval.a = buildAST("Constant", 1, "stringConstant");
				;
    break;}
case 91:
#line 530 "parser.y"
{ printf("Constant -> null\n");
				  yyval.a = buildAST("Constant", 1, "null");
				;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 442 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 535 "parser.y"
 
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


