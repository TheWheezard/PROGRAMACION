import java.text.*;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;

/**
 * La clase ClasePrincipalConcurrente crea una matriz cuadrada de la forma
 * [n][n] y otra de la forma [n], ambas de tipo entero, y realiza el producto
 * entre sí, separando las filas por grupos para resolverla en diferentes hilos
 * de forma concurrente.
 * 
 * Está probado con un tamaño máximo de n = 30000 añadiendo necesariamente el
 * flag -Xmx4G y con un tamaño máximo de n = 50000 con el flag -Xmx10G. Por sí
 * solo recomendamos no superar n = 10000.
 * 
 * @author Javier López Sierra
 * @see matVectorConcurrente
 */
public class ClasePrincipalConcurrente {
    static int[][] matrizCuadrada;
    static int[] matrizB;

    public static void main(String[] args) {
        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca tamaño de las matrices:");
        int n = scan.nextInt();
        System.out.println("Introduzca en cuántas partes se dividirá el proceso:");
        int numHilos = scan.nextInt();
        matrizCuadrada = new int[n][n];
        matrizB = new int[n];
        int[] matRes = new int[n]; // matriz resultado

        // cronómetro 1 (proceso completo)
        Date d1 = new Date();
        DateFormat df1 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom1 = System.currentTimeMillis(); // se prepara el cronometro
        d1.setTime(inicCronom1); // se activa el cronometro

        // rellenamos las matrices con valores aleatorios menos res, que será
        // inicializada a 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrizCuadrada[i][j] = random.nextInt();
            }
            matrizB[i] = random.nextInt();
            matRes[i] = 0;
        }

        matVectorConcurrente[] matrices = new matVectorConcurrente[numHilos];
        Runnable[] tareas = new Runnable[numHilos];
        Thread[] hilos = new Thread[numHilos];
        int j = 0;
        for (int i = 0; i < tareas.length; i++) {
            tareas[i] = matrices[i] = new matVectorConcurrente(i, n * i / numHilos, j);
            j = n * i / numHilos;
        }

        // cronómetro 2 (cálculo)
        Date d2 = new Date();
        DateFormat df2 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom2 = System.currentTimeMillis(); // se prepara el cronometro
        d2.setTime(inicCronom2); // se activa el cronometro

        for (int i = 0; i < hilos.length; i++) {
            hilos[i] = new Thread(tareas[i]);
            hilos[i].start();
        }
        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // creación del resultado
        int iterRes = 0;
        for (int i = 0; i < matrices.length; i++) {
            for (int k = 0; k < matrices[i].matResParcial.length && iterRes + k < matRes.length; k++) {
                matRes[iterRes + k] = matrices[i].matResParcial[k];
            }
            iterRes += matrices[i].matResParcial.length;
        }
        
        // fin cronómetro 2
        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d2.setTime(finCronom);
        System.out.println("Cálculo finalizado a las " + df2.format(d2) + " tras " + (finCronom - inicCronom2) + " milisegundos");

        // fin cronómetro 1
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");

        scan.close();
        System.out.println("Fin.");
    }
}
