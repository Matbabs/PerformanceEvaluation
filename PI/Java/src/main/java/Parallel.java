public class Parallel extends Thread {
    private final int startingStep;
    private final int endingStep;
    private final double steps;
    private double sum = 0.0;

    public Parallel(final int start, final int end, final double steps) {
        this.startingStep = start;
        this.endingStep = end;
        this.steps = steps;
    }

    @Override
    public void run() {
        super.run();
        for (int ii = startingStep; ii < endingStep; ++ii) {
            double temp = (ii - 0.5) * steps;
            sum += 4.0 / (1.0 + temp * temp);
        }
    }

    double getSum() {
        return this.sum;
    }

    public static void main(String[] args) throws InterruptedException {
        Preprocessing preprocessing = new Preprocessing(args);
        int nb_steps = preprocessing.getNbIterations();
        int numberThreads = preprocessing.getNbThreads(); // greater or equal to 2
        preprocessing.timerStart();

        double sum = 0.0;
        double steps = 1.0 / (double) nb_steps;

        Parallel[] threads = new Parallel[numberThreads];

        int numberIterationsPerThread = nb_steps / numberThreads;

        for (int ii = 0; ii < numberThreads; ++ii) {
            threads[ii] = new Parallel(ii * numberIterationsPerThread,
                    ii < numberThreads - 1 ? (ii + 1) * numberIterationsPerThread : nb_steps,
                    steps);
            threads[ii].start();
        }

        for (int ii = 0; ii < numberThreads; ++ii) {
            threads[ii].join();
            sum += threads[ii].getSum();
        }

        sum *= steps;

        preprocessing.timerStop();

        System.out.println(sum);
        System.out.println(preprocessing.timerDuration());
    }
}
