public class TestBariera {
    public static void main(String[] args) {
        Bariera bariera = new Bariera(3);

        Runnable zadanie = () -> {
            try {
                System.out.println(Thread.currentThread().getName() + " przed barierą");
                bariera.czekaj();
                System.out.println(Thread.currentThread().getName() + " za barierą");
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        };

        for (int i = 0; i < 6; i++) {
            new Thread(zadanie, "Wątek-" + i).start();
        }
    }
}
