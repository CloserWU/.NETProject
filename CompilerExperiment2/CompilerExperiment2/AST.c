#include "AST.h"
// �½�ast�ڵ㣬��ʼ��val��childs
struct ast* newAST(char* val) {
	struct ast* a = malloc(sizeof(struct ast));
	if (!a) {
		yyerror((char*)"oom");
		exit(0);
	}
	a->val = val;
	a->childs = NULL;
	return a;
}

// �½�list�ڵ㣬��ʼ��node��next
struct list* initChild(struct ast* node) {
	struct list* a = malloc(sizeof(struct list));
	if (!a) {
		yyerror((char*)"oom");
		exit(0);
	}
	a->next = NULL;
	a->node = node;
	return a;
}

// ��һ��list�ڵ���뵽һ��ast�ڵ��childs��
void addChild(struct ast* root, struct ast* child) {
	if (root == NULL || child == NULL) {
		yyerror("null pointer of root");
		exit(0);
	}
	// ���ast��childsΪ�գ���ֱ�Ӹ�ֵ
	if (root->childs == NULL) {
		struct list* c = initChild(child);
		root->childs = c;
		return;
	}
	// �����ߵ�childs���һ���ڵ㣬Ȼ���޸�����ָ��
	struct list* childs = root->childs;
	while (childs->next != NULL) {
		childs = childs->next;
	}
	struct list* tail = initChild(child);
	childs->next = tail;
}

// �ļ�����ʽ��ӡast
void printAST(struct ast* root) {
	if (root == NULL) return;
	printf("%s\n", root->val);
	printAST_R(root, 0);
}

// �ݹ飬level��ǰ��ĳ���
// �ݹ��ȴ�ӡ��ǰ��Ȼ��dfs��ӡ�ӽڵ�
void printAST_R(struct ast* root, int level) {
	level += 1;
	if (root == NULL) return;
	struct list* childs = root->childs;
	while (childs != NULL) {
		print(childs->node, level);
		printAST_R(childs->node, level);
		childs = childs->next;
	}
}

// ��ӡһ��
void print(struct ast* root, int level) {
	if (root == NULL) return;
	for (int i = 1; i < level; i++) {
		printf(" | ");
	}
	printf(" |- ");
	printf("%s\n", root->val);
}