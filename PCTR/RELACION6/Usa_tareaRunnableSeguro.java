import java.util.Scanner;

/**
 * Clase que actúa mediante el uso de la clase tareaRunnable. Permite indicar
 * cuántas iteraciones queremos que dé el bucle que los objetos hebra que se
 * generarán.
 * 
 * @author Javier López Sierra
 * @see tareaRunnableSeguro
 */
public class Usa_tareaRunnableSeguro {
    public static void main(String[] args) throws InterruptedException {
        Scanner scan = new Scanner(System.in);
        System.out.println("Ejercicio 2. Indique número de vueltas:");
        int numVueltas = scan.nextInt();
        ClaseAux c = new ClaseAux();
        Runnable hSube = new tareaRunnableSeguro(numVueltas, 0, c); // creamos runnable que sube el valor de c.n
        Runnable hBaja = new tareaRunnableSeguro(numVueltas, 1, c); // creamos runnable que baja el valor de c.n
        // iniciamos los hilos
        Thread A = new Thread(hSube);
        Thread B = new Thread(hBaja);
        A.start(); B.start();
        A.join(); B.join();

        System.out.println(c.getN()); // imprimimos por pantalla el resultado final de n
        scan.close();
    }
}
