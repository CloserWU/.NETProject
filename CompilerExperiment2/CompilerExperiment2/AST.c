#include "AST.h"
// 新建ast节点，初始化val和childs
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

// 新建list节点，初始化node和next
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

// 将一个list节点加入到一个ast节点的childs中
void addChild(struct ast* root, struct ast* child) {
	if (root == NULL || child == NULL) {
		yyerror("null pointer of root");
		exit(0);
	}
	// 如果ast的childs为空，则直接赋值
	if (root->childs == NULL) {
		struct list* c = initChild(child);
		root->childs = c;
		return;
	}
	// 否则，走到childs最后一个节点，然后修改链表指针
	struct list* childs = root->childs;
	while (childs->next != NULL) {
		childs = childs->next;
	}
	struct list* tail = initChild(child);
	childs->next = tail;
}

// 文件树格式打印ast
void printAST(struct ast* root) {
	if (root == NULL) return;
	printf("%s\n", root->val);
	printAST_R(root, 0);
}

// 递归，level是前面的长度
// 递归先打印当前，然后dfs打印子节点
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

// 打印一行
void print(struct ast* root, int level) {
	if (root == NULL) return;
	for (int i = 1; i < level; i++) {
		printf(" | ");
	}
	printf(" |- ");
	printf("%s\n", root->val);
}