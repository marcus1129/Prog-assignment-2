#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


///////// Buffer stuff, might use later //////////////
/*typedef struct dynamicBuffer{
    int* prevBlock;
    char* content;
    int* nextBlock;
} dynamicBuffer;

void allocNewBufferBlock(struct dynamicBuffer self){
    
}

struct dynamicBuffer* allocNewBuffer(){
    dynamicBuffer* temp = malloc(sizeof(dynamicBuffer));
    temp->content = malloc(1025);
    for (int i = 0; i < 1023; i++){
        temp.content[i] = '\0';
    }
    temp->prevBlock = NULL;
    temp->nextBlock = NULL;
    return temp;
}

bool isBufferFull(dynamicBuffer* buffer){
    if((*buffer).content[1024] == '\0'){
        return false;
    } else{
        return true;
    }
}

void printBuffer(dynamicBuffer* buffer){
    int i = 0;
    bool printLoop = true;
    while(printLoop){
        while((*buffer).content[i] != '\0'){
            printf((*buffer)-content[i]);
        }
        if(i == 1024)
    }
    if(isBufferFull(buffer)){

    }
}*/

typedef struct Worker{
    int workerId;
    char* firstName;
    char* surName;
    int departmentId;
    float rate;
    struct Worker* prevWorker;
    struct Worker* nextWorker;
    /*bool word;
    bool excel;
    bool database;*/
} worker;

struct Worker* indlaes(){
    //Opens file
    const char* workerInfoPath = "./tekstfil.txt";
    FILE *filePtr;
    filePtr = fopen(workerInfoPath, "r");

    //Initiates string buffer
    char* buffer = malloc(1001);
    buffer[1001] = '\0';

    //Creates a worker
    struct Worker* currWorker = malloc(sizeof(struct Worker));
    currWorker->prevWorker = NULL;
    currWorker->nextWorker = NULL;

    //Reads from file
    while(fgets(buffer, 1000, filePtr)!= NULL){
        int idDigits;
        int surnameStart;
        int departmentIdStart;

        //Initiates temporary buffers
        char* tempFirstName = malloc(30);
        tempFirstName[30] = '\0';

        char* tempSurName = malloc(30);
        tempSurName[30] = '\0';

        char* tempId = malloc(3);
        tempId[3] = '\0';

        char* tempRate = malloc(30);
        tempRate[30] = '\0';

        //Defines how many digits workerId is
        for(int z = 0; z < 30; z++){
            if(buffer[z] == ' '){
                idDigits = z;
                z = 30;
            }
        }

        //Stores workerId in current active worker
        for(int z = 0; z < idDigits; z++){
            tempId[z] = buffer[z];
        }
        currWorker->workerId = atoi(tempId);

        //Loops through line read from file
        for(int i = 0; i < 100; i++){
            //Reads firstname
            for(int z = 0; z < 30; z++){
                if(buffer[z + idDigits + 1] == ' '){
                    tempFirstName[z] = '\0';
                    surnameStart = z + idDigits + 2;
                    z = 30;
                } else{
                    tempFirstName[z] = buffer[z + idDigits + 1];
                }
            }
            //Stores firstname
            currWorker->firstName = &tempFirstName[0];

            //Reads surname
            for(int z = 0; z < 30; z++){
                if(buffer[z + surnameStart] == ' '){
                    tempSurName[z] = '\0';
                    departmentIdStart = z + surnameStart + 1;
                    z = 30;
                } else{
                    tempSurName[z] = buffer[z + surnameStart];
                }
            }
            //Stores surname
            currWorker->surName = &tempSurName[0];

            //Stores departmentId
            currWorker->departmentId = buffer[departmentIdStart] - '0';

            //Reads rate
            for(int z = 0; z < 30; z++){
                if(buffer[z + departmentIdStart + 2] == '\n'){
                    tempRate[z] = '\0';
                    departmentIdStart = z + departmentIdStart + 2;
                    z = 30;
                } else{
                    tempRate[z] = buffer[z + departmentIdStart + 2];
                }
            }
            //Stores rate
            currWorker->rate = atof(tempRate);

            //If we have reached the end of the line, we create a new chain in the linked list and set it to the current active worker.
            if(buffer[i+1] == '\n'){
                i = 100;
                struct Worker* newWorker = malloc(sizeof(worker));
                currWorker->nextWorker = newWorker;
                newWorker->prevWorker = currWorker;
                newWorker->nextWorker = NULL;
                currWorker = newWorker;
            }
        }
    }

    //Sets current active worker to be the first in the linked list
    while(currWorker->prevWorker != NULL){
        currWorker = currWorker->prevWorker;
    }
    fclose(filePtr);
    return currWorker;
}

