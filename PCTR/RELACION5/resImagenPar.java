import java.util.Random;
import java.util.concurrent.*;

/**
 * La clase resImagenPar realiza la función de resaltado de forma paralela
 * dividiendo el proceso en tareas mediante un ejecutor en función de la
 * ecuación de Subramanian considerando el Coeficiente de Bloqueo igual a cero.
 * 
 * @author Javier López Sierra
 * @see InnerResImagenPar
 */
public class resImagenPar {
    public static void main(String[] args) {
        int n = 30000;
        int[][] matriz = new int[n][n];
        Random ran = new Random();
        // Llenamos la matriz con valores aleatorios entre 0 y 255
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz.length; j++) {
                matriz[i][j] = ran.nextInt() % 255;
            }
        }

        int nPuntos = n;
        int nTareas = 20;//Runtime.getRuntime().availableProcessors();
        int tVentana = nPuntos / nTareas;
        int linf = 0;
        int lsup = tVentana;

        long inicTiempo = System.nanoTime(); // iniciar cuenta de tiempo

        ThreadPoolExecutor ept = new ThreadPoolExecutor(nTareas, nTareas, 0L, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
        ept.prestartAllCoreThreads();
        for (int i = 0; i < nTareas; i++) {
            ept.execute(new InnerResImagenPar(linf, lsup, matriz));
            linf = lsup + 1;
            lsup += tVentana;
        }
        ept.shutdown();
        boolean procesos;
        try {
            procesos = ept.awaitTermination(200, TimeUnit.SECONDS);
            while (!procesos) {
                procesos = ept.awaitTermination(200, TimeUnit.SECONDS);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        double tiempoTotal = (double) (System.nanoTime() - inicTiempo) / (long) 1.0e9;
        System.out.println("Tiempo: " + tiempoTotal);
    }
}

/**
 * InnerResImagenPar es una clase que implementa la interfaz Runnable para hacer
 * cálculos paralelos sobre una matriz cuadrada.
 * 
 * @author Javier López Sierra
 * @see Runnable
 */
class InnerResImagenPar implements Runnable {
    private int inicio, fin, n = 30000;
    private int[][] matriz;

    /**
     * Constructor para clase InnerResImagenPar.
     * 
     * @param inicio entero que indica por dónde va a comenzar a hacerse el cálculo
     *               para la hebra.
     * @param fin    entero que indica el final del cálculo para la hebra.
     * @param matriz matriz de enteros sobre la que haremos los cálculos.
     */
    public InnerResImagenPar(int inicio, int fin, int[][] matriz) {
        this.inicio = inicio;
        this.fin = fin;
        this.matriz = matriz;
    }

    /**
     * Función que realiza el cálculo de la ecuación de resaltado de forma paralela.
     */
    public void calcular() {
        for (int i = inicio; i < fin; i++) { // debe hacer los mismos cálculos que la versión
            for (int j = 0; j < n; j++) { // secuencial, pero dentro del rango exigido
                matriz[i][j] = 4 * matriz[i][j];

                if (i + 1 < fin) {
                    matriz[i][j] = matriz[i][j] - matriz[i + 1][j];
                }
                if (i - 1 >= n) {
                    matriz[i][j] = matriz[i][j] - matriz[i - 1][j];
                }

                if (j + 1 < matriz[i].length) {
                    matriz[i][j] = matriz[i][j] - matriz[i][j + 1];
                }
                if (j - 1 >= 0) {
                    matriz[i][j] = matriz[i][j] - matriz[i][j - 1];
                }

                matriz[i][j] = matriz[i][j] / 8;
            }
        }
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable.
     * 
     * @see Runnable#run()
     */
    public void run() {
        calcular();
    }

}