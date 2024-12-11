import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Czytelnia {
    private int liczbaCzytelnikow = 0; // Liczba aktywnych czytelników
    private int liczbaPisarzy = 0;     // Liczba aktywnych pisarzy
    private final Lock lock = new ReentrantLock();
    private final Condition czytelnicyCondition = lock.newCondition();
    private final Condition pisarzeCondition = lock.newCondition();

    public void chceCzytac() throws InterruptedException {
        lock.lock();
        try {
            while (liczbaPisarzy > 0) {
                czytelnicyCondition.await();
            }
            liczbaCzytelnikow++;
        } finally {
            lock.unlock();
        }
    }

    public void koniecCzytania() {
        lock.lock();
        try {
            liczbaCzytelnikow--;
            if (liczbaCzytelnikow == 0) {
                pisarzeCondition.signal();
            }
        } finally {
            lock.unlock();
        }
    }

    public void chcePisac() throws InterruptedException {
        lock.lock();
        try {
            while (liczbaCzytelnikow > 0 || liczbaPisarzy > 0) {
                pisarzeCondition.await();
            }
            liczbaPisarzy++;
        } finally {
            lock.unlock();
        }
    }

    public void koniecPisania() {
        lock.lock();
        try {
            liczbaPisarzy--;
            pisarzeCondition.signal();
            czytelnicyCondition.signalAll();
        } finally {
            lock.unlock();
        }
    }
}
