import java.text.*;
import java.util.Date;
import java.util.Random;

/**
 * La clase prodMatricesSecuencial realiza el producto de una matriz cuadrada [n][n] por otra
 * matriz [n], ambas de valores enteros.
 * 
 * @author Javier López Sierra
 */
public class prodMatricesSecuencial {
    static int[][] matrizCuadrada;
    static int[] matrizB;
    static int[] matRes;
    public static void main(String[] args) {

        Random random = new Random();
        System.out.println("Tamaño de m = 30000");
        int n = 30000;

        // cronómetro
        Date d1 = new Date();
        DateFormat df1 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom1 = System.currentTimeMillis(); // se prepara el cronometro
        d1.setTime(inicCronom1); // se activa el cronometro

        matrizCuadrada = new int[n][n];
        matrizB = new int[n];
        matRes = new int[n]; // matriz resultado
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

        // fin cronómetro 1
        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d1.setTime(finCronom);
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");
        System.out.println("Fin.");
    }
}
