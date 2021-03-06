from math import floor

import time
import sys


def compute(start: int, end: int, steps: float):
    """
    Function to calculate the PI approximation. It only calculates the portion between "start" and "end".
    :param start: Where this function starts calculating
    :param end: Where this function stop calculating
    :param steps: 1/number of steps
    :return: The calculated portion
    """
    sum = 0.0
    for ii in range(start, end):
        x = (ii-0.5)*steps
        sum += 4.0 / (1.0 + x * x)

    return sum


def main(nSteps=1000000, nThreads=8):
    """
    Main program, calculates the approximation of PI
    :param nSteps: Number of steps for the algorithm
    :param nThreads: Number of threads (unused for serialized version)
    :return: Tuple with PI approximation and time taken to calculate
    """
    nb_steps = nSteps or 1000000
    threads = nThreads or 8
    sumpi = 0.0
    steps = 1 / nb_steps

    div = floor(nb_steps / threads)
    last_div = div + nb_steps - div * threads  # Add what's remaining to the last thread

    t1 = time.time()
    # Starts threads-1 threads
    for ii in range(0, threads - 1):
        sumpi += compute(ii * div, (ii+1)*div, steps)
    # The last thread
    sumpi += compute((threads-1)*div, (threads-1)*div + last_div, steps)

    return steps * sumpi, time.time() - t1


if __name__ == '__main__':
    if len(sys.argv) > 3:
        print("USAGE :\n./main.py NITERATIONS NTHREADS")
        exit(0)
    niter = 1000000
    nthreads = 8
    try:
        if len(sys.argv) > 1:
            niter = int(sys.argv[1])
        if len(sys.argv) == 3:
            nthreads = int(sys.argv[2])
        if niter < 1 or nthreads < 1:
            raise ValueError("Negative arguments")
    except ValueError as e:
        print("Invalid argument type : {}".format(e))
        exit(0)

    pi, theTime = main(niter, nthreads)
    print("{}\n{}".format(pi, theTime))

