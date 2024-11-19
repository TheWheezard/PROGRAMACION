
/**
 * Algoritmo de Panadería de Lamport
 * 
 * El Algoritmo de Panadería de Lamport es un algoritmo de exclusión mutua que permite a múltiples hilos
 * entrar en sus secciones críticas sin conflictos. El algoritmo se basa en el concepto de
 * tomar un número antes de entrar en la sección crítica.
 * 
 * Para este ejercicio se ha hecho uso de IA.
 * 
 * @author Javier López Sierra
 */
public class Lamport implements Runnable{
    private int N; // number of threads
    private volatile boolean[] choosing;
    private volatile int[] number;

    public Lamport(int numThreads) {
        this.N = numThreads;
        choosing = new boolean[N];
        number = new int[N];
        for (int i = 0; i < N; i++) {
            choosing[i] = false;
            number[i] = 0;
        }
    }

    /**
     * Su propósito es asignar un número a un hilo antes de que pueda entrar en su sección crítica.
     * 
     * @param id Identificador del hilo
     */
    public void lock(int id) {
        choosing[id] = true;
        number[id] = 1 + max(number);
        choosing[id] = false;

        for (int j = 0; j < N; j++) {
            while (choosing[j]) {
                // Wait until thread j receives its number
            }
            while (number[j] != 0 && (number[j] < number[id] || (number[j] == number[id] && j < id))) {
                // Wait until all threads with smaller numbers or with the same number, but with
                // higher priority, finish their work
            }
        }
    }

    /**
     * Su propósito es liberar el número asignado a un hilo después de que haya terminado de ejecutar su sección crítica.
     * 
     * @param id Identificador del hilo
     */
    public void unlock(int id) {
        number[id] = 0;
    }

    /**
     * Devuelve el número máximo en un array de enteros.
     * 
     * @param array Array de enteros
     * @return Número máximo
     */
    private int max(int[] array) {
        int max = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }
        return max;
    }

    @Override
    public void run() {
        for (int i = 0; i < 100000; i++) {
            int id = Integer.parseInt(Thread.currentThread().getName());
            lock(id);
            System.out.println("Thread " + id + " is in critical section");
            unlock(id);
        }
    }

    public static void main(String[] args) {
        int numThreads = 5;
        Lamport lamport = new Lamport(numThreads);
        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            threads[i] = new Thread(lamport, Integer.toString(i));
            threads[i].start();
        }
        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
