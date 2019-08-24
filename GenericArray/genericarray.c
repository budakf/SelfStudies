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

void copy_elements( GenericArray * dest, GenericArray * source ){
    for(int i = 0; i < source->size; i++){
        dest->container[i] = malloc( sizeof(void *) );
        dest->container[i] = source->container[i];
    }
}

void enhance_capacity(GenericArray * array){
    GenericArray * temp = malloc( sizeof(GenericArray) );
    temp->container = malloc( sizeof(void *) * array->size );
    temp->size = array->size;
    copy_elements(temp, array);
    init_GenericArray(array, array->capacity*2);
    copy_elements(array, temp);
    array->size = temp->size;
    free(temp);
}

void push_back( GenericArray * array , void * element){
    if(array->size == array->capacity){
        enhance_capacity(array);
    }
    array->container[array->size] = malloc( sizeof(void *) );
    array->container[array->size] = element;
    ++array->size;
}

void pop_back(GenericArray * array){
    --array->size;
    array->container[array->size] = NULL;
}


int main(){

    GenericArray *array = malloc( sizeof(GenericArray) );
    init_GenericArray(array , 1);

    int first = 10;
    char second = 'F';
    push_back(array, &first );
    push_back(array, &first );
    push_back(array, &first );
    push_back(array, &first );
    push_back(array, &first );
    pop_back(array);
    push_back(array, &second );
    
    printf( "%d \n", *((int *)array->container[0]) );
    printf( "%c\n", *((char *)array->container[4]) );
    printf( "size:%d\ncapacity:%d\n", array->size, array->capacity );

    return 0;
}