class Calka_runnable implements Runnable {

    private double dx;
    private double xp;
    private int N;

    private double result;

    public Calka_runnable(double xp, double xk, double dx) {

	    this.xp = xp;
        this.N = (int) Math.ceil((xk-xp) / dx);
        this.dx = (xk-xp)/N;

        this.result = 0;

    }

    private double getFunction(double x) {
        return Math.sin(x);
    }

    public void run() {

        double calka = 0;

        for(int i = 0; i < N; i++){

            double x1 = xp + i * dx;
            double x2 = x1 + dx;
            calka += ( (getFunction(x1) + getFunction(x2) ) / 2.) * dx;

        }

        result = calka;
    }

    public double getResult() {
        return result;
    }
}
