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
public class tareaRunnable implements Runnable {
    /* Variables internas */
    private int vueltas;
    private int subeBaja;
    ClaseAux clase; // variable de tipo ClaseAux sobre la que observaremos el cambio de valores.

    /**
     * Constructor de tareaRunnable.
     * 
     * @param vueltas  : (<b>int</b>) Este parámetro indica la cantidad total de vueltas que hará
     *                 el bucle.
     * @param subeBaja : (<b>int</b>) Este parámetro indica si la hebra hará aumentar (0) o
     *                 disminuir (1) el valor de {@code n}.
     * @param clase    : (<b>ClaseAux</b>) Este parámetro contiene la clase sobre la que se va a probar
     *                 la condición de concurso.
     */
    public tareaRunnable(int vueltas, int subeBaja, ClaseAux clase) {
        this.vueltas = vueltas;
        this.subeBaja = subeBaja;
        this.clase = clase;
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable. Aumentará o disminuirá
     * en 1 el valor de la variable {@code n} de {@code clase} según indique {@code subeBaja} , tantas
     * veces como indique {@code vueltas}.
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