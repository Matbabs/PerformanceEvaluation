import time
import sys
from random import randint


def main(nSteps=1000000, nThreads=8):
    """
    Main program, calculates the approximation of PI
    :param nSteps: Size of the tab to generate
    :param nThreads: Number of threads (unused for serialized version)
    :return: Time taken to calculate
    """
    tab = [randint(1, nSteps) for _ in range(nSteps)]
    t1 = time.time()
    tab.sort()
    return time.time() - t1


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

    theTime = main(niter, nthreads)
    print("{}".format(theTime))
