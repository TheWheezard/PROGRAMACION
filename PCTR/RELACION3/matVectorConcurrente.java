/**
 * La clase matVectorConcurrente recibe un conjunto de filas de una matriz
 * cuadrada[n][n] y la posición de la fila inicial y realiza el producto con
 * otra matriz[n], guardando el resultado parcial en un array. Ambas matrices
 * están rellenas de valores enteros aleatorios.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Runnable
 */
public class matVectorConcurrente implements Runnable {
    int idHilo;
    int filas; // filas de la matriz cuadrada
    int inicio; // fila inicial de la matriz cuadrada
    static int n = 500;
    int[] matResParcial;

    /**
     * Constructor para la clase matVectorConcurrente.
     * 
     * @param idHilo Parámetro que identifica el objeto.
     * @param filas  Parámetro que indica el número de filas de la matriz cuadrada
     *               asignados para su cálculo.
     * @param inicio Parámetro que indica la fila de la matriz cuadrada desde la que
     *               se empieza el cálculo.
     */
    public matVectorConcurrente(int idHilo, int filas, int inicio) {
        this.idHilo = idHilo;
        this.filas = filas;
        this.inicio = inicio;
        matResParcial = new int[filas]; // las n * x/total_partes filas que le tocan

    }

    /**
     * Método modificador que realiza el producto escalar de un grupo de filas de
     * una matriz cuadrada[n][n] con una matriz[n] de la clase
     * ClasePrincipalVector.
     * 
     * @see ClasePrincipalVector
     */
    public void calcular() {
        for (int i = 0; i < matResParcial.length && inicio < n; i++) {
            int res = 0;
            for (int j = 0; j < ClasePrincipalVector.matrizB.length; j++) {
                res = res + ClasePrincipalVector.matrizCuadrada[inicio + i][j] * ClasePrincipalVector.matrizB[j];
            }
            matResParcial[i] = res;
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
