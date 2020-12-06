#include <boost/sort/sort.hpp>
#include <iostream>
#include "preprocessing.hpp"

int main(int argc, char *argv[]) {
    Preprocessing preprocess(argc, argv);

    preprocess.timer_start();

    const size_t sz = preprocess.get_array_size();
    std::vector<int> randArray(sz);
    for(int i=0;i<sz;i++)
        randArray[i]=rand()%sz;  //Generate number between 0 to array_size

    boost::sort::sample_sort(randArray.begin(), randArray.end(), preprocess.get_nb_threads());

    preprocess.timer_stop();

    std::cout << preprocess.timer_duration() << std::endl;

    return 0;
}