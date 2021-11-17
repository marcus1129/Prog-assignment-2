#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>


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
    bool word;
    bool excel;
    bool database;
} worker;

struct Worker* indlaes(FILE* filePtr){
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
    return currWorker;
}

void udskrivalt(struct Worker* worker, FILE* filePtr2){
    //Sets current active worker to the first worker
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }

    //Prints all workers information
    char* tempWord;
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
    }
    printf("%d %s %s %d %.2f Word: %s, Excel: %s, Database: %s\n", worker->workerId, worker->firstName, worker->surName, worker->departmentId, worker->rate, tempWord, tempExcel, tempDatabase);
    if(filePtr2 == NULL){
        printf("Error opening file");
    } else{
        fprintf(filePtr2, "%d %s %s %d %.2f Word: %s, Excel: %s, Database: %s\n", worker->workerId, worker->firstName, worker->surName, worker->departmentId, worker->rate, tempWord, tempExcel, tempDatabase);
    }
    while(worker->nextWorker != NULL){
        if(worker->nextWorker->word){
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
        }
        printf("%d %s %s %d %.2f Word: %s, Excel: %s, Database: %s\n", worker->nextWorker->workerId, worker->nextWorker->firstName, worker->nextWorker->surName, worker->nextWorker->departmentId, worker->nextWorker->rate, tempWord, tempExcel, tempDatabase);
        if(filePtr2 == NULL){
            printf("Error opening file");
        } else{
            fprintf(filePtr2, "%d %s %s %d %.2f Word: %s, Excel: %s, Database: %s\n", worker->nextWorker->workerId, worker->nextWorker->firstName, worker->nextWorker->surName, worker->nextWorker->departmentId, worker->nextWorker->rate, tempWord, tempExcel, tempDatabase);
        }
        worker = worker->nextWorker;
    }
    printf("\n");
    if(filePtr2 == NULL){
        printf("Error opening file");
    } else{
        fprintf(filePtr2, "\n");
    }
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
    //free(worker);
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
    struct Worker* activeWorker = worker;
    while(activeWorker->nextWorker != NULL){
        activeWorker = activeWorker->nextWorker;
    }

    struct Worker* newWorker = malloc(sizeof(worker));
    activeWorker->nextWorker = newWorker;
    newWorker->prevWorker = activeWorker;
    newWorker->nextWorker = NULL;
    
    activeWorker = newWorker;

    activeWorker->workerId = activeWorker->prevWorker->workerId + 1;
    activeWorker->firstName = firstName;
    activeWorker->surName = surName;
    activeWorker->departmentId = departmentId;
    activeWorker->rate = rate;
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

void gennemsnit(struct Worker* worker, FILE* filePtr){
    float total;
    float avgRate;
    int workerCount;

    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    jumpPoint:
    total += worker->rate;
    workerCount++;
    if(worker->nextWorker != NULL){
        worker = worker->nextWorker;
        goto jumpPoint;
    }
    avgRate = total/(float)workerCount;
    printf("Average Rate: %d\n", workerCount);
    if(filePtr != NULL){
        fprintf(filePtr, "Average Rate: %.2f\n", avgRate);
    }
}

void indlaeskurser(struct Worker* worker, FILE* filePtr3){
    //Initiates string buffer
    char* buffer = malloc(1001);
    int idDigits;
    char tempId[30];
    int tempComp;
    buffer[1001] = '\0';
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    worker->word = false;
    worker->excel = false;
    worker->database = false;
    while(worker->nextWorker != NULL){
        worker->nextWorker->word = false;
        worker->nextWorker->excel = false;
        worker->nextWorker->database = false;
        worker = worker->nextWorker;
    }

    //Reads from file
    while(fgets(buffer, 1000, filePtr3)!= NULL){
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
        tempId[idDigits] = '\0';

        if(idDigits > 1){
            tempComp = atoi(tempId);
        } else{
            tempComp = tempId[0] - '0';
        }

        char* temp = malloc(30);
        while(worker->prevWorker != NULL){
            worker = worker->prevWorker;
        }
        while(worker->workerId != tempComp){
            worker = worker->nextWorker;
        }
        for(int z = 0; z < 30; z++){
            if(buffer[z + idDigits + 1] == '\n'){
                temp[z] = '\0';
                z = 30;
            } else{
                temp[z] = buffer[z + idDigits + 1];
            }
        }
        if(strcmp(temp, "word") == 0){
            worker->word = true;
        } else if(strcmp(temp, "excel") == 0){
            worker->excel = true;
        } else if(strcmp(temp, "database") == 0){
            worker->database = true;
        }
        memset(temp,0,strlen(temp));
    }
}

void kursusmed(struct Worker* worker, FILE* filePtr, const char* course){
    int workerList[40];
    int i = 0;
    while(worker->prevWorker != NULL){
        worker = worker->prevWorker;
    }
    if(strcmp(course, "word") == 0){
        if(worker->word == true){
            workerList[i] = worker->workerId;
            i++;
        }
    } else if(strcmp(course, "excel") == 0){
        if(worker->excel == true){
            workerList[i] = worker->workerId;
            i++;
        }
    } else if(strcmp(course, "database") == 0){
        if(worker->database == true){
            workerList[i] = worker->workerId;
            i++;
        }
    }
    
    while(worker->nextWorker != NULL){
        if(strcmp(course, "word") == 0){
            if(worker->nextWorker->word == true){
                workerList[i] = worker->nextWorker->workerId;
                i++;
            }
        } else if(strcmp(course, "excel") == 0){
            if(worker->nextWorker->excel == true){
                workerList[i] = worker->nextWorker->workerId;
                i++;
            }
        } else if(strcmp(course, "database") == 0){
            if(worker->nextWorker->database == true){
                workerList[i] = worker->nextWorker->workerId;
                i++;
            }
        }
        worker = worker->nextWorker;
    }
    for(int z = 0; z < i; z++){
        printf("%d\n", workerList[z]);
    }
}

int main()
{
    const char* filePath = "./workerInfo.txt";
    const char* workerInfoPath = "./tekstfil.txt";
    const char* coursePath = "./kurser.txt";
    FILE* filePtr;
    FILE* filePtr2;
    FILE* filePtr3;
    filePtr = fopen(filePath, "a");
    filePtr2 = fopen(workerInfoPath, "r");
    filePtr3 = fopen(coursePath, "r");
    

    //dynamicBuffer* buffer = allocNewBuffer();
    //Creates new worker
    struct Worker* firstWorker;

    //Reads all other workers from file, and links them to first worker
    firstWorker = indlaes(filePtr2);

    //Gets worker courses
    indlaeskurser(firstWorker, filePtr3);

    //Prints all workers information
    udskrivalt(firstWorker, filePtr);

    //Calculates the average rate
    gennemsnit(firstWorker, filePtr);

    //Sets new rate
    nysats(firstWorker, 3, 5.f);
    udskrivalt(firstWorker, filePtr);

    //Adds a new worker
    tilfoej(firstWorker, "Erik", "Eriksen", 3, 260.75);
    udskrivalt(firstWorker, filePtr);
    
    //Deletes worker 4
    slet(firstWorker, 4);
    udskrivalt(firstWorker, filePtr);

    //Gets all workers that has taken the course
    kursusmed(firstWorker, filePtr, "word");

    //Deletes all workers
    deleteAllWorkers(firstWorker);

    fflush(filePtr);
    fflush(filePtr2);
    fflush(filePtr3);

    fclose(filePtr);
    fclose(filePtr2);
    fclose(filePtr3);
    return 0;
}
