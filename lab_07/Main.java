import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Future;
import java.util.concurrent.ForkJoinPool;

public class Main {

    private static final int NTHREADS = 10;

    public static void main(String[] args) {

        // --------- Całka sekwencyjna --------- //
        System.out.println("\n--------- Całka sekwencyjna ---------\n");

        double xp = 0.0;
        double xk = Math.PI;
        double dx = 0.001;

        Calka_callable calka_sekw = new Calka_callable(xp, xk, dx);
        calka_sekw.compute_integral();

        // --------- Całka równoległa - wersja callable --------- //
        System.out.println("\n--------- Całka równoległa - wersja callable ---------\n");

        xp = 0.0;
        xk = Math.PI;
        dx = 0.001;

        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

        List<Future<Double>> futures = new ArrayList<>();

        double range = (xk - xp) / NTHREADS;

        for (int i = 0; i < NTHREADS; i++) {

            double xp_loc = xp + i * range;
            double xk_loc = xp_loc + range;

            Calka_callable calka_rown = new Calka_callable(xp_loc, xk_loc, dx);
            futures.add(executor.submit(calka_rown));
        }

        executor.shutdown();
        double totalIntegral = 0;
        for (Future<Double> future : futures) {
                try {
                        totalIntegral += future.get();
                } catch (Exception e) {
                        e.printStackTrace();
                }
        }

        System.out.println("\nWynik całki: " + totalIntegral);

        // --------- Sortowanie przez scalanie --------- //
        System.out.println("\n--------- Sortowanie przez scalanie ---------\n");

        int[] array = {38, 27, 43, 3, 9, 82, 10};
        System.out.println("Przed sortowaniem:");

        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        ForkJoinPool pool = new ForkJoinPool();

        DivideTask mainTask = new DivideTask(array);

        int[] sortedArray = pool.invoke(mainTask);

        System.out.println("Po sortowaniu:");
        for (int num : sortedArray) {
            System.out.print(num + " ");
        }

        System.out.println();

        // --------- Całka równoległa - wersja runnable --------- //
        System.out.println("\n--------- Całka równoległa - wersja runnable ---------\n");

        xp = 0.0;
        xk = Math.PI;
        dx = 0.001;

        ExecutorService executor2 = Executors.newFixedThreadPool(NTHREADS);

        Calka_runnable[] calkaRunnable = new Calka_runnable[NTHREADS];

        double range2 = (xk - xp) / NTHREADS;
        for (int i = 0; i < NTHREADS; i++) {
            double xp_loc = xp + i * range2;
            double xk_loc = xp_loc + range2;
            calkaRunnable[i] = new Calka_runnable(xp_loc, xk_loc, dx);

            executor2.execute(calkaRunnable[i]);
        }

        executor2.shutdown();
        while(!executor2.isTerminated()) {}

        double totalIntegral2 = 0.0;
        for (int i = 0; i < NTHREADS; i++)
        {
            totalIntegral2 += calkaRunnable[i].getResult();
        }

        System.out.println("Wynik całki: " + totalIntegral2);
    }
}
