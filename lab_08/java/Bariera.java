public class Bariera {
    private final int liczbaWatkow;
    private int watkiNaBarierze = 0;

    public Bariera(int liczbaWatkow) {
        this.liczbaWatkow = liczbaWatkow;
    }

    public synchronized void czekaj() throws InterruptedException {
        watkiNaBarierze++;
        if (watkiNaBarierze == liczbaWatkow) {
            watkiNaBarierze = 0;
            notifyAll();
        } else {
            wait();
        }
    }
}
