/*
hashtable:
   hashtable的实现方法不会影响最后的结果，所以大家可以自由发挥。
   允许大家使用模版\struct等方法，不过要做相应的改动。

   hashtable主要存储变量的声明，由于经常查询，所以要用速度比较快的hashtable来实现
*/
#ifndef _H_hashtable
#define _H_hashtable

#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#define HASH_TABLE_CAPACITY 256
class Declaration;

typedef unsigned int uint;

/** hash table element*/
typedef struct _htItem {
    struct _htItem* next;
    char* key_string;
    int line;
    uint fid;

} htItem;

/** init the hashTable 构造函数，申请哈希表的空间*/
void htInit(htItem** ht, uint length);

/** set hashTable element 哈希表中插入一个值*/
uint htSet(char* key, uint val, htItem** ht, int li);

uint htSetl(char* key, htItem** ht);

/** get element from hashtable 从哈希表中获得一个对应的key*/
htItem* htGet(char* key, htItem** ht);

/** Delete element from hashTable 从哈希表中删除一个key*/
int htDel(char* key, htItem** ht);

/** BKDR hash function 对string进行散列得到一个整数值*/
uint bkdrHash(char* key);

/** get the index of hash table 根据key计算一个整数值，然后获得对应的槽位*/
uint htIndex(char* key, htItem** ht);

/** get hashTable elements */
uint htLen(htItem** ht);

/*打印哈希表*/
void print_hashTable(htItem** ht);

#endif


/*class Hashtable {
private:

public:*/

