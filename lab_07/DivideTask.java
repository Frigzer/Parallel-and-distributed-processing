import java.util.concurrent.RecursiveTask;

class DivideTask extends RecursiveTask<int[]> {

    int[] arrayToDivide;

    public DivideTask(int[] arrayToDivide) {
        this.arrayToDivide = arrayToDivide;
    }

    protected int[] compute() {

        if (arrayToDivide.length <= 1) {
            return arrayToDivide;
        }

        int mid = arrayToDivide.length / 2;

        int[] leftArray = new int[mid];
        int[] rightArray = new int[arrayToDivide.length - mid];

        System.arraycopy(arrayToDivide, 0, leftArray, 0, mid);
        System.arraycopy(arrayToDivide, mid, rightArray, 0, rightArray.length);

        DivideTask task1 = new DivideTask(leftArray);
        DivideTask task2 = new DivideTask(rightArray);

        task1.fork();
        int[] tab2 = task2.compute();
        int[] tab1 = task1.join();

        int[] result = new int[arrayToDivide.length];

        scal_tab(tab1, tab2, result);

        return result;

    }

    private void scal_tab(
            int[] tab1,
            int[] tab2,
            int[] scal_tab) {

        int i = 0, j = 0, k = 0;

        while ((i < tab1.length) && (j < tab2.length)) {

            if (tab1[i] < tab2[j]) {
                scal_tab[k] = tab1[i++];
            } else {
                scal_tab[k] = tab2[j++];
            }

            k++;
        }

        if (i == tab1.length) {

            for (int a = j; a < tab2.length; a++) {
                scal_tab[k++] = tab2[a];
            }

        } else {

            for (int a = i; a < tab1.length; a++) {
                scal_tab[k++] = tab1[a];
            }

        }
    }

}
