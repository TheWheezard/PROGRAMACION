/**
 * Clase que contiene una variable con valor inicial 0 cuyo valor puede ser
 * incrementado o decrementado.
 * 
 * @author Javier López Sierra
 */
public class ClaseAux {
    private static int n = 0; // Variable que se irá modificando.

    /**
     * Constructor de la clase ClaseAux.
     */
    public ClaseAux() {
    }

    /**
     * Método modificador que aumenta en 1 el valor de n.
     */
    public void incrementar() {
        n++;
    }

    /**
     * Método modificador que disminuye en 1 el valor de n.
     */
    public void decrementar() {
        n--;
    }

    /**
     * Método que devuelve el valor de la variable n.
     * 
     * @return valor de n en el momento de ser llamada.
     */
    public int getN() {
        return (n);
    }
}
