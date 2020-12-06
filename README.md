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

# Phases
The project will be divided into phases. The completion of the phases depends of the efficiency of the group and/or the time found to complete them.

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
