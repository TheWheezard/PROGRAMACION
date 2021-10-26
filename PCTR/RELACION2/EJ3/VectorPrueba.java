import java.lang.Math;

/**
 * Esta clase crea un vector con 10^6 posiciones llenas de números aleatorios
 * que serán multiplicados por un mismo escalar.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Runnable
 */
public class VectorPrueba implements Runnable {
    static double[] vector = new double[(int) Math.pow(10, 6)];
    static private double escalar = 2;
    int inicio, fin = vector.length;

    /**
     * Constructor para la clase VectorPrueba.
     * 
     * @param inicio Parámetro que definirá la posición desde donde comenzará las
     *               multiplicaciones en 'cálculo'.
     * @param fin    Parámetro que indicará la posición donde terminará de
     *               realizarse la secuencia de multiplicaciones en 'cálculo'. Debe
     *               cumplirse fin > inicio para que sea un rango válido. En caso de
     *               no cumplirlo, su valor será el tamaño del vector
     *               (vector.length).
     */
    public VectorPrueba(int inicio, int fin) {
        this.inicio = inicio;
        if (fin > inicio) {
            this.fin = fin; // fin debe cumplir fin > inicio para que sea un rango
        } else {
            this.fin = vector.length; // en caso de no cumplirlo, su valor será el tamaño del vector
        }
        for (int i = 0; i < vector.length; i++) {
            vector[i] = Math.random();
        }
    }

    /**
     * Método que toma un rango del vector comprendido entre las posiciones inicio y
     * fin en la forma [inicio,fin) y los multiplica por un escalar.
     */
    public void calcular() {
        for (int i = inicio; i < fin; i++) {
            vector[i] = vector[i] * escalar;
        }
    }

    /**
     * Sobrecarga del método run() de la clase Thread que llama al método calcular.
     * 
     * @see Java.lang.Runnable.run
     */
    public void run() {
        calcular();
    }

}