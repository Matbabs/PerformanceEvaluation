#include <boost/thread/thread.hpp>
#include <iostream>
#include "preprocessing.hpp"


class Pi {
public:
    Pi(size_t nb_steps, size_t nb_threads);

    double compute();

private:

    void compute_part(size_t thread_id, size_t start, size_t end);

    const size_t m_nb_steps;
    const size_t m_nb_threads;
    const double m_steps;
    std::vector<std::unique_ptr<boost::thread>> m_threads;
    std::vector<double> m_results;

};

Pi::Pi(const size_t nb_steps, const size_t nb_threads)
        : m_nb_steps(nb_steps),
          m_nb_threads(nb_threads),
          m_steps(1.0 / (double) m_nb_steps) {
    m_threads.reserve(m_nb_threads);
    m_results.reserve(m_nb_threads);
}

void Pi::compute_part(const size_t thread_id, const size_t start, const size_t end) {
    double sum = 0.0;
    for (size_t ii = start; ii < end; ++ii) {
        double temp = (ii - 0.5) * m_steps;
        sum += 4.0 / (1.0 + temp * temp);
    }
    m_results[thread_id] = sum;
}

double Pi::compute() {
    size_t numberIterationsPerThread = m_nb_steps / m_nb_threads;
    double sum = 0.0;

    for (size_t ii = 0; ii < m_nb_threads; ++ii) {
        m_threads.push_back(std::make_unique<boost::thread>(
                [
                        this,
                        ii,
                        capture_start = ii * numberIterationsPerThread,
                        capture_end = ii < m_nb_threads - 1 ? (ii + 1) * numberIterationsPerThread : m_nb_steps
                ] {
                    compute_part(ii, capture_start, capture_end);
                }));
    }

    for (size_t ii = 0; ii < m_nb_threads; ++ii) {
        m_threads[ii].get()->join();
        sum += m_results[ii];
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