/**
 * La clase deadlock crea tres hebras de tipo Object y las ejecuta de forma que se genere un interbloqueo.
 * @author Javier López Sierra
 */
public class deadlock {
    public static void main(String[] args) {
        final Object region_A = new Object();
        final Object region_B = new Object();
        final Object region_C = new Object();
        final int n = 0;

        Thread Hilo_C = new Thread(new Runnable() {
            public void run() {
                synchronized (region_C) {
                    for (int i = 0; i < 100000; i++);
                    synchronized (region_B) {
                        System.out.println(n);
                    }
                }
            }
        });

        Thread Hilo_B = new Thread(new Runnable() {
            public void run() {
                synchronized (region_B) {
                    for (int i = 0; i < 100000; i++);
                    synchronized (region_A) {
                        System.out.println(n);
                    }
                }
            }
        });

        Thread Hilo_A = new Thread(new Runnable() {
            public void run() {
                synchronized (region_A) {
                    for (int j = 0; j < 100000; j++);
                    synchronized (region_C) {
                        System.out.println(n);
                    }
                }
            }
        });
        
        Hilo_B.start();
        Hilo_A.start();
        Hilo_C.start();
    }
}