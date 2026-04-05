#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stddef.h>

typedef enum
{
    HT_OK = 0,
    HT_BAD_ARG,
    HT_NO_MEMORY,
    HT_OUT_OF_RANGE
} hash_table_res_t;

typedef struct HashNode
{
    char * key;
    void * value;
    size_t value_size;
    struct HashNode * next;
}HashNode;

typedef struct HashTable
{
    HashNode ** buckets;
    size_t capacity;
    size_t size;
}HashTable;

HashTable * hashTableCreate(size_t init_cap);
void hashTableDestroy(HashTable *ht);

hash_table_res_t hashTablePut(HashTable *ht, const char *key, const void *value, size_t value_size);
void *hashTableGet(const HashTable *ht, const char *key);
hash_table_res_t hashTableRemove(HashTable *ht, const char *key);
int hashTableContains(const HashTable *ht, const char *key);


#endif