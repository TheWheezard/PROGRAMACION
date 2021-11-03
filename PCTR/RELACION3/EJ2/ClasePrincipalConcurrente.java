import java.util.Random;
import java.util.Scanner;

/**
 * La clase ClasePrincipalConcurrente crea una matriz cuadrada de la forma
 * [n][n] y otra de la forma [n], ambas de tipo entero, y realiza el producto
 * entre sí, separando las filas por grupos para resolverla en diferentes hilos
 * de forma concurrente.
 * 
 * Está probado con un tamaño máximo de n = 30000 añadiendo necesariamente los
 * flags -Xmx4G -ea
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
        matrizCuadrada = new int[n][n];
        matrizB = new int[n];
        int[] matRes = new int[n]; // matriz resultado

        // rellenamos las matrices con valores aleatorios menos res, que será
        // inicializada a 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrizCuadrada[i][j] = random.nextInt();
            }
            matrizB[i] = random.nextInt();
            matRes[i] = 0;
        }

        System.out.println("Introduzca en cuántas partes se dividirá el proceso:");
        int numHilos = scan.nextInt();
        matVectorConcurrente[] matrices = new matVectorConcurrente[numHilos];
        Runnable[] tareas = new Runnable[numHilos];
        Thread[] hilos = new Thread[numHilos];
        int j = 0;
        for (int i = 0; i < tareas.length; i++) {
            tareas[i] = matrices[i] = new matVectorConcurrente(i, n * i / numHilos, j);
            j = n * i / numHilos;
        }

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

        int iterRes = 0;
        for (int i = 0; i < matrices.length; i++) {
            for (int k = 0; k < matrices[i].matResParcial.length && iterRes + k < matRes.length; k++) {
                matRes[iterRes + k] = matrices[i].matResParcial[k];
            }
            iterRes += matrices[i].matResParcial.length;
        }
        scan.close();
        System.out.println("Fin.");
    }
}
