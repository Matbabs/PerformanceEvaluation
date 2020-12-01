#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//compile with `gcc c_pi.c -l pthread -lm -o c_pi`

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

#define NB_THREADS 50

int main () { 
    static long nb_pas = 1000000;
    pthread_t  p_thread[NB_THREADS];
    Step steps[NB_THREADS];
    double pi,bloc; 
    bloc = nb_pas/NB_THREADS;
    for(int i=0;i<NB_THREADS;i++){
        steps[i].start = bloc*i;
        steps[i].inc = bloc;
        steps[i].res = 0;
        pthread_create(&p_thread[i],NULL, c_pi, &steps[i]);
    }
    for(int i=0;i<NB_THREADS;i++){
        pthread_join(p_thread[i],NULL);
        pi += steps[i].res;
    }
    printf("%f\n",pi);
    return 0;
}