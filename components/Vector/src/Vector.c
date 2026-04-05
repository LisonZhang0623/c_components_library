#include "Vector.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

vector_res_t vectorInit(Vector * vec, size_t elem_size)
{
    if(vec == NULL || elem_size == 0)
    {
        return VEC_BAD_ARG;
    }
    vec->capacity = vec->size = 0;
    vec->data = NULL;
    vec->elem_size = elem_size;
    return VEC_OK;
}

vector_res_t vectorFree(Vector * vec)
{
    if(vec == NULL)
    {
        return VEC_BAD_ARG;
    }
    vec->capacity = vec->elem_size = vec->size = 0;
    free(vec->data);
    vec->data = NULL;
    return VEC_OK;
}

vector_res_t vectorPushBack(Vector * vec, const void * elem)
{
    if(vec == NULL || elem == NULL || vec->elem_size == 0) 
    {
        return VEC_BAD_ARG;
    }

    //扩容
    if(vec->capacity == vec->size)
    {
        size_t new_cap = vec->capacity == 0 ? 4 : vec->capacity * 2;
        void * new_data = 
            realloc(vec->data,new_cap * vec->elem_size);
        if(new_data == NULL)
        {
            return VEC_NO_MEMORY;
        }
        vec->data = new_data;
        vec->capacity = new_cap;
    }

    void * target = (char *)vec->data + vec->size * vec->elem_size;
    vec->size ++;
    memcpy(target,elem,vec->elem_size);
    return VEC_OK;
}

vector_res_t vectorPopBack(Vector *vec)
{
    if(vec == NULL || vec->elem_size == 0)
    {
        return VEC_BAD_ARG;
    }
    
    if (vec->size == 0)
    {
        return VEC_BAD_ARG;
    }

    vec->size --;
    return VEC_OK;
}

void *vectorAt(Vector *vec, size_t index)
{
    if (vec == NULL || index >= vec->size)
    {
        return NULL;
    }

    return (char *)vec->data + index * vec->elem_size;
}

const void *vectorAtConst(const Vector *vec, size_t index)
{
    if (vec == NULL || index >= vec->size)
    {
        return NULL;
    }
    return (const char *)vec->data + index * vec->elem_size;
}

void vectorClear(Vector *vec)
{
    if (vec == NULL)
    {
        return;
    }

    vec->size = 0;
}

int vectorEmpty(const Vector *vec)
{
    if (vec == NULL)
    {
        return 1;
    }
    return vec->size == 0;
}

static void _vectorSwap(Vector *vec, size_t i, size_t j)
{
    if (vec == NULL || i == j)
    {
        return;
    }

    void *pi = (char *)vec->data + i * vec->elem_size;
    void *pj = (char *)vec->data + j * vec->elem_size;

    void *tmp = malloc(vec->elem_size);
    if (tmp == NULL)
    {
        return;
    }

    memcpy(tmp, pi, vec->elem_size);
    memcpy(pi, pj, vec->elem_size);
    memcpy(pj, tmp, vec->elem_size);

    free(tmp);
}

static void _quickSort(Vector * vec, int l, int r, vectorCompareFunc cmp)
{
    if (vec == NULL || cmp == NULL || l >= r)
    {
        return;
    }

    //取中间值
    void *pivot = malloc(vec->elem_size);
    if (pivot == NULL)
    {
        return;
    }
    memcpy(pivot, vectorAt(vec, (size_t)((l + r) >> 1)), vec->elem_size);

    int i = l - 1, j = r + 1;
    while(i < j)
    {
        do i++; while (cmp(vectorAt(vec, (size_t)i), pivot));
        do j--; while (cmp(pivot, vectorAt(vec, (size_t)j)));
        if(i < j)
        {
            _vectorSwap(vec,(size_t)i,(size_t)j);
        }
    }
    free(pivot);
    _quickSort(vec,l,j,cmp);
    _quickSort(vec,j+1,r,cmp);
}

vector_res_t vectorSort(Vector * vec,vectorCompareFunc cmp)
{
    if(vec->size <= 1)
    {
        return VEC_OK;
    }
    if (vec == NULL || cmp == NULL)
    {
        return VEC_BAD_ARG;
    }
    _quickSort(vec, 0, (int)vec->size - 1, cmp);
    return VEC_OK;
}

int vectorIntCmp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x < y;
}

int vectorDoubleCmp(const void *a, const void *b)
{
    double x = *(const double *)a;
    double y = *(const double *)b;
    return x < y;
}

int vectorCharCmp(const void *a, const void *b)
{
    char x = *(const char *)a;
    char y = *(const char *)b;
    return x < y;
}


void __vectorTest001()
{
    Vector vec;
    vectorInit(&vec, sizeof(int));

    for (int i = 1; i <= 5; i++)
    {
        vectorPushBack(&vec, &i);
    }

    printf("size before pop: %zu\n", vec.size);

    vectorPopBack(&vec);

    printf("size after pop: %zu\n", vec.size);

    for (size_t i = 0; i < vec.size; i++)
    {
        printf("%d ", *(int *)vectorAt(&vec, i));
    }
    printf("\n");

    vectorClear(&vec);
    printf("after clear, empty = %d\n", vectorEmpty(&vec));

    vectorFree(&vec);
}

static int intCmp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x < y;
}

void __vectorTest002(void)
{
    Vector vec;
    if (vectorInit(&vec, sizeof(int)) != VEC_OK)
    {
        printf("vectorInit failed\n");
        return;
    }

    int arr[] = {5, 2, 9, 1, 7, 3, 8, 4, 6};

    for (int i = 0; i < 9; i++)
    {
        if (vectorPushBack(&vec, &arr[i]) != VEC_OK)
        {
            printf("vectorPushBack failed\n");
            vectorFree(&vec);
            return;
        }
    }

    for (size_t i = 0; i < vec.size; i++)
    {
        printf("%d ", *(int *)vectorAt(&vec, i));
    }
    printf("\n");
    vectorSort(&vec, intCmp);

    for (size_t i = 0; i < vec.size; i++)
    {
        printf("%d ", *(int *)vectorAt(&vec, i));
    }
    printf("\n");

    vectorFree(&vec);
}