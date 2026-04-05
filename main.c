#include <stdio.h>
#include <string.h>
#include "HashTable.h"
#include "Vector.h"

void testVector()
{
    Vector vec;
    vectorInit(&vec,VECTOR_CHAR);
    const char * arr = "acdpou";
    for(int i=0;i<strlen(arr);i++)
    {
        vectorPushBack(&vec,arr + i);
    }
    vectorSort(&vec,vectorCharCmp);
    for(int i=0;i<vec.size;i++)
    {
        printf("%c ",VECTOR_GET(char,&vec,i));
    }
    printf("\n");
    vectorFree(&vec);
}

typedef struct Student
{
    int age;
    double score;
} Student;

void testHash()
{
    HashTable *ht = hashTableCreate(8);

    int num = 123;
    double pi = 3.14159;
    Student stu = {20, 95.5};

    hashTablePut(ht, "number", &num, sizeof(num));
    hashTablePut(ht, "pi", &pi, sizeof(pi));
    hashTablePut(ht, "student", &stu, sizeof(stu));

    int *pnum = (int *)hashTableGet(ht, "number");
    double *ppi = (double *)hashTableGet(ht, "pi");
    Student *pstu = (Student *)hashTableGet(ht, "student");

    if (pnum) {
        printf("number = %d\n", *pnum);
    }
    if (ppi) {
        printf("pi = %f\n", *ppi);
    }
    if (pstu) {
        printf("student.age = %d, student.score = %.2f\n", pstu->age, pstu->score);
    }

    hashTableDestroy(ht);
}
int main(int argc, char const *argv[])
{
    // testVector();
    testHash();
    return 0;
}
