#include <stdio.h>
#include <stdlib.h>

typedef struct GenericArray{
    void ** container;
    int capacity;
    int size;
}GenericArray;

void init_GenericArray(GenericArray * array, int capacity){
    array->size = 0;
    array->capacity = capacity;
    array->container = malloc( sizeof(void *) * capacity );
}

// void enhance_capacity(GenericArray * array){
//     GenericArray * temp = array;
//     init_GenericArray(array, array->capacity*2);
//     array->size = temp->size;
//     array->nextIndex = temp->nextIndex;
// }

// void copy_elements( GenericArray * dest, GenericArray * source ){
//     for(int i = 0; i < source->size; i++){
//         dest->container[i] = malloc( sizeof(void *) );
//     }
// }


void push_back( GenericArray * array , void * element){
    array->container[array->size] = malloc( sizeof(void *) );
    array->container[array->size] = element;
    ++array->size;
}

void pop_back(GenericArray * array){
    --array->size;
    array->container[array->size] = NULL;
}


int main(){

    GenericArray *array;
    init_GenericArray(array , 10);

    int first = 10;
    char second = 'F';
    push_back(array, &first );
    printf( "%d \n", *((int *)array->container[0]) );
    //pop_back(array);
    push_back(array, &second );
    printf( "%c\n", *((char *)array->container[1]) );
    printf( "%d\n", array->size );

    return 0;
}