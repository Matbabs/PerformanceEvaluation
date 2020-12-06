import java.util.Properties;
import java.util.stream.IntStream;

public class ParallelStream {
    public static void main(String[] args){
        Preprocessing preprocessing = new Preprocessing(args);
        int nb_steps = preprocessing.getNbIterations();
        preprocessing.timerStart();

        // Control the parallelism factor:
        //      - parallelism > 2 — JDK creates the (# of CPUs - 1) threads for the commonPool
        //      - parallelism = 1 — JDK creates a new thread for every submitted task
        //      - parallelism = 0 — a submitted task is executed on a caller thread
        Properties props = System.getProperties();
        props.setProperty("java.util.concurrent.ForkJoinPool.common.parallelism", String.valueOf(preprocessing.getNbThreads()));

        double sum;
        double steps = 1.0 / (double) nb_steps;

        sum = IntStream.rangeClosed(0, nb_steps).parallel().mapToDouble(ii -> (ii - 0.5) * steps).map(x -> 4.0 / (1.0 + x * x)).sum();

        sum*= steps;

        preprocessing.timerStop();

        System.out.println(sum);
        System.out.println(preprocessing.timerDuration());
    }
}
