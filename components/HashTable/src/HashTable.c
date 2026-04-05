#include "HashTable.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define HT_DEFAULT_CAPACITY 16
#define HT_MAX_LOAD_FACTOR 0.75

static size_t htHash(const char * key)
{
    size_t hash = 5381;
    int ch = 0;
    do
    {
        ch = (unsigned char)*key ++;
        hash = ((hash << 5) + hash) + (size_t)ch;
    }while(ch != 0);
    return hash;
}

static HashNode * hashNodeCreate(const char *key, const void *value, size_t value_size)
{
    if (key == NULL || value == NULL || value_size == 0) 
    {
        return NULL;
    }
    HashNode * node = (HashNode *)malloc(sizeof(HashNode));
    if(node == NULL)
    {
        return NULL;
    }
    node->key = strdup(key);
    node->value_size = value_size;
    
    node->value = malloc(value_size);
    if(node->value == NULL)
    {
        free(node->key);
        free(node);
        return NULL;
    }

    memcpy(node->value,value,value_size);
    node->next = NULL;
    return node;
}

static void hashNodeDestroy(HashNode * node)
{
    if(node == NULL || node->value_size == 0)
    {
        return;
    }
    free(node->key);
    free(node->value);
    free(node);
}

static hash_table_res_t hashTableResize(HashTable * ht, size_t new_cap)
{
    if(ht == NULL || new_cap < 1 || new_cap <= ht->capacity)
    {
        return HT_BAD_ARG;
    }
    HashNode ** new_buckets = (HashNode **)calloc(new_cap,sizeof(HashNode *));
    if(new_buckets == NULL)
    {
        return HT_NO_MEMORY;
    }
    for(size_t i = 0;i < ht->capacity; ++ i)
    {
        HashNode * node = ht->buckets[i];
        while(node != NULL)
        {
            HashNode * next = node->next;
            size_t new_index = htHash(node->key) % new_cap;
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next;
        }
    }
    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_cap;
    return HT_OK;
}

static int hashTableNeedResize(const HashTable *ht)
{
    if (ht == NULL || ht->capacity == 0) 
    {
        return 0;
    }
    double load_factor = (double)ht->size / (double)ht->capacity;
    return load_factor > HT_MAX_LOAD_FACTOR;
}

HashTable * hashTableCreate(size_t init_cap)
{
    if (init_cap == 0) 
    {
        init_cap = HT_DEFAULT_CAPACITY;
    }
    HashTable * ht = (HashTable *)malloc(sizeof(HashTable));
    if(ht == NULL)
    {
        return NULL;
    }
    ht->buckets = (HashNode **)calloc(init_cap,sizeof(HashNode *));
    if(ht->buckets == NULL)
    {
        free(ht);
        return NULL;
    }
    ht->capacity = init_cap;
    ht->size = 0;
    return ht;
}

void hashTableDestroy(HashTable *ht)
{
    if(ht == NULL)
    {
        return;
    }
    for(size_t i = 0;i < ht->capacity; ++i)
    {
        HashNode * node = ht->buckets[i];
        while(node != NULL)
        {
            HashNode * next = node->next;
            hashNodeDestroy(node);
            node = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

hash_table_res_t hashTablePut(HashTable *ht, const char *key, const void *value, size_t value_size)
{
    if (ht == NULL || key == NULL || value == NULL || value_size == 0) 
    {
        return HT_BAD_ARG;
    }
    size_t index = htHash(key) % ht->capacity;
    HashNode * node = ht->buckets[index];

    //判断key是否存在
    while(node != NULL)
    {
        if(strcmp(node->key,key) == 0)
        {//key存在
            void * new_value = malloc(value_size);
            if(new_value == NULL)
            {
                return HT_NO_MEMORY;
            }
            memcpy(new_value,value,value_size);
            free(node->value);
            node->value = new_value;
            node->value_size = value_size;
            return HT_OK;
        }
        node = node->next;
    }

    //key不存在直接插入
    HashNode * new_node = hashNodeCreate(key,value,value_size);
    if(new_node == NULL)
    {
        return HT_NO_MEMORY;
    }

    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->size ++;

    if(hashTableNeedResize(ht))
    {
        size_t new_capacity = ht->capacity * 2;
        if (new_capacity == 0) 
        {
            new_capacity = HT_DEFAULT_CAPACITY;
        }
        if (!hashTableResize(ht, new_capacity)) 
        {
            /* 扩容失败不影响当前已有插入结果 */
            return HT_OK;
        }
    }
    return HT_OK;
}

void *hashTableGet(const HashTable *ht, const char *key)
{
    if (ht == NULL || key == NULL || ht->capacity == 0) 
    {
        return NULL;
    }
    size_t index = htHash(key) % ht->capacity;
    HashNode * node = ht->buckets[index];
    while(node != NULL)
    {
        if(strcmp(node->key,key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

hash_table_res_t hashTableRemove(HashTable *ht, const char *key)
{
    
}

int hashTableContains(const HashTable *ht, const char *key)
{
    return hashTableGet(ht,key) != NULL;
}