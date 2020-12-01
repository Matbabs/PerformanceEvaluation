from math import floor
import time
import sys

from multiprocessing import Pool

def compute(start, end, steps):
    sum = 0.0
    x = 0.0
    for ii in range(start, end):
        x = (ii-0.5)*steps
        sum += 4.0 / (1.0 + x * x)

    return sum

def main():
    nb_steps = 1000000
    threads = 8
    sum = 0.0
    steps = 1 / nb_steps

    div = floor(nb_steps / threads)
    last_div = div + nb_steps - div * threads # add what's missing to the last thread

    poolDef = []

    for ii in range(0, threads-1):
        poolDef.append((ii*div, (ii+1)*div, steps))
    poolDef.append(((threads-1)*div, (threads-1)*div + last_div, steps))

    # #start threads-1 threads
    # for ii in range(0, threads - 1):
    #     sum += compute(ii * div, (ii+1)*div, steps)
    #
    # sum += compute((threads-1)*div, (threads-1)*div + last_div, steps)
    t1 = time.time()
    with Pool(threads) as p:
        rez = p.starmap(compute, poolDef)
    for e in rez:
        sum += e
    print("Time : {}".format(time.time() - t1))

    return steps * sum


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print(main())

