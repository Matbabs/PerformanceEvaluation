import java.util.stream.IntStream;

public class ParallelStream {
    public static void main(String[] args){
        int nb_steps = 100000;
        double sum;
        double steps = 1.0 / (double) nb_steps;

        sum = IntStream.rangeClosed(0, nb_steps).parallel().mapToDouble(ii -> (ii - 0.5) * steps).map(x -> 4.0 / (1.0 + x * x)).sum();

        sum*= steps;

        System.out.println("PI=" + sum);
    }
}
