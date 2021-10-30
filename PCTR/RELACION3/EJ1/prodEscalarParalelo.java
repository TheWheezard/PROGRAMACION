/**
 * La clase prodEscalarParalelo crea un hilo con un vector auxiliar donde efectuará el
 * producto escalar entre los elementos comprendidos entre dos posiciones dadas
 * de dos vectores principales.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Thread
 */
public class prodEscalarParalelo extends Thread {
    //static double[] vec1 = new double[(int) Math.pow(10, 6)];
    //static double[] vec2 = new double[(int) Math.pow(10, 6)];
    static double[] vecAux;
    int idHebra, inicio, fin;

    /**
     * Constructor de la clase prodEscalarParalelo.
     * 
     * @param idHebra Parámetro de tipo Int que identificará el número de
     *                hebra/vector.
     * @param inicio  Parámetro de tipo Int que indicará la posición inicial del
     *                rango de posiciones en los vectores principales donde se hará
     *                el cálculo.
     * @param fin     Parámetro de tipo Int que indicará la posición final del rango
     *                de posiciones en los vectores principales donde se hará el
     *                cálculo.
     */
    public prodEscalarParalelo(int idHebra, int inicio, int fin) {
        this.idHebra = idHebra;
        this.inicio = inicio;
        this.fin = fin;
        vecAux = new double[fin - inicio];
    }

    /**
     * Método observador que devuelve el identificador de la hebra/vector
     * resultante.
     * 
     * @return Valor de tipo Int que identifica la hebre/vector resultante.
     */
    public int getIdHebra() {
        return idHebra;
    }

    /**
     * Método que devuelve el tamaño del vector que contiene el resultado.
     * 
     * @return valor del tamaño del vector resultado.
     */
    public int getTam() {
        return vecAux.length;
    }

    /**
     * Método observador que devuelve el valor de una posición del vector resultante
     * del producto escalar sobre el rango indicado anteriormente.
     * 
     * @param i Posición del vector resultante de la que queremos su valor.
     * @return Valor de tipo double de la posición i del vector resultante del
     *         producto escalar.
     */
    public double getRes(int i) {
        return vecAux[i];
    }

    /**
     * Método que toma un rango del vector comprendido entre las posiciones inicio y
     * fin de dos vectores de la clase ClasePrincipalParalelo en la forma [inicio,fin) y los multiplica entre sí,
     * guardando el resultado en un vector auxiliar.
     * @see ClasePrincipalParalelo
     */
    public void calcular() {
        int j = 0;
        for (int i = inicio; i < fin; i++) {
            vecAux[j] = ClasePrincipalParalelo.vec1[i] * ClasePrincipalParalelo.vec2[i];
            j++;
        }
    }

    /**
     * Sobrecarga del método run() de la clase Thread que llama al método calcular
     * de la clase prodEscalarParalelo.
     * 
     * @see Java.lang.Thread.run
     */
    public void run() {
        calcular();
    }
}
/* continuar desde escalaVPar y VectorPrueba */