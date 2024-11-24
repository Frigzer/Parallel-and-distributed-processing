public class Watek extends Thread {
    private final char znak;
    private final int IdWatek;
    private final Obraz obraz;
    
    public Watek(char znak, int IdWatek, Obraz obraz){
        this.znak = znak;
        this.IdWatek = IdWatek;
        this.obraz = obraz;
    }

    public void start() {
      obraz.calculate_histogram_znak(znak);
      obraz.print_histogram_znak(znak, IdWatek);
    }
}
