#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#ifndef _PROCESSING_H_
#define _PROCESSING_H_

    int nbIterations;
    int nbThreads;
    clock_t startTime, endTime;

    void initProcessing(int argc, char *argv[]){
        if(argc != 3){
            printf("Usage: <number of iterations> <number of threads>\n");
            exit(1);
        }
        nbIterations = atoi(argv[1]);
        nbThreads = atoi(argv[2]);
    }

    void timerStart() {
        startTime = clock();
    }

    void timerStop() {
        endTime = clock();
    }

    double timerDuration() {
        return ((float)(endTime - startTime))/CLOCKS_PER_SEC;
    }
    
#endif