import java.util.Scanner;


class Histogram_test {

	private static void printSection(String sectionName) {
		System.out.println("\n// ==================== " + sectionName + " ==================== //\n");
	}

	private static void joinAllThreads(Thread[] threads, int p) {
		for (int i = 0; i < p; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {}
		}
	}

	private static void saveHistogram(Watek2D[] watek, Obraz obraz, int p) {
		for (int i = 0; i < p; i++) {
			int[] histograms = watek[i].get_histogram();
			obraz.combine_histograms(histograms);
		}
	}

    public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);

		System.out.println("Set image size: n (#rows), m(#kolumns)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();
		Obraz obraz_1 = new Obraz(n, m);

		printSection("Histogram sekwencyjny");
		obraz_1.calculate_histogram();
		obraz_1.print_histogram();

		// ============================================================================
		// Wariant 1: Histogram równoległy - wersja uproszczona
		// ============================================================================

		/*

		printSection("Wariant 1: Histogram równoległy - wersja uproszczona");

		Watek[] NewThr = new Watek[94];
		char[] znak = new char[94];
		for (int i=0; i<94; i++){
			znak[i] = (char) (33 + i);
			(NewThr[i] = new Watek(znak[i], i, obraz_1)).start();
		}

		joinAllThreads(NewThr, 94);

		obraz_1.compare_histograms();

		 */

		// ============================================================================
		// Wariant 2: Histogram równoległy - wersja z podziałem na wątki
		// ============================================================================

		/*

		printSection("Histogram równoległy - Wariant 2");

		System.out.println("Wariant 2: Histogram równoległy - wersja z podziałem na wątki");

		System.out.println("Podaj liczbę wątków");
		int l_w = scanner.nextInt();

		Thread[] NewThr = new Thread[l_w];
		int N = 94;
		int el_na_watek = (int) Math.ceil((float) N / l_w);

		for (int i = 0; i < l_w; i++) {
			int start = i * el_na_watek;
			int end = el_na_watek * (i + 1);
			if (end > N) end = N;
			NewThr[i] = new Thread(new WatekRunnable(start, end, i, obraz_1));
			NewThr[i].start();
		}

		joinAllThreads(NewThr, l_w);

		obraz_1.compare_histograms();

		*/

		// ============================================================================
		// Wariant 3.1: Histogram równoległy - dekompozycja cykliczna wierszami
		// ============================================================================

		/*

		printSection("Wariant 3.1: Histogram równoległy - dekompozycja cykliczna wierszami");

		System.out.println("Podaj liczbę wątków");
		int l_w = scanner.nextInt();

		Watek2D[] RunThread = new Watek2D[l_w];
		Thread[] NewThr = new Thread[l_w];
		int N = n; // dekompozycja wierszami
		int wiersz_na_watek = (int) Math.ceil((float) N / l_w);

		for (int i = 0; i < l_w; i++) {

			// Dekompozycja cykliczna wierszowa
			int start = i;
			int end = N;
			int skok = l_w;
			if (end > N) end = N;

			RunThread[i] = new Watek2D(start, end, skok, 0, m, 1, obraz_1);
			NewThr[i] = new Thread(RunThread[i]);
			NewThr[i].start();

		}
		joinAllThreads(NewThr, l_w);

		saveHistogram(RunThread, obraz_1, l_w);

		obraz_1.print_histogram_all();

		obraz_1.compare_histograms();

		*/

		// ============================================================================
		// Wariant 3.2: Histogram równoległy - dekompozycja blokowa kolumnami
		// ============================================================================

		/*

		printSection("Wariant 3.2: Histogram równoległy - dekompozycja blokowa kolumnami");

		System.out.println("Podaj liczbę wątków");
		int l_w = scanner.nextInt();

		Watek2D[] RunThread = new Watek2D[l_w];
		Thread[] NewThr = new Thread[l_w];
		int N = m; // dekompozycja kolumnami
		int kolumna_na_watek = (int) Math.ceil((float) N / l_w);

		for (int i = 0; i < l_w; i++) {

			// Dekompozycja blokowa kolumnami
			int start = i * kolumna_na_watek;
			int end = kolumna_na_watek * (i + 1);
			int skok = 1;
			if (end > N) end = N;

			RunThread[i] = new Watek2D(0, n, 1, start, end, skok, obraz_1);
			NewThr[i] = new Thread(RunThread[i]);
			NewThr[i].start();

		}
		for (int i = 0; i < l_w; i++) {
			try {
				NewThr[i].join();
			} catch (InterruptedException e) {}
		}

		joinAllThreads(NewThr, l_w);

		saveHistogram(RunThread, obraz_1, l_w);

		obraz_1.print_histogram_all();

		obraz_1.compare_histograms();

		 */

		// ============================================================================
		// Wariant 4.1: Histogram równoległy - dekompozycja blokowa 2D
		// ============================================================================

		/*

		printSection("Wariant 4.1: Histogram równoległy - dekompozycja blokowa 2D");

		System.out.println("Podaj liczbę wątków");
		int l_w = scanner.nextInt();

		int r_w = (int) Math.ceil(Math.sqrt((double) l_w * n / m));
		int c_w = (int) Math.ceil((double) l_w / r_w);

		int wiersz_na_watek = (int) Math.ceil((float) n / r_w);
		int kolumna_na_watek = (int) Math.ceil((float) m / c_w);

		Watek2D[] RunThread = new Watek2D[r_w * c_w];
		Thread[] NewThr = new Thread[r_w * c_w];

		int threadIndex = 0;
		for (int i = 0; i < r_w; i++) {
			for (int j = 0; j < c_w; j++) {

				// Dekompozycja blokowa 2D
				int rowStart = i * wiersz_na_watek;
				int rowEnd = wiersz_na_watek * (i + 1);
				int rowJump = 1;

				int colStart = j * kolumna_na_watek;
				int colEnd = kolumna_na_watek * (j + 1);
				int colJump = 1;

				if (rowEnd > n) rowEnd = n;
				if (colEnd > m) colEnd = m;

				RunThread[threadIndex] = new Watek2D(rowStart, rowEnd, rowJump, colStart, colEnd, colJump, obraz_1);
				NewThr[threadIndex] = new Thread(RunThread[threadIndex]);
				NewThr[threadIndex].start();
				threadIndex++;
			}

		}

		joinAllThreads(NewThr, l_w);

		saveHistogram(RunThread, obraz_1, l_w);

		obraz_1.print_histogram_all();

		obraz_1.compare_histograms();

		 */

		// ============================================================================
		// Wariant 4.2: Histogram równoległy - dekompozycja cykliczna 2D
		// ============================================================================

		printSection("Wariant 4.2: Histogram równoległy - dekompozycja cylkiczna 2D");

		System.out.println("Podaj liczbę wątków");
		int l_w = scanner.nextInt();

		int r_w = (int) Math.ceil(Math.sqrt((double) l_w * n / m));
		int c_w = (int) Math.ceil((double) l_w / r_w);

		Watek2D[] RunThread = new Watek2D[r_w * c_w];
		Thread[] NewThr = new Thread[r_w * c_w];

		int threadIndex = 0;
		for (int i = 0; i < r_w; i++) {
			for (int j = 0; j < c_w; j++) {

				// Dekompozycja cykliczna 2D
				int rowStart = i;
				int rowEnd = n;
				int rowJump = r_w;

				int colStart = j;
				int colEnd = m;
				int colJump = c_w;

				RunThread[threadIndex] = new Watek2D(rowStart, rowEnd, rowJump, colStart, colEnd, colJump, obraz_1);
				NewThr[threadIndex] = new Thread(RunThread[threadIndex]);
				NewThr[threadIndex].start();
				threadIndex++;
			}

		}

		joinAllThreads(NewThr, l_w);

		saveHistogram(RunThread, obraz_1, l_w);

		obraz_1.print_histogram_all();

		obraz_1.compare_histograms();

    }

}

