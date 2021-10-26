import java.util.Scanner;

/**
 * Clase que actúa mediante el uso de la clase tareaRunnable. Permite indicar
 * cuántas iteraciones queremos que dé el bucle que los objetos hebra que se
 * generarán.
 * 
 * @author Javier López Sierra
 */
public class Usa_tareaRunnable {
    public static void main(String[] args) throws InterruptedException {
        Scanner scan = new Scanner(System.in);
        System.out.println("Ejercicio 2. Indique número de vueltas:");
        int numVueltas = scan.nextInt();
        ClaseAux c = new ClaseAux();
        Runnable hSube = new tareaRunnable(numVueltas, 0, c); // creamos runnable que sube el valor de c.n
        Runnable hBaja = new tareaRunnable(numVueltas, 1, c); // creamos runnable que baja el valor de c.n
        // iniciamos los hilos
        new Thread(hSube).start();
        new Thread(hBaja).start();

        System.out.println(c.getN()); // imprimimos por pantalla el resultado final de n
        scan.close();
    }
}
