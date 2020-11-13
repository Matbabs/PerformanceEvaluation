public class Sequential {

    public static void main(String[] args){
        int nb_steps = 100000;
        double sum = 0.0;
        double steps = 1.0 / (double) nb_steps;

        for (int ii = 0 ; ii <= nb_steps; ++ii){
            double x = (ii - 0.5) * steps;
            sum+=4.0 / (1.0 + x * x);
        }

        sum*= steps;

        System.out.println("PI=" + sum);
    }
}
