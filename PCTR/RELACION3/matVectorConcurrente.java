import java.text.*;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;

/**
 * La clase matVectorConcurrente crea una matriz cuadrada de la forma
 * [n][n] y otra de la forma [n], ambas de tipo entero, y realiza el producto
 * entre sí, separando las filas por grupos para resolverla en diferentes hilos
 * de forma concurrente.
 * 
 * Está probado con un tamaño máximo de n = 30000 añadiendo necesariamente el
 * flag -Xmx4G y con un tamaño máximo de n = 50000 con el flag -Xmx10G. Por sí
 * solo recomendamos no superar n = 10000.
 * 
 * @author Javier López Sierra
 * @see MatVecConcurrente
 */
public class matVectorConcurrente {
    static int[][] matrizCuadrada;
    static int[] matrizB;

    /**
     * <p>
     * La función <b>main</b> rellena una {@code matrizCuadrada[][]} y una
     * {@code matrizB[]} de tipo <b>double</b> con números
     * aleatorios, para acto seguido dividir {@code matrizCuadrada} en tantas partes
     * como indique el usuario por teclado. Dichas partes se enviarán a hebras de
     * tipo <b>MatVecConcurrente</b>, que ejecutarán el producto con
     * {@code matrizB[]} al mismo tiempo.
     * </p>
     * <p>
     * Esta clase <b>main</b> recibirá los resultados y terminará la operación de
     * producto
     * realizando la suma de éstos. Toda la operación de producto será controlada
     * por un cronómetro. Se devuelve por pantalla el resultado, así como fecha,
     * hora y tiempo que se ha tardado en completar la operación.
     * </p>
     * 
     * @param args No se emplea
     */
    public static void main(String[] args) {
        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca tamano de las matrices:");
        int n = scan.nextInt();
        System.out.println("Introduzca en cuantas partes se dividira el proceso:");
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

        MatVecConcurrente[] matrices = new MatVecConcurrente[numHilos];
        Runnable[] tareas = new Runnable[numHilos];
        Thread[] hilos = new Thread[numHilos];
        int j = 0;
        for (int i = 0; i < tareas.length; i++) {
            tareas[i] = matrices[i] = new MatVecConcurrente(i, n * i / numHilos, j);
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
        System.out.println("Calculo finalizado a las " + df2.format(d2) + " tras " + (finCronom - inicCronom2) + " milisegundos");

        // fin cronómetro 1
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");

        scan.close();
        System.out.println("Fin.");
    }
}

/**
 * La clase MatVecConcurrente recibe un conjunto de filas de una matriz
 * cuadrada[n][n] y la posición de la fila inicial y realiza el producto con
 * otra matriz[n], guardando el resultado parcial en un array. Ambas matrices
 * están rellenas de valores enteros aleatorios.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Runnable
 */
class MatVecConcurrente implements Runnable {
    int idHilo;
    int filas; // filas de la matriz cuadrada
    int inicio; // fila inicial de la matriz cuadrada
    static int n = 500;
    int[] matResParcial;

    /**
     * Constructor para la clase matVectorConcurrente.
     * 
     * @param idHilo (<b>int</b>) Parámetro que identifica el objeto.
     * @param filas  (<b>int</b>) Parámetro que indica el número de filas de la matriz cuadrada
     *               asignados para su cálculo.
     * @param inicio (<b>int</b>) Parámetro que indica la fila de la matriz cuadrada desde la que
     *               se empieza el cálculo.
     */
    public MatVecConcurrente(int idHilo, int filas, int inicio) {
        this.idHilo = idHilo;
        this.filas = filas;
        this.inicio = inicio;
        matResParcial = new int[filas]; // las n * x/total_partes filas que le tocan

    }

    /**
     * Método modificador que realiza el producto escalar de un grupo de filas de
     * una matriz {@code cuadrada[n][n]} con una {@code matriz[n]} de la clase
     * matVectorConcurrente.
     * 
     * @see matVectorConcurrente
     */
    public void calcular() {
        for (int i = 0; i < matResParcial.length && inicio < n; i++) {
            int res = 0;
            for (int j = 0; j < matVectorConcurrente.matrizB.length; j++) {
                res = res + matVectorConcurrente.matrizCuadrada[inicio + i][j] * matVectorConcurrente.matrizB[j];
            }
            matResParcial[i] = res;
        }
    }

    /**
     * Sobrecarga del método {@code run()} de la interfaz Runnable.
     * 
     * @see Java.lang.Runnable.run
     */
    public void run() {
        this.calcular();
    }
}
