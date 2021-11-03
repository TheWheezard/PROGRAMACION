import java.util.Random;
import java.util.Scanner;

/**
 * La clase matVector realiza el producto de una matriz cuadrada [n][n] por otra
 * matriz [n], ambas de valores enteros.
 * 
 * Está probado con un tamaño máximo de n = 30000 añadiendo necesariamente los
 * flags -Xmx4G -ea
 * 
 * @author Javier López Sierra
 */
public class matVector {
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
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrizCuadrada[i][j] = random.nextInt();
            }
            matrizB[i] = random.nextInt();
            matRes[i] = 0;
        }

        for (int i = 0; i < n; i++) { // se hace el producto secuencial
            for (int j = 0; j < n; j++) {
                matRes[i] += matrizCuadrada[i][j] * matrizB[j];
            }
        }

        System.out.println("Fin.");
        scan.close();
    }
}
