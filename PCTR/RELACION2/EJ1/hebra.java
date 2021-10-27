/**
 * Clase que, mediante extensión de la clase Thread, genera hebras que hacen
 * aumentar o disminuir el valor de una variable interna un número determinado
 * de veces.
 * 
 * @author Javier López Sierra
 * 
 * @see Java.lang.Thread
 */

public class hebra extends Thread {
    /* Variables internas */
    private int vueltas;
    private int subeBaja;
    private static int n = 0; // variable sobre la que observaremos el cambio de valores.

    /**
     * Constructor de hebra.
     * 
     * @param vueltas  Este parámetro indica la cantidad total de vueltas que hará
     *                 el bucle.
     * @param subeBaja Este parámetro indica si la hebra hará aumentar (0) o
     *                 disminuir (1) el valor de 'n'.
     */
    public hebra(int vueltas, int subeBaja) {
        this.vueltas = vueltas;
        this.subeBaja = subeBaja;
    }

    /**
     * Método observador que devuelve el valor de una variable compartida por los
     * objetos hebra.
     * 
     * @return valor de la variable común a las hebras generadas.
     */
    public static int getN() {
        return n;
    }

    /**
     * Sobrecarga del método run() de la clase Thread. Aumentará o disminuirá en 1
     * el valor de la variable n según indique subeBaja, tantas veces como indique
     * 'vueltas'
     * 
     * @see Java.lang.Thread.run()
     */
    public void run() {
        switch (subeBaja) {
        case 0:
            for (int i = 0; i < vueltas; i++) {
                n += 1;
            }
            break;
        case 1:
            for (int i = 0; i < vueltas; i++) {
                n -= 1;
            }
            break;
        }
    }
}