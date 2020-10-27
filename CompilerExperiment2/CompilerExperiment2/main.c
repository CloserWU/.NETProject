/*
main.c
   定义main()主函数
   整个项目的流程为，修改scanner.l(已经修改完成) 和parser.y文件，然后
   运行debug.bat，用bision解析parser.y和scanner.l，生成lex.yy.c和parser_tab.h和parser_tab.c
   因为生成的是C文件，所以main在调用时，也需要声明为c文件，否则C中extern的属性，cpp中访问不到
   然后运行main.c，输入decaf文件，进行解析，并输出

   项目源文件有且仅有 AST.h AST.c hashtable.h hashtable.c graphviz.h graphviz_utility.h
   graphviz.cpp main.c scanner.l parser.y parser.h scanner.h
   其他文件是生成出来的
*/
#include "scanner.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "AST.h"
#include "hashtable.h"
#include <assert.h>
#include "graphviz.h"
#include "draw.h"


/*
	输入流，默认为stdin,本程序中为指定的文件
*/
extern FILE * yyin;
// 全局hashmap， 用于存放未被使用的 -> 右侧token，在main中初始化，在parser.y中使用
extern map_t map;
// 获取parser.y的全局ast根节点，用于打印和画图
struct ast* root;


/*
	Function main()
	--------------
	首先根据参数确定输入的来源，然后调用Inityylex()和yyparse进行语法分析。

	C中不能调用C++，需采取一定办法， 详见graphviz.h
	全局变量的声明加上extern，其他文件中使用时不需要加上extern，main中声明了map和yyin全局常量
	会在parser.y 和 parser_tab.h/c 中被使用
	而parser.y中定义root常量，在main.c里使用。
*/
int main(int argc, char *argv[])
{
	// 新建hashmap
	map = hashmap_new();
	if (root == NULL) {
		printf("------------    NULL   ------------------------\n");
	}
	else {
		printf("&&&&&&&&&&&&&&&&&&&&&& %s &&&&&&&&&&&&&&&&&&\n", root->val);
	}
	FILE * fIn; 
	switch(argc)
	{
	case 1: 					/*默认为test.decaf*/
    		fIn=fopen("samples\\functions.decaf","r");
			if(fIn==NULL)
			{
				printf("default file not found\n");
				exit(1);
			}
			yyin = fIn;
    		break;
    case 2: 
    	    if ((fIn = fopen(argv[1],"r")) == NULL)
    	    {
            	printf("File %s not found.\n",argv[1]);
             	exit(1);
            }
            else 
            	yyin=fIn;
            break;
	default:
		printf("useage:pp2 [filename]\n");
		exit(1);
	}
	// 引用的函数在其他文件 scanner.h parser.h
	Inityylex();
	Inityyparse();
	// 返回值是int，不知代表什么
	int c = yyparse(); // c = 0
	fclose(fIn);

	printf("\n\n\n\n\n\n");

	if (root == NULL) {
		printf("------------    NULL   ------------------------\n");
	}
	else {
		// 根据root画出ast
		drawAST(root);
		printf("       SHOW TIME\n , length of map is %d \n", hashmap_length(map));
		// 根据root按文件树格式打印
		printAST(root);
	}

	
	return 0;
}



