public class Watek2D implements Runnable{

    private final int rowStart;
    private final int rowEnd;
    private final int rowJump;
    private final int colStart;
    private final int colEnd;
    private final int colJump;
    int[] hist_local;

    Obraz obraz;

    public Watek2D(int rowStart, int rowEnd, int rowJump, int colStart, int colEnd, int colJump, Obraz obraz) {

        this.rowStart = rowStart;
        this.rowEnd = rowEnd;
        this.rowJump = rowJump;
        this.colStart = colStart;
        this.colEnd = colEnd;
        this.colJump = colJump;
        this.obraz = obraz;
        this.hist_local = new int[94];
        for (int i = 0; i < 94; i++) {
            hist_local[i] = 0;
        }
    }

    @Override
    public void run() {
        obraz.calculate_histogram_universal(rowStart, rowEnd, rowJump, colStart, colEnd, colJump, hist_local);
    }

    public int[] get_histogram() {
        return hist_local;
    }
}
