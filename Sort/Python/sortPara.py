#!/usr/bin/python3

# Source : https://stackoverflow.com/questions/12451651/multi-process-quicksort-in-python-hangs-for-large-numbers-of-elements
import random, multiprocessing, time, sys, math

DESIRED_PROC_DEPTH = 4
proc_depth = 1 #start at one to count the parent process that kicks this all off


def main(nSteps=1000000, nThreads=8):
    """
    Main program, calculates the approximation of PI
    :param nSteps: Size of the tab to generate
    :param nThreads: Number of threads (unused for serialized version)
    :return: Time taken to calculate
    """
    # import sys; sys.setrecursionlimit(2**30)
    num_elements = 1000000
    list_of_numbers = [random.randint(0,nSteps) for num in range(nSteps)]
    # print list_of_numbers
    # simple_start = time.time()
    # simple_sorted = simple_qs(list_of_numbers)
    # simple_total_time = time.time() - simple_start
    # print("Using a single thread we sorted " + str(num_elements) + " elements in " + str(simple_total_time) + " seconds")
    the_q = multiprocessing.Queue()
    sorter = MTQuickSort(list_of_numbers, the_q, math.floor(math.log(nThreads, 2)))
    start = time.time()
    sorter.start()
    sorted_list = the_q.get()
    sorter.join()
    mt_total_time = time.time() - start
    # print sorted_list
    # print("Sorted " + str(nSteps) + " elements in " + str(mt_total_time) + " seconds")
    return mt_total_time


class MTQuickSort(multiprocessing.Process):
    DESIRED_PROC_DEPTH = 2
    def __init__(self, list_to_sort, queue, nThreads):
        super(MTQuickSort, self).__init__()
        # print(self.name)
        self.queue = queue
        self.list = list_to_sort
        self.DESIRED_PROC_DEPTH = nThreads

    def run(self):
        self.queue.put(self.quicksort(self.list))

    def quicksort(self, list):
        global proc_depth
        if len(list) == 0:
            # base case is that list is empty
            return []
        else:
            pivot = list[0]
            less = [x for x in list[1:] if x <= pivot]
            greater = [x for x in list[1:] if x > pivot]
            if proc_depth < DESIRED_PROC_DEPTH:
                proc_depth += 1
                # We create threads in blocks of two since we partition the list into two parts
                lessor_q = multiprocessing.Queue()
                greater_q = multiprocessing.Queue()
                qs_process1 = MTQuickSort(less, lessor_q, self.DESIRED_PROC_DEPTH)
                qs_process2 = MTQuickSort(greater, greater_q, self.DESIRED_PROC_DEPTH)
                qs_process1.start()
                qs_process2.start()
                rez = lessor_q.get() + [pivot] + greater_q.get()
                qs_process1.join()
                qs_process2.join()
                return rez
            else:
                less_than_pivot = self.quicksort(less)
                greater_than_pivot = self.quicksort(greater)
                return less_than_pivot + [pivot] + greater_than_pivot

def simple_qs(list):
    if len(list) == 0:
        # base case is that list is empty
        return []
    else:
        pivot = list[0]
        return simple_qs([x for x in list[1:] if x <= pivot]) + [pivot] + simple_qs([x for x in list[1:] if x > pivot])


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

