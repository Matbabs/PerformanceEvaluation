import java.util.stream.IntStream;

public class SequentialStream {
    public static void main(String[] args) {
        Preprocessing preprocessing = new Preprocessing(args);
        int nb_steps = preprocessing.getNbIterations();
        preprocessing.timerStart();

        double sum;
        double steps = 1.0 / (double) nb_steps;

        sum = IntStream.rangeClosed(0, nb_steps).mapToDouble(ii -> (ii - 0.5) * steps).map(x -> 4.0 / (1.0 + x * x)).sum();

        sum *= steps;

        preprocessing.timerStop();

        System.out.println(sum);
        System.out.println(preprocessing.timerDuration());
    }
}
