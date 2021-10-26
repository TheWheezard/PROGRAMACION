/**
 * tareaLambda
 */
public class tareaLambda {
    static int n = 0;

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Valor inicial de n: " + n);
        Runnable run1 = () -> {
            for (int i = 0; i < 10000000; i++) {
                n++;
            }
        };
        Runnable run2 = () -> {
            for (int i = 0; i < 10000000; i++) {
                n--;
            }
        };

        Thread hilo1 = new Thread(run1);
        Thread hilo2 = new Thread(run2);
        hilo1.start();
        hilo2.start();
        hilo1.join();
        hilo2.join();

        System.out.println("Resultado de n: " + n);
    }
}