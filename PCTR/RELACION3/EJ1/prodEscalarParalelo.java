/**
 * La clase prodEscalarParalelo crea un hilo con un vector auxiliar donde
 * efectuará el producto escalar entre los elementos comprendidos entre dos
 * posiciones dadas de dos vectores principales.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Thread
 */
public class prodEscalarParalelo extends Thread {
    double res;
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
    }

    /**
     * Método observador que devuelve el identificador de la hebra/vector
     * resultante.
     * 
     * @return Valor de tipo Int que identifica la hebra/vector resultante.
     */
    public int getIdHebra() {
        return idHebra;
    }

    /**
     * Método observador que devuelve el valor de la variable resultante del
     * producto escalar sobre el rango indicado anteriormente.
     * 
     * @return Valor de tipo double del resultado del producto escalar parcial.
     */
    public double getRes() {
        return res;
    }

    /**
     * Método que toma un rango del vector comprendido entre las posiciones inicio y
     * fin de dos vectores de la clase ClasePrincipalEscalar en la forma
     * [inicio,fin) y los multiplica entre sí, guardando el resultado en una
     * variable auxiliar.
     * 
     * @see ClasePrincipalEscalar
     */
    public void calcular() {
        res = 0;
        for (int i = inicio; i < fin; i++) {
            res = res + ClasePrincipalEscalar.vec1[i] * ClasePrincipalEscalar.vec2[i];
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