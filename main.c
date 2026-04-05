#include <stdio.h>
#include <string.h>
#include "Array.h"
#include "Vector.h"


int main(int argc, char const *argv[])
{
    // __arrayTest001();
    // __vectorTest001();
    // __vectorTest002();
    Vector vec;
    vectorInit(&vec,sizeof(char));
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
    return 0;
}
