public class Preprocessing {
    private int arraySize;
    private int parallelism;
    private long startTime;
    private long endTime;

    public Preprocessing(String[] args) {
        if (args.length != 2) {
            throw new RuntimeException("Usage: <array size> <parallelism factor>");
        }

        arraySize = Integer.parseInt(args[0]);
        parallelism = Integer.parseInt(args[1]);
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

    public int getArraySize() {
        return arraySize;
    }

    public int getParallelism() {
        return parallelism;
    }
}
