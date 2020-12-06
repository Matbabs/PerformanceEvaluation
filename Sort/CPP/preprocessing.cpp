#include "preprocessing.hpp"

Preprocessing::Preprocessing(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <array size> <number of threads>";
        exit(0);
    }

    m_array_size = atoi(argv[1]);
    m_nb_threads = atoi(argv[2]);
}

void Preprocessing::timer_start() {
    m_start = std::chrono::high_resolution_clock::now();
}

void Preprocessing::timer_stop() {
    m_end = std::chrono::high_resolution_clock::now();
}

double Preprocessing::timer_duration() const {
    return std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count() * 1e-6;
}

size_t Preprocessing::get_nb_threads() const { return m_nb_threads; }

size_t Preprocessing::get_array_size() const { return m_array_size; }
