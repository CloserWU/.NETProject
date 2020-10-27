/*
hashtable:
   hashtable��ʵ�ַ�������Ӱ�����Ľ�������Դ�ҿ������ɷ��ӡ�
   ������ʹ��ģ��\struct�ȷ���������Ҫ����Ӧ�ĸĶ���

   hashtable��Ҫ�洢���������������ھ�����ѯ������Ҫ���ٶȱȽϿ��hashtable��ʵ��
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

/** init the hashTable ���캯���������ϣ��Ŀռ�*/
void htInit(htItem** ht, uint length);

/** set hashTable element ��ϣ���в���һ��ֵ*/
uint htSet(char* key, uint val, htItem** ht, int li);

uint htSetl(char* key, htItem** ht);

/** get element from hashtable �ӹ�ϣ���л��һ����Ӧ��key*/
htItem* htGet(char* key, htItem** ht);

/** Delete element from hashTable �ӹ�ϣ����ɾ��һ��key*/
int htDel(char* key, htItem** ht);

/** BKDR hash function ��string����ɢ�еõ�һ������ֵ*/
uint bkdrHash(char* key);

/** get the index of hash table ����key����һ������ֵ��Ȼ���ö�Ӧ�Ĳ�λ*/
uint htIndex(char* key, htItem** ht);

/** get hashTable elements */
uint htLen(htItem** ht);

/*��ӡ��ϣ��*/
void print_hashTable(htItem** ht);

#endif


/*class Hashtable {
private:

public:*/

