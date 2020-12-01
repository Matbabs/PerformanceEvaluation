#include <iostream>
#include "preprocessing.hpp"


class Pi {
public:
    Pi(size_t nb_steps, size_t nb_threads);

    double compute() const;

private:

    const size_t m_nb_steps;
    const size_t m_nb_threads;
    const double m_steps;
};

Pi::Pi(const size_t nb_steps, const size_t nb_threads)
        : m_nb_steps(nb_steps),
          m_nb_threads(nb_threads),
          m_steps(1.0 / (double) m_nb_steps) {
}


double Pi::compute() const {
    double sum = 0.0;

    for (size_t ii = 0; ii < m_nb_steps; ++ii) {
        double temp = (ii - 0.5) * m_steps;
        sum += 4.0 / (1.0 + temp * temp);
    }

    return sum * m_steps;
}

int main(int argc, char *argv[]) {
    Preprocessing preprocess(argc, argv);

    preprocess.timer_start();
    Pi pi(preprocess.get_nb_iterations(), preprocess.get_nb_threads());
    double res = pi.compute();
    preprocess.timer_stop();

    std::cout << res << std::endl;
    std::cout << preprocess.timer_duration() << std::endl;

    return 0;
}