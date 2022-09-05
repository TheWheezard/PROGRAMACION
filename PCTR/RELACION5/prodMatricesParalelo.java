import java.text.*;
import java.util.Date;
import java.util.Random;
import java.util.concurrent.*;

/**
 * La clase prodMatricesParalelo crea una matriz cuadrada de la forma
 * [n][n] y otra de la forma [n], ambas de tipo entero, y realiza el producto
 * entre sí, separando las filas por grupos para resolverla en diferentes hilos
 * de forma concurrente.
 * 
 * @author Javier López Sierra
 * @see ProdMatrices
 */
public class prodMatricesParalelo {
    static int[][] matrizCuadrada;
    static int[] matrizB;
    static int[] matRes;

    public static void main(String[] args) {
        Random random = new Random();
        System.out.println("Tamaño de m = 30000");
        int n = 30000;
        matrizCuadrada = new int[n][n];
        matrizB = new int[n];
        matRes = new int[n]; // matriz resultado

        // cronómetro
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

        // Nt=Nc/1-Cb == numHilos = Runtime.getRuntime().availableProcessors() / 1 - 0
        int numHilos = Runtime.getRuntime().availableProcessors();
        System.out.println("El proceso se dividirá en tantas tareas como indique la ecuación de Subramanian: " + numHilos);
        int nPuntos = n;
    	int nTareas = Runtime.getRuntime().availableProcessors();
    	int tVentana = nPuntos/nTareas;
    	int linf = 0;
    	int lsup = tVentana;

        ThreadPoolExecutor ept = new ThreadPoolExecutor(nTareas, nTareas, 0L, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
        ept.prestartAllCoreThreads();
        for (int i = 0; i < nTareas; i++) {
            ept.execute(new ProdMatrices(linf, lsup, matrizCuadrada, matrizB, matRes));
            linf = lsup +1;
            lsup += tVentana;
        }
        ept.shutdown();


        // fin cronómetro
        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d1.setTime(finCronom);
        System.out.println("Proceso finalizado a las " + df1.format(d1) + " tras " + (finCronom - inicCronom1) + " milisegundos");
        System.out.println("Fin.");
    }
}

/**
 * La clase ProdMatrices recibe un conjunto de filas de una matriz
 * cuadrada[n][n] y la posición de la fila inicial y realiza el producto con
 * otra matriz[n], guardando el resultado parcial en un array. Ambas matrices
 * están rellenas de valores enteros aleatorios.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Runnable
 */
class ProdMatrices implements Runnable {
    private int inicio; // fila inicial de la matriz cuadrada
    private int fin;
    int[][] matA;
    int[] matB;
    int[] matR;

    /**
     * Constructor para la clase ProdMatrices.
     * 
     * @param idHilo Parámetro que identifica el objeto.
     * @param filas  Parámetro que indica el número de filas de la matriz cuadrada
     *               asignados para su cálculo.
     * @param inicio Parámetro que indica la fila de la matriz cuadrada desde la que
     *               se empieza el cálculo.
     */
    public ProdMatrices(int inicio, int fin, int[][] mat1, int[] mat2, int[] mat3) {
        this.inicio = inicio;
        this.fin = fin;
        this.matA = mat1;
        this.matB = mat2;
        this.matR = mat3;
    }

    /**
     * Método modificador que realiza el producto escalar de un grupo de filas de
     * una matriz cuadrada[n][n] con una matriz[n] de la clase
     * prodMatricesParalelo.
     * 
     * @see prodMatricesParalelo
     */
    public void calcular() {
        for (int i = inicio; i < fin; i++) {
            int res = 0;
            for (int j = 0; j < matB.length; j++) {
                res = res + matA[i][j] * matB[j];
            }
            matR[i] = res;
        }
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable.
     * 
     * @see Java.lang.Runnable.run
     */
    public void run() {
        this.calcular();
    }
}
