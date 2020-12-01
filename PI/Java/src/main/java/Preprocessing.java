public class Preprocessing {
    private int nbIterations;
    private int nbThreads;
    private long startTime;
    private long endTime;

    public Preprocessing(String[] args) {
        if (args.length != 2) {
            throw new RuntimeException("Usage: <number of iterations> <number of threads>");
        }

        nbIterations = Integer.parseInt(args[1]);
        nbThreads = Integer.parseInt(args[1]);
    }

    public void timerStart() {
        startTime = System.nanoTime();
    }

    public void timerStop() {
        endTime = System.nanoTime();
    }

    public double timerDuration() {
        return (endTime - startTime) * 1.0e-9;
    }

    public int getNbIterations() {
        return nbIterations;
    }

    public int getNbThreads() {
        return nbThreads;
    }
}
