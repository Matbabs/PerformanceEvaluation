#include <boost/thread/thread.hpp>
#include <iostream>


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
    Pi pi(1000000000, 4);
    double res = pi.compute();
    std::cout << "Pi: " << res << std::endl;

    return 0;
}