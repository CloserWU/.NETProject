// C调用C++，需要在cpp源代码加一层wrapper，在wrapper中，要用如下方法包裹wrapper
// 并且定义一个结构体，存放cpp源码中的对象；在wrapper中定义方法，将结构体参数传入，并且调用接口即可
/*
#ifdef __cplusplus
extern "C" {
#endif
...
#ifdef __cplusplus
};
#endif
*/


// 定义结构体
struct graphvizWrapper;

#ifdef __cplusplus
extern "C" {
#endif
	// 定义下列结构，结构体参数为第一个参数，并且调用cpp源码的函数需要加上extern
	struct graphvizWrapper* getInstance(void);

	void release(struct graphvizWrapper** graphviz);

	extern void addNode(struct graphvizWrapper* graphviz, int a, char* label);

	extern void addEdge(struct graphvizWrapper* graphviz, int a, int b, char* label);

	extern void Export(struct graphvizWrapper* graphviz, char* file);

#ifdef __cplusplus
};
#endif


