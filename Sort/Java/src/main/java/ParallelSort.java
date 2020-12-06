import java.util.Arrays;
import java.util.Properties;
import java.util.Random;

public class ParallelSort {
    public static void main(final String[] args) {
        final var preprocessing = new Preprocessing(args);

        // Control the parallelism factor:
        //      - parallelism > 2 — JDK creates the (# of CPUs - 1) threads for the commonPool
        //      - parallelism = 1 — JDK creates a new thread for every submitted task
        //      - parallelism = 0 — a submitted task is executed on a caller thread
        Properties props = System.getProperties();
        props.setProperty("java.util.concurrent.ForkJoinPool.common.parallelism", String.valueOf(preprocessing.getParallelism()));

        int[] array = new Random().ints(preprocessing.getArraySize(), 0, preprocessing.getArraySize()).toArray();

        preprocessing.timerStart();
        Arrays.parallelSort(array);

        preprocessing.timerStop();

        System.out.println(preprocessing.timerDuration());
    }
}
