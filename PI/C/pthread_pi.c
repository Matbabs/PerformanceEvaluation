#include "./processing.h"

//compile with `gcc pthread_pi.c processing.h -l pthread -lm -o pthread_pi`

typedef struct Step{
    double start;
    long inc;
    double res;
}Step;

void* c_pi(void *st){
    Step *step = st;   
    for(long k=step->start;k<step->start+step->inc;k++){
        step->res += 4.0 * pow(-1, k) / (2*k + 1);
    }
}

int main (int argc, char *argv[]) { 

    initProcessing(argc,argv);

    long nb_pas = nbIterations;
    pthread_t  p_thread[nbThreads];

    timerStart();

    Step steps[nbThreads];
    double pi,bloc; 
    bloc = nb_pas/nbThreads;
    for(int i=0;i<nbThreads;i++){
        steps[i].start = bloc*i;
        steps[i].inc = bloc;
        steps[i].res = 0;
        pthread_create(&p_thread[i],NULL, c_pi, &steps[i]);
    }
    for(int i=0;i<nbThreads;i++){
        pthread_join(p_thread[i],NULL);
        pi += steps[i].res;
    }

    timerStop();

    printf("%f\n",pi);
    printf("%f\n", timerDuration());
    return 0;
}