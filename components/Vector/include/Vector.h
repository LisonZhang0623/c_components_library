#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

#define VECTOR_GET(type, vec, index) (*(type *)vectorAt(vec, index))

#define VECTOR_CHAR         sizeof(char)
#define VECTOR_INT          sizeof(int)
#define VECTOR_U_INT        sizeof(unsigned int)
#define VECTOR_FOALT        sizeof(float)
#define VECTOR_LONG         sizeof(long)
#define VECTOR_LONG_LONG    sizeof(long long)
#define VECTOR_U_LONG_LONG  sizeof(unsigned long long)

typedef enum
{
    VEC_OK = 0,
    VEC_BAD_ARG,
    VEC_NO_MEMORY,
    VEC_OUT_OF_RANGE
} vector_res_t;

typedef struct Vector
{
    size_t size;
    size_t capacity;
    size_t elem_size;
    void * data;
}Vector;

typedef int (*vectorCompareFunc)(const void *a, const void *b);

vector_res_t vectorInit(Vector * vec, size_t elem_size);
vector_res_t vectorFree(Vector * vec);
vector_res_t vectorPushBack(Vector * vec, const void * elem);
vector_res_t vectorPopBack(Vector *vec);

void *vectorAt(Vector *vec, size_t index);
const void *vectorAtConst(const Vector *vec, size_t index);

void vectorClear(Vector *vec);
int vectorEmpty(const Vector *vec);

vector_res_t vectorSort(Vector * vec,vectorCompareFunc cmp);

int vectorIntCmp(const void *a, const void *b);
int vectorDoubleCmp(const void *a, const void *b);
int vectorCharCmp(const void *a, const void *b);

void __vectorTest001();
void __vectorTest002();

#endif