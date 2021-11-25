/** */
public class arrSeguro extends Thread{
    public static long iterations = 1000000;
    public ArraySeguro a;

    public arrSeguro(ArraySeguro a) {
      this.a = a;
    }

    public void run() {
        for (long i = 0; i < iterations; i++)
            a.inc();
    }

    public static void main(String[] args) throws Exception {
        ArraySeguro array = new ArraySeguro();
        arrSeguro A = new arrSeguro(array);
        arrSeguro B = new arrSeguro(array);
        A.start();
        B.start();
        A.join();
        B.join();
        long[] aux = array.get();
        for (long l : aux) {
            System.out.println(l);
        }
    }
}

/**
 * ArraySeguro
 */
class ArraySeguro {
    long[] n = new long[10];

    public ArraySeguro() {
        for (long l : n) {
            l = 0;
        }
    }
    public synchronized void inc() {
        for (int i = 0; i < n.length; i++) {
            n[i] += 1;
        }
    }
    public synchronized long[] get() {
        return n;
    }
}