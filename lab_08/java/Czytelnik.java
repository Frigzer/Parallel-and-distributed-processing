public class Czytelnik implements Runnable {
    private final Czytelnia czytelnia;

    public Czytelnik(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                Thread.sleep((int) (Math.random() * 1000));
                czytelnia.chceCzytac();
                System.out.println(Thread.currentThread().getName() + " czyta");
                Thread.sleep((int) (Math.random() * 1000));
                czytelnia.koniecCzytania();
                System.out.println(Thread.currentThread().getName() + " skończył czytać");
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
