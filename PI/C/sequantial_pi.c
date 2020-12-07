#include "./processing.h"

//compile with `gcc sequantial_pi.c processing.h -l pthread -lm -o sequantial_pi`

int main (int argc, char *argv[]) { 
    double pi;
    initProcessing(argc,argv);
    long nb_pas = nbIterations;

    timerStart();
    for(long k=0;k<nb_pas;k++)
        pi += 4.0 * pow(-1, k) / (2*k + 1);
    timerStop();

    printf("%f\n",pi);
    printf("%f\n", timerDuration());
    return 0;
}