/**
 * La clase concursoLambda realiza dos operaciones concurrentes usando la interfaz
 * Runnable con funciones lambda.
 * 
 * @author Javier López Sierra
 */
public class concursoLambda {
    static int n = 0; // Variable estática que modificaremos

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Valor inicial de n: " + n);

        // Función lambda-1
        Runnable run1 = () -> {
            for (int i = 0; i < 10000000; i++) {
                n++;
            }
        };

        // Función lambda-2
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