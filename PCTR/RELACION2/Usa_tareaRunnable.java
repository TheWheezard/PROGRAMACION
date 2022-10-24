import java.util.Scanner;

/**
 * Clase que actúa mediante el uso de la clase tareaRunnable. Permite indicar
 * cuántas iteraciones queremos que realice el bucle que los objetos hebra
 * tendrán que hacer.
 * 
 * @author Javier López Sierra
 * @see tareaRunnable
 */
public class Usa_tareaRunnable {
    public static void main(String[] args) throws InterruptedException {
        Scanner scan = new Scanner(System.in);
        System.out.println("Ejercicio 2. Indique numero de vueltas:");
        int numVueltas = scan.nextInt();
        ClaseAux c = new ClaseAux();
        Runnable hSube = new tareaRunnable(numVueltas, 0, c); // creamos runnable que sube el valor de c.n
        Runnable hBaja = new tareaRunnable(numVueltas, 1, c); // creamos runnable que baja el valor de c.n
        // iniciamos los hilos
        Thread t0 = new Thread(hSube);
        Thread t1 = new Thread(hBaja);

        t0.start();
        t1.start();
        t0.join();
        t1.join();

        System.out.println("c.n = " + c.getN()); // imprimimos por pantalla el resultado final de n
        scan.close();
    }
}

/**
 * Clase que contiene una variable con valor inicial 0 cuyo valor puede ser
 * incrementado o decrementado.
 * 
 * @author Javier López Sierra
 */
class ClaseAux {
    private static int n = 0; // Variable que se irá modificando.

    /**
     * Constructor de la clase ClaseAux.
     */
    public ClaseAux() {
    }

    /**
     * Método modificador que aumenta en 1 el valor de {@code n}.
     */
    public void incrementar() {
        n++;
    }

    /**
     * Método modificador que disminuye en 1 el valor de {@code n}.
     */
    public void decrementar() {
        n--;
    }

    /**
     * Método que devuelve el valor de la variable {@code n}.
     * 
     * @return (<b>int</b>) valor de n en el momento de ser llamada.
     */
    public int getN() {
        return (n);
    }
}
