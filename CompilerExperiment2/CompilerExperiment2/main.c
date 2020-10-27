/*
main.c
   ����main()������
   ������Ŀ������Ϊ���޸�scanner.l(�Ѿ��޸����) ��parser.y�ļ���Ȼ��
   ����debug.bat����bision����parser.y��scanner.l������lex.yy.c��parser_tab.h��parser_tab.c
   ��Ϊ���ɵ���C�ļ�������main�ڵ���ʱ��Ҳ��Ҫ����Ϊc�ļ�������C��extern�����ԣ�cpp�з��ʲ���
   Ȼ������main.c������decaf�ļ������н����������

   ��ĿԴ�ļ����ҽ��� AST.h AST.c hashtable.h hashtable.c graphviz.h graphviz_utility.h
   graphviz.cpp main.c scanner.l parser.y parser.h scanner.h
   �����ļ������ɳ�����
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
	��������Ĭ��Ϊstdin,��������Ϊָ�����ļ�
*/
extern FILE * yyin;
// ȫ��hashmap�� ���ڴ��δ��ʹ�õ� -> �Ҳ�token����main�г�ʼ������parser.y��ʹ��
extern map_t map;
// ��ȡparser.y��ȫ��ast���ڵ㣬���ڴ�ӡ�ͻ�ͼ
struct ast* root;


/*
	Function main()
	--------------
	���ȸ��ݲ���ȷ���������Դ��Ȼ�����Inityylex()��yyparse�����﷨������

	C�в��ܵ���C++�����ȡһ���취�� ���graphviz.h
	ȫ�ֱ�������������extern�������ļ���ʹ��ʱ����Ҫ����extern��main��������map��yyinȫ�ֳ���
	����parser.y �� parser_tab.h/c �б�ʹ��
	��parser.y�ж���root��������main.c��ʹ�á�
*/
int main(int argc, char *argv[])
{
	// �½�hashmap
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
	case 1: 					/*Ĭ��Ϊtest.decaf*/
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
	// ���õĺ����������ļ� scanner.h parser.h
	Inityylex();
	Inityyparse();
	// ����ֵ��int����֪����ʲô
	int c = yyparse(); // c = 0
	fclose(fIn);

	printf("\n\n\n\n\n\n");

	if (root == NULL) {
		printf("------------    NULL   ------------------------\n");
	}
	else {
		// ����root����ast
		drawAST(root);
		printf("       SHOW TIME\n , length of map is %d \n", hashmap_length(map));
		// ����root���ļ�����ʽ��ӡ
		printAST(root);
	}

	
	return 0;
}



