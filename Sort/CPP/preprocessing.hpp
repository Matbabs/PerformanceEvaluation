#include <cstddef>
#include <iostream>
#include <chrono>

#ifndef CPP_PREPROCESSING_HPP
#define CPP_PREPROCESSING_HPP

class Preprocessing {
public:
    Preprocessing(int argc, char **argv);

    void timer_start();

    void timer_stop();

    double timer_duration() const;

    size_t get_nb_threads() const;

    size_t get_array_size() const;

private:
    size_t m_nb_threads;
    size_t m_array_size;

    typedef std::chrono::high_resolution_clock::time_point TimeVar;

    TimeVar m_start;
    TimeVar m_end;
};


#endif //CPP_PREPROCESSING_HPP