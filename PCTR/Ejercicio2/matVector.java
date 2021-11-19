import java.text.*;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;

/**
 * La clase matVector realiza el producto de una matriz cuadrada [n][n] por otra
 * matriz [n], ambas de valores enteros.
 * 
 * @author Javier López Sierra
 */
public class matVector {
    static int[][] matrizCuadradaA;
    static int[][] matrizCuadradaB;

    public static void main(String[] args) {

        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca tamaño de las matrices:");
        int n = scan.nextInt();

        // cronómetro 1 (proceso completo)
        Date d1 = new Date();
        DateFormat df1 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom1 = System.currentTimeMillis(); // se prepara el cronometro
        d1.setTime(inicCronom1); // se activa el cronometro

        matrizCuadradaA = new int[n][n];
        matrizCuadradaB = new int[n][n];
        int[][] matRes = new int[n][n]; // matriz resultado
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrizCuadradaA[i][j] = matrizCuadradaB[i][j] = random.nextInt();
                matRes[i][j] = 0;
            }
        }

        // cronómetro 2 (cálculo)
        Date d2 = new Date();
        DateFormat df2 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom2 = System.currentTimeMillis(); // se prepara el cronometro
        d2.setTime(inicCronom2); // se activa el cronometro

        for (int i = 0; i < matrizCuadradaA.length; i++) { // se hace el producto secuencial
            for (int j = 0; j < matRes[0].length; j++) {
                for (int k = 0; k < matrizCuadradaB.length; k++) {
                    matRes[i][j] += matrizCuadradaA[i][k] * matrizCuadradaB[k][j];
                }
            }
        }

        // fin cronómetro 2
        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d2.setTime(finCronom);
        System.out.println("Cálculo finalizado a las " + df2.format(d2) + " tras " + (finCronom - inicCronom2) + " milisegundos");

        // fin cronómetro 1
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");

        System.out.println("Fin.");
        scan.close();
    }
}