void udskrivalt(struct Worker* worker){
    //Opens file
    const char* filePath = "./workerInfo.txt";
    FILE *filePtr2;
    filePtr2 = fopen(filePath, "a");

    //Sets current active worker to the first worker
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }

    //Prints all workers information
    /*char* tempWord;
    char* tempExcel;
    char* tempDatabase;
    if(worker->word){
        tempWord = "Taken";
    } else{
        tempWord = "Not taken";
    }
    if(worker->excel){
        tempExcel = "Taken";
    } else{
        tempExcel = "Not taken";
    }
    if(worker->database){
        tempDatabase = "Taken";
    } else{
        tempDatabase = "Not taken";
    }*/
    printf("%d %s %s %d %.2f\n", worker->workerId, worker->firstName, worker->surName, worker->departmentId, worker->rate/*, tempWord, tempExcel, tempDatabase*/);
    if(filePtr2 == NULL){
        printf("ERR: %s could not be opened", filePath);
    } else{
        fprintf(filePtr2, "%d %s %s %d %.2f\n", worker->workerId, worker->firstName, worker->surName, worker->departmentId, worker->rate/*, tempWord, tempExcel, tempDatabase*/);
    }
    while(worker->nextWorker != NULL){
        /*if(worker->nextWorker->word){
            tempWord = "Taken";
        } else{
            tempWord = "Not taken";
        }
        if(worker->nextWorker->excel){
            tempExcel = "Taken";
        } else{
            tempExcel = "Not taken";
        }
        if(worker->nextWorker->database){
            tempDatabase = "Taken";
        } else{
            tempDatabase = "Not taken";
        }*/
        printf("%d %s %s %d %.2f\n", worker->nextWorker->workerId, worker->nextWorker->firstName, worker->nextWorker->surName, worker->nextWorker->departmentId, worker->nextWorker->rate/*, tempWord, tempExcel, tempDatabase*/);
        if(filePtr2 == NULL){
            printf("ERR: %s could not be opened", filePath);
        } else{
            fprintf(filePtr2, "%d %s %s %d %.2f\n", worker->nextWorker->workerId, worker->nextWorker->firstName, worker->nextWorker->surName, worker->nextWorker->departmentId, worker->nextWorker->rate/*, tempWord, tempExcel, tempDatabase*/);
        }
        worker = worker->nextWorker;
    }
    printf("\n");
    fprintf(filePtr2, "\n");
    fclose(filePtr2);
}

void slet(struct Worker* worker, int workerIndex){
    //Sets current worker to the first worker
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    for(int i = 1; i < workerIndex; i++){
        worker = worker->nextWorker;
    }
    worker->prevWorker->nextWorker = worker->nextWorker;
    worker->nextWorker->prevWorker = worker->prevWorker;
    free(worker);
}

void deleteAllWorkers(struct Worker* worker){
    //Sets active worker to last worker
    while(worker->nextWorker != NULL){
        worker = worker->nextWorker;
    }
    //Deletes workers 1 at a time
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
        free(worker->nextWorker);
    }
    free(worker);
}

void tilfoej(struct Worker* worker, char* firstName, char* surName, int departmentId, float rate){
    while(worker->nextWorker != NULL){
        worker = worker->nextWorker;
    }
    
    struct Worker* newWorker = malloc(sizeof(worker));
    worker->nextWorker = newWorker;
    newWorker->prevWorker = worker;
    newWorker->nextWorker = NULL;
    worker = newWorker;

    worker->workerId = worker->prevWorker->workerId + 1;
    worker->firstName = firstName;
    worker->surName = surName;
    worker->departmentId = departmentId;
    worker->rate = rate;
}

void nysats(struct Worker* worker, int department, float percentIncrease){
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    do{
        if(worker->departmentId = department){
            worker->rate = worker->rate*(1 + percentIncrease/100.f);
        }
        worker = worker->nextWorker;
    } while(worker->nextWorker != NULL);
}

void gennemsnit(struct Worker* worker){
    float total;
    int workerCount;
    int avgRate;
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    while(worker->nextWorker != NULL){
        total += worker->rate;
        workerCount++;
        worker = worker->nextWorker;
    }
    avgRate = total/(float)workerCount;

}

int main()
{
    //dynamicBuffer* buffer = allocNewBuffer();
    //Creates new worker
    struct Worker* firstWorker;

    //Reads all other workers from file, and links them to first worker
    firstWorker = indlaes();

    //Calculates the average rate
    //gennemsnit(firstWorker);

    //Prints all workers information
    udskrivalt(firstWorker);

    //Sets new rate
    nysats(firstWorker, 3, 5.f);
    udskrivalt(firstWorker);

    //Adds a new worker
    tilfoej(firstWorker, "Erik", "Eriksen", 3, 260.75);
    udskrivalt(firstWorker);
    

    //Deletes worker 4
    slet(firstWorker, 4);
    udskrivalt(firstWorker);

    deleteAllWorkers(firstWorker);
    return 0;
}
