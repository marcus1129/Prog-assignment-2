#include <stdio.h>
#include <stdlib.h>

typedef struct dynamicBuffer{
    int *prevBlock;
    int *nextBlock;
    void (*allocNewBufferBlock)(struct dynamicBuffer self);
    struct dynamicBuffer (*allocNewBuffer)();
} dynamicBuffer;

void allocNewBufferBlock(struct dynamicBuffer self){
    
}

struct dynamicBuffer allocNewBuffer(){

}

int main()
{

    //Opens file
    /*const int workerInfoPath = "./tekstfil.txt";
    char *buffer = calloc(1, sizeof(char[100]));
    FILE *filePtr;
    filePtr = fopen(workerInfoPath, "r");

    //Reads from file
    fgets(buffer, 1000, filePtr);
    for(int z = 0; z < 100; z++){

    }*/

    printf("Hello world!\n");
    return 0;
}
