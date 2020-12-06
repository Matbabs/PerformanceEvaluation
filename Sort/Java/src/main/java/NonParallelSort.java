import java.util.Arrays;
import java.util.Properties;
import java.util.Random;

public class NonParallelSort {
    public static void main(final String[] args) {
        final var preprocessing = new Preprocessing(args);

        int[] array = new Random().ints(preprocessing.getArraySize(), 0, preprocessing.getArraySize()).toArray();

        preprocessing.timerStart();
        Arrays.sort(array);

        preprocessing.timerStop();

        System.out.println(preprocessing.timerDuration());
    }
}
