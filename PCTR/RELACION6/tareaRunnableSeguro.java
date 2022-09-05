/**
 * Clase que, mediante implementación de la interfaz Runnable, genera hebras que
 * hacen aumentar o disminuir el valor de la variable de un objeto ClaseAux un
 * número determinado de veces.
 * 
 * @author Javier López Sierra
 * 
 * @see ClaseAux
 * @see Runnable
 */
public class tareaRunnableSeguro implements Runnable {
    /* Variables internas */
    private int vueltas;
    private int subeBaja;
    ClaseAux clase; // variable de tipo ClaseAux sobre la que observaremos el cambio de valores.

    /**
     * Constructor de tareaRunnable.
     * 
     * @param vueltas  Este parámetro indica la cantidad total de vueltas que hará
     *                 el bucle.
     * @param subeBaja Este parámetro indica si la hebra hará aumentar (0) o
     *                 disminuir (1) el valor de 'n'.
     * @param clase    Este parámetro contiene la clase sobre la que se va a probar
     *                 la condición de concurso.
     */
    public tareaRunnableSeguro(int vueltas, int subeBaja, ClaseAux clase) {
        this.vueltas = vueltas;
        this.subeBaja = subeBaja;
        this.clase = clase;
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable. Aumentará o disminuirá
     * en 1 el valor de la variable n de 'clase' según indique subeBaja, tantas
     * veces como indique 'vueltas'
     * 
     * @see Runnable#run()
     */
    public void run() {
        switch (subeBaja) {
        case 0:
            for (int i = 0; i < vueltas; i++) {
                clase.incrementar();
            }
            break;
        case 1:
            for (int i = 0; i < vueltas; i++) {
                clase.decrementar();
            }
            break;
        }
    }
}

/**
 * Clase que contiene una variable con valor inicial 0 cuyo valor puede ser
 * incrementado o decrementado.
 * 
 * @author Javier López Sierra
 */
class ClaseAux {
    private static int n = 0; // Variable que se irá modificando.
    
    /**
     * Constructor de la clase ClaseAux.
     */
    public ClaseAux() {
    }

    /**
     * Método modificador que aumenta en 1 el valor de n. Está protegido con synchronized
     */
    public synchronized void incrementar() {
        n++;
    }

    /**
     * Método modificador que disminuye en 1 el valor de n. Está protegido con synchronized
     */
    public synchronized void decrementar() {
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
