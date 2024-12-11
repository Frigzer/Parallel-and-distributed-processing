public class TestCzytelnia {
    public static void main(String[] args) {
        Czytelnia czytelnia = new Czytelnia();

        // Tworzenie wątków dla czytelników
        for (int i = 0; i < 5; i++) {
            new Thread(new Czytelnik(czytelnia), "Czytelnik-" + i).start();
        }

        // Tworzenie wątków dla pisarzy
        for (int i = 0; i < 2; i++) {
            new Thread(new Pisarz(czytelnia), "Pisarz-" + i).start();
        }
    }
}
