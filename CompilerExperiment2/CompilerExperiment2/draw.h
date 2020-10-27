#include "graphviz.h"
#include <assert.h>

struct graphvizWrapper* graphviz;
// 全局变量， 写出dot文件
// dot -Tpng -o example.png example.dot
// https://github.com/sjsimps/Graphviz-Utility/blob/master/graphviz_utility.h
int idx = 0;

void drawNode_R(struct ast* root) {
	if (root == NULL) return;
	int pre = idx;
	struct list* childs = root->childs;
	while (childs != NULL) {
		addNode(graphviz, ++idx, childs->node->val);
		addEdge(graphviz, pre, idx, "");
		drawNode_R(childs->node);
		childs = childs->next;
	}
}
// 类似与printAST

void drawNode(struct ast* root) {
	if (root == NULL) return;
	addNode(graphviz, 0, root->val);
	drawNode_R(root);
}


void drawAST(struct ast* root) {
	if (root == NULL) return;
	graphviz = getInstance();
	drawNode(root);
	Export(graphviz, "example.dot");
	release(&graphviz);
	assert(graphviz == NULL);
}

