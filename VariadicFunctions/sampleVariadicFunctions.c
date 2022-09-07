#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include <ctype.h>

void print(char * format, ...){

    va_list args;
    va_start(args, format);

    while(*format != '\0' ){
        int chr = toupper(*format);

        if(chr == 'D'){
            int integer = va_arg(args, int);
            printf("%d",integer);
        }

        if(chr == 'C'){
            char character = va_arg(args, int);
            printf("%c",character);
        }

        if(chr == 'F'){
            double floatingPointNumber = va_arg(args, double);
            printf("%.2f",floatingPointNumber);
        }
        if(chr=='\n'){
            printf("\n");
        }

        ++format;
    }

    va_end(args);

}

int sumIntegers(int count, ...){
    va_list args;
    int sum = 0;
    va_start(args,count);
    for(int i = 0; i < count; i++){
        sum += va_arg(args, int);
    }
    va_end(args);
    return sum;
}

double sumNumbers(int count , ...){
    va_list args;
    va_start(args, count);
    double sum = .0;
    for(int i = 0; i<count; i++){
       sum += va_arg(args, double);
    }
    va_end(args);
    return sum;
}

char * concat(char * firstString, ...){

    va_list args, backupArgs;
    va_start(args, firstString);
    va_copy(backupArgs, args);
    int len = strlen(firstString); 
    char * temp;

    while((temp = va_arg(args, char *)) != NULL){
        len += strlen(temp);
    }
    va_end(args);

    char * result = (char *) malloc(sizeof(char) * len+1 );
    if (!result) {
		fprintf(stderr, "Unsufficient Memory\n");
		exit(1);
	}

    strcpy(result, firstString);
    while((temp = va_arg(backupArgs, char *)) != NULL){
        strcat(result, temp);
    }

    va_end(backupArgs);
    return result;

}

char ** makeStringList(char * firstString, ...){
    va_list args, backupArgs;
    va_start(args, firstString);
    va_copy(backupArgs, args);

    char * temp;
    int count = 1; // because first element is firstString
    while((temp = va_arg(args, char *))!= NULL){
        ++count;
    }
    va_end(args);

    char ** resultStringList = malloc(sizeof(char *) * count);
    int index = 0;
    resultStringList[index] = malloc( sizeof(char) * strlen(firstString)+1);
    strcpy(resultStringList[index], firstString);
    while((temp = va_arg(backupArgs, char *))!= NULL){
        ++index;
        resultStringList[index] = malloc( sizeof(char) * strlen(temp)+1);
        strcpy(resultStringList[index], temp);
    }

    va_end(backupArgs);

    return resultStringList;

}

int main(){
    print( "d c f\n",10,'y',4.3 );
    print( "d\n",sumIntegers(5, 12,1,1,1,1) );
    print( "f\n", sumNumbers(4, 12.3,3.2,4.3,8.9) );
    char * output = concat("Fatih", "Budak", "Galatasaray", "Liverpool", NULL);
    printf( "%s\n", output );
    free(output);

    char ** stringList = makeStringList("Fatih", "Budak", "Galatasaray", "Liverpool", NULL);
    printf( "%s \n", stringList[0]);
    printf( "%s \n", stringList[1]);
    printf( "%s \n", stringList[2]);
    printf( "%s \n", stringList[3]);

    int count = 4;
    for(int index = 0; index < count; ++index)
    {
        free(stringList[index]);
    }

    return 0;
}