import java.text.*;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;

/**
 * La clase <b>matVector</b> realiza el producto de una matriz cuadrada [n][n] por otra
 * matriz [n], ambas de valores enteros.
 * 
 * Está probado con un tamaño máximo de n = 30000 añadiendo necesariamente el
 * flag -Xmx4G y con un tamaño máximo de n = 50000 con el flag -Xmx10G. Por sí
 * solo recomendamos no superar n = 10000.
 * 
 * @author Javier López Sierra
 */
public class matVector {
    static int[][] matrizCuadrada;
    static int[] matrizB;

    /**
     * <p>
     * La función <b>main</b> rellena una {@code matrizCuadrada[][]} y una
     * {@code matrizB[]} de tipo <b>double</b> con números
     * aleatorios, para ejecutar el producto con {@code matrizB[]}.
     * </p>
     * <p>
     * Toda la operación de producto será controlada por un cronómetro. Se devuelve
     * por pantalla el resultado, así como fecha, hora y tiempo que se ha tardado en
     * completar la operación.
     * </p>
     * 
     * @param args No se emplea
     */
    public static void main(String[] args) {

        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca tamano de las matrices:");
        int n = scan.nextInt();

        // cronómetro 1 (proceso completo)
        Date d1 = new Date();
        DateFormat df1 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom1 = System.currentTimeMillis(); // se prepara el cronometro
        d1.setTime(inicCronom1); // se activa el cronometro

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

        // cronómetro 2 (cálculo)
        Date d2 = new Date();
        DateFormat df2 = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom2 = System.currentTimeMillis(); // se prepara el cronometro
        d2.setTime(inicCronom2); // se activa el cronometro

        for (int i = 0; i < n; i++) { // se hace el producto secuencial
            for (int j = 0; j < n; j++) {
                matRes[i] += matrizCuadrada[i][j] * matrizB[j];
            }
        }

        // fin cronómetro 2
        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d2.setTime(finCronom);
        System.out.println("Calculo finalizado a las " + df2.format(d2) + " tras " + (finCronom - inicCronom2) + " milisegundos");

        // fin cronómetro 1
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");

        System.out.println("Fin.");
        scan.close();
    }
}
