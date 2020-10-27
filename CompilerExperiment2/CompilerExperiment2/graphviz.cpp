/*
wrapper的实现也是用cpp，需要用
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
};
#endif
包裹代码
*/
#include "graphviz.h"
#include "graphviz_utility.h"


#ifdef __cplusplus
extern "C" {
#endif
	// 结构体，内部存放cpp源码的类
	struct graphvizWrapper {
		GraphvizUtility graphviz;
	};

	// 可以new struct
	struct graphvizWrapper* getInstance(void) {
		return new struct graphvizWrapper;
	}

	// 释放指针，并指向NULL
	void release(struct graphvizWrapper** graphviz) {
		delete * graphviz;
		*graphviz = NULL;
	}

	// 调用addNode
	void addNode(struct graphvizWrapper* graphviz, int a, char* label) {
		graphviz->graphviz.AddNode(a, label);
	}

	// 调用addEdge
	void addEdge(struct graphvizWrapper* graphviz, int a, int b, char* label) {
		graphviz->graphviz.AddEdge(a, b, label);	
	}

	// 调用export
	void Export(struct graphvizWrapper* graphviz, char* file) {
		graphviz->graphviz.Export(file);
	}

#ifdef __cplusplus
};
#endif
