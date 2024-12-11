public class Pisarz implements Runnable {
    private final Czytelnia czytelnia;

    public Pisarz(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                Thread.sleep((int) (Math.random() * 2000));
                czytelnia.chcePisac();
                System.out.println(Thread.currentThread().getName() + " pisze");
                Thread.sleep((int) (Math.random() * 2000));
                czytelnia.koniecPisania();
                System.out.println(Thread.currentThread().getName() + " skończył pisać");
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
