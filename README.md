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
```
<<Insert Pseudo code here, plz.>>
```

## Sorting algorithms
The challenge here is memory management and division of it between all the threads