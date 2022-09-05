/**
 * La clase heterogenea contiene dos variables de tipo long, cada cual con un
 * método setter que se encarga de sumarle 1 al valor actual de dicha variable.
 * El método setter para una de ellas es synchronized.
 * 
 * @author Javier López Sierra
 */
public class heterogenea {
    long n, m;

    /**
     * Constructor de la clase heterogenea. Inicializa los valores a 0.
     */
    public heterogenea() {
        n = m = 0;
    }

    /**
     * Método que realiza la suma: n = n + 1. Es synchronized.
     */
    public synchronized void sumN() {
        n++;
    }

    /**
     * Método que realiza la suma: m = m + 1. NO es synchronized.
     */
    public void sumM() {
        m++;
    }

    /**
     * Método que devuelve el valor de la variable n.
     * 
     * @return Elemento de tipo long (n).
     */
    public long getN() {
        return n;
    }

    /**
     * Método que devuelve el valor de la variable m.
     * 
     * @return Elemento de tipo long (m).
     */
    public long getM() {
        return m;
    }
}
