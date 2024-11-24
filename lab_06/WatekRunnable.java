public class WatekRunnable implements Runnable{
    private final int start;
    private final int end;
    private final int IdWatek;
    private final Obraz obraz;

    public WatekRunnable(int start, int end, int IdWatek, Obraz obraz){

      this.start = start;
      this.end = end;
      this.IdWatek = IdWatek;
      this.obraz = obraz;

    }

    @Override
    public void run(){

        for (int i = start; i < end; i += 1)
        {
            char znak = (char) (i + 33);
            obraz.calculate_histogram_znak(znak);
            obraz.print_histogram_znak(znak, IdWatek);

        }
    }
}
