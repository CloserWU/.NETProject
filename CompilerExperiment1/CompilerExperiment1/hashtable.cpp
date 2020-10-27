/*
Hashtable.cpp:
add your code below:
*/
#include <stdio.h>
#include "declaration.h"
#include "hashtable.h"

/*��ʼ��HashTable*/
void htInit(htItem** ht, uint length) {
    uint i;
    for (i = 0; i < length; i++) {
        ht[i] = (htItem*)malloc(sizeof(htItem));
        memset(ht[i], 0, sizeof(htItem));
    }
    ht[0]->fid = length;
}

/** get hashTable elements ���ж�Ӧ��hashֵ������������ҵ��򷵻ظýڵ�*/
htItem* htGet(char* key, htItem** ht) {
    uint i = htIndex(key, ht);
    htItem* item = ht[i]->next;
    htItem* tmp = (htItem*)malloc(sizeof(htItem));
    memset(tmp, 0, sizeof(htItem));
    while (item)
    {
        if (strcmp(key, item->key_string) == 0) {
            return item;
        }
        item = item->next;
    }
    return NULL;
}

/** set hashTable element �����µ�hashֵ*/
uint htSet(char* key, uint fid, htItem** ht, int li) {
    uint i = htIndex(key, ht);
    htItem* item = ht[i];
    while (item->next)
    {
        //�Ѿ����ڵĻ���ֱ�Ӹ���ֵ
            //printf("!!!  %s  !!! \n",item->next->key_string);
        if (strcmp(item->next->key_string, key) == 0) {
            item->next->fid += fid;
            return item->next->fid;
        }
        else {
            item = item->next;
        }
    }
    item->next = (htItem*)malloc(sizeof(htItem));
    item->next->fid = fid;
    item->next->line = li;
    item->next->key_string = key;
    item->next->next = NULL;
    return 1;
}
uint htSetl(char* key, htItem** ht) {
    uint i = htIndex(key, ht);
    htItem* item = ht[i];
    while (item->next)
    {
        //�Ѿ����ڵĻ���ֱ�Ӹ���ֵ
            //printf("!!!  %s  !!! \n",item->next->key_string);
        if (strcmp(item->next->key_string, key) == 0) {
            return item->next->line;
        }
        else {
            item = item->next;
        }
    }
    return 1;
}

/** delete one element of hashtable  ɾ��hashֵ*/
int htDel(char* key, htItem** ht) {
    uint i = htIndex(key, ht);
    htItem* item = ht[i];
    while (item->next) {
        if (strcmp(key, item->next->key_string) == 0) {
            htItem* tmp = item->next;
            item->next = tmp->next;
            free(tmp);
            return 0;
        }
        item = item->next;
    }
    return -1;
}

/** BKDR hash function  ���ַ�������ɢ�У��õ�һ��������hashֵ*/
uint bkdrHash(char* key)
{
    uint seed = 131;
    uint hash = 0;
    while (*key != '\n' && *key != 0)
    {
        hash = hash * seed + (*key++);
    }
    return (hash & 0x7FFFFFFF);
}

/** get the index of hash table  ���ݵõ���hashֵѡ��һ����λ��*/
uint htIndex(char* key, htItem** ht) {
    uint hashedKey = bkdrHash(key);
    uint length = (ht[0]->fid - 1);
    return (uint)hashedKey % length + 1;
}

/** get element number in the hashtable */
uint htLen(htItem** ht) {
    uint alength = ht[0]->fid;
    uint i, length = 0;
    for (i = 1; i < alength; i++) {
        if (ht[i]->next) {
            length++;
        }
    }
    return length;
}

/** get capacity of hashtable */
uint htCapacity(htItem** ht)
{
    return ht[0]->fid;
}

void print_hashTable(htItem** ht)
{
    uint length = ht[0]->fid;
    uint i;
    htItem* item;
    for (i = 1; i < length; i++)
    {
        item = ht[i]->next;
        while (item)
        {
            printf("%s => %d\n", item->key_string, item->fid);
            item = item->next;
        }
    }
}


