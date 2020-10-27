// C����C++����Ҫ��cppԴ�����һ��wrapper����wrapper�У�Ҫ�����·�������wrapper
// ���Ҷ���һ���ṹ�壬���cppԴ���еĶ�����wrapper�ж��巽�������ṹ��������룬���ҵ��ýӿڼ���
/*
#ifdef __cplusplus
extern "C" {
#endif
...
#ifdef __cplusplus
};
#endif
*/


// ����ṹ��
struct graphvizWrapper;

#ifdef __cplusplus
extern "C" {
#endif
	// �������нṹ���ṹ�����Ϊ��һ�����������ҵ���cppԴ��ĺ�����Ҫ����extern
	struct graphvizWrapper* getInstance(void);

	void release(struct graphvizWrapper** graphviz);

	extern void addNode(struct graphvizWrapper* graphviz, int a, char* label);

	extern void addEdge(struct graphvizWrapper* graphviz, int a, int b, char* label);

	extern void Export(struct graphvizWrapper* graphviz, char* file);

#ifdef __cplusplus
};
#endif


