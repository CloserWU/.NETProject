/*
wrapper��ʵ��Ҳ����cpp����Ҫ��
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
};
#endif
��������
*/
#include "graphviz.h"
#include "graphviz_utility.h"


#ifdef __cplusplus
extern "C" {
#endif
	// �ṹ�壬�ڲ����cppԴ�����
	struct graphvizWrapper {
		GraphvizUtility graphviz;
	};

	// ����new struct
	struct graphvizWrapper* getInstance(void) {
		return new struct graphvizWrapper;
	}

	// �ͷ�ָ�룬��ָ��NULL
	void release(struct graphvizWrapper** graphviz) {
		delete * graphviz;
		*graphviz = NULL;
	}

	// ����addNode
	void addNode(struct graphvizWrapper* graphviz, int a, char* label) {
		graphviz->graphviz.AddNode(a, label);
	}

	// ����addEdge
	void addEdge(struct graphvizWrapper* graphviz, int a, int b, char* label) {
		graphviz->graphviz.AddEdge(a, b, label);	
	}

	// ����export
	void Export(struct graphvizWrapper* graphviz, char* file) {
		graphviz->graphviz.Export(file);
	}

#ifdef __cplusplus
};
#endif
