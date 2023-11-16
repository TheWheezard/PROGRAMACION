import java.util.Scanner;

/**
 * Clase que funciona mediante el uso de la clase hebra. Permite indicar cuántas
 * iteraciones queremos que dé el bucle que los objetos hebra que se generarán.
 * 
 * @author Javier López Sierra
 */
public class Usa_hebraSeguro {
    public static void main(String[] args) throws InterruptedException {
        Scanner scan = new Scanner(System.in);
        System.out.println("Ejercicio 1. Indique número de vueltas:");
        int numVueltas = scan.nextInt();
        hebraSeguro hSube = new hebraSeguro(numVueltas, 0); // sube el valor de res.
        hebraSeguro hBaja = new hebraSeguro(numVueltas, 1); // baja el valor de res.
        hSube.start(); // inicia hilo
        hBaja.start();
        hSube.join(); // termina hilo
        hBaja.join();
        System.out.println(hebraSeguro.getN()); // imprimimos por pantalla el resultado final de n
        scan.close();
    }
}
