# Threading Frenzy

## Introduction

![](https://img.shields.io/static/v1.svg?label=Multithreading&message=Frenzy&color=2cb6aa)
![](https://img.shields.io/static/v1.svg?label=&message=C&color=5c6bc0)
![](https://img.shields.io/static/v1.svg?label=&message=CPP&color=659ad2)
![](https://img.shields.io/static/v1.svg?label=&message=Python&color=ffd340)
![](https://img.shields.io/static/v1.svg?label=&message=Java&color=ea2d2e)
![](https://img.shields.io/static/v1.svg?label=&message=Go&color=2cb6aa)
![](https://img.shields.io/static/v1.svg?label=&message=Rust&color=fbbc04)
![](https://img.shields.io/static/v1.svg?label=&message=Ruby&color=a81401)

This repository is the result of our Performance Evaluation project (november-december 2020).
Our team was composed of Volodia PAROL-GUARINO, Matisse BABONNEAU and Alexandre DUVIVIER

# Goals
The goal of the project is to evaluate the performances of different multithreading approaches. We are testing aspects such as :
- Languages
- Recommended libraries
- Compilators / Interpretors
- Compilation options (optimisations, memory management...)
- SDKs

We will compare the performance in two categories:
- the first one is a global comparaison (to find the best of the best) ;
- the second one is to analyze the result grouping them by the language they are written in (to find the best possible implementation in languages where parameters are varying).

![](https://geekflare.com/wp-content/uploads/2020/07/Go-Logo_Aqua-e1595512116516-600x270.png =50x)

# Actual Content
This project was split into 2 parts :
- Pi : We evaluated the performances of each language solution using the Pi approximation algorithm.
- Sorting : We evaluated the performances of each chosen language implementation for array sorting.
The following languages / libraries were used :
- C (Pi Sequential; Pi parallel (PThread, OpenMP (Not used), MPI (Not used)))
- C++ (Pi Sequential, Pi Parallel (Boost), Sorting (Boost))
- Ruby (Pi Sequential; Pi parallel; Sorting (Default implementation))
- Rust (Pi Sequential; Pi parallel; Sorting (Default implementation))
- Java (Pi Sequential; Pi parallel; Sorting (Default implementation); Sorting Parallel)
- Python (Pi Sequential; Pi parallel; Sorting (Default implementation); Sorting Parallel)
- Go (Pi Sequential; Pi parallel; Sorting Sequential)

# Original Phases
The project was original divided into phases. The completion of each phases depended of the efficiency of the group and/or the time found to complete them.
This part isn't up-to-date anymore, and is here to compare with actual achievements.


## Phase 1 (mandatory)
Algorithms:
- PI

Implementation in:
- Go (native, [gofast](https://github.com/Matbabs/gofast))
- C (Using MPI, OpenMP, PThreads)
- C++ (Boost)
- JAVA (using SDKs from different vendors + synchronized/semaphores)
- Python (Multiprocessing)

## Phase 2 (optional but recommended)
Algorithms :
- Sorting algorithms (sequential / parallel)

Implementation in :
- Phase 1 languages

## Phase 3 (optional)

Algorithms :
- Phase 1 & 2 algorithms

Implementation in :
- Rust
- Ruby
- Kotlin


# Algorithms

Please note that each algorithm should be provided in both sequential and parallel versions.

## PI
### Sequential
```c
nb_steps = 1000000
sum = 0.0
steps = 1 / nb_steps

for (ii = 1 ;  ii <= nb_steps ; ++ii){
    x = (i-0.5)*steps
    sum += 4.0 / (1.0 + x * x)
}

p = steps * sum
```

### Parallel
```c
compute(start, end, steps){
    sum = 0.0
    x = 0.0

    for (ii = start ;  ii <= end ; ++ii){
        x = (ii-0.5)*steps
        sum += 4.0 / (1.0 + x * x)
    }

    return sum
}

main() {
    nb_steps = 1000000
    threads = 4
    sum = 0.0
    steps = 1 / nb_steps

    div = (int) nb_steps / threads
    last_div = div + nb_steps - div * threads // add what's missing to the last thread

    // start threads-1 threads
    for (ii = 1; ii < threads - 1 ; ++ii){
        start_thread((id_thread) -> {
            sum += compute(id_thread * div, (id_thread+1)*div, steps)
        })
    }

    sum += compute((threads-1)*div, (threads-1)*div + last_div, steps)

    wait_for_all_threads()

    p = steps * sum
}
```

## Sorting algorithms
The challenge here is memory management and division of it between all the threads

# Content of the repo
## PI : Approximation using the above algorithms

Note that all programs under this section use the following syntax :
`./PROG ITERATIONS NTHREADS`
where
PROG is the program to call
ITERATIONS is the number of iterations to run for the PI approximation
NTHREADS is the number of parallel threads

Each program prints on stdout the estimated value of PI on a first line, then the time mesured for the calcul. Ex :
```
3.1415946535888706
0.10193371772766113
```
Here the program took ~100ms to complete

List of files :
- Java = Java implementations (the parallel stream implementation's NTHREADS refert to the parallelism value of the common thread pool)
- Projet_Python = Python implementations.
- Makefile = Makefile to build and run everything.
- runner.sh = Runner script which automatically runs benchmarks for a given program.

## Sorting

Note that all programs under this section use the following syntax :
`./PROG ARRAY_SIZE NTHREADS`
where
PROG is the program to call
ARRAY_SIZE is the size of the array to be generated (values are integers ranging from 0 to ARRAY_SIZE exclusive)
NTHREADS is the number of threads

Each program prints on stdout the estimated time to sort (not to generate the array)
```
7.2830092
```
Here the program took about 7 seconds to complete.

Exceptions:
- Java parallel implementation is currently using the parameter NTHREADS as the parallelism value.
- Python parallel version takes the NTHREADS parameter as a deepness value instead of a number of threads.

# How to build results
Each part (PI / Sort) contains a Makefile :
- 'make clean' : Clean the project
- 'make' : Build all codes (will complain if it cannot compile one specific language, but it won't stop)
- 'make runPI' : Run PI benchmarks
- 'make runSort' : Run Sort benchmarks
- 'make buildRez' : Export data into CSVs

Once 'make buildRez' has finished, final results can be found in the data/ folder.
You can find data under the given formats :
N;NTHREADS[;DATA];TIME
where :
- N is the program parameter for the size of the array (sorting) or the precision of the approximation (pi)
- NTHREADS is the number of threads (1 for sequential)
- DATA is only there for PI approximation, and gives the result of the algorithm
- TIME is the time taken to complete.

Each configuration (N;NTHREADS) is run 10 times, you can get the average using the corresponding 'tools/uniformize.rb' script :
- Pi : `cd PI/data/ && ruby ../../tools/uniformize_pi.rb `ls``
- Sort : `cd Sort/data/ && ruby ../../tools/uniformize_sort.rb \`ls\``

This script will create files names XXX_uniformized.csv, which contain the average measures for each configuration, without the DATA column.

