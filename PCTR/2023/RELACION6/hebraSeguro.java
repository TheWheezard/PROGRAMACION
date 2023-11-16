/**
 * Clase que, mediante extensión de la clase Thread, genera hebras que hacen
 * aumentar o disminuir el valor de una variable interna un número determinado
 * de veces.
 * 
 * @author Javier López Sierra
 * 
 * @see Java.lang.Thread
 */

public class hebraSeguro extends Thread {
    /* Variables internas */
    private int vueltas;
    private int subeBaja;
    private static int n = 0; // variable sobre la que observaremos el cambio de valores.
    public static Object lock = new Object () ; // cerrojo

    /**
     * Constructor de hebra.
     * 
     * @param vueltas  Este parámetro indica la cantidad total de vueltas que hará
     *                 el bucle.
     * @param subeBaja Este parámetro indica si la hebra hará aumentar (0) o
     *                 disminuir (1) el valor de 'n'.
     */
    public hebraSeguro(int vueltas, int subeBaja) {
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
     * La función sumaN() Aumentará o en 1 el valor de la variable n. Está protegido
     * mediante synchronized para evitar que se realicen modificaciones simultáneas
     * en la variable n.
     */
    public synchronized void sumaN() {
        n += 1;
    }

    /**
     * La función restaN() Aumentará o en 1 el valor de la variable n. Está protegido
     * mediante synchronized para evitar que se realicen modificaciones simultáneas
     * en la variable n.
     */
    public synchronized void restaN() {
        n -= 1;
    }

    /**
     * Sobrecarga del método run() de la clase Thread. Llamará al método setN() para
     * aumentar o disminuir en 1 el valor de n en función de subeBaja.
     * 
     * @see Thread#run()
     */
    public void run() {
        switch (subeBaja) {//comprobará siempre si puede acceder o no a la operación
            case 0:
                for (int i = 0; i < vueltas; i++) synchronized(lock) {
                    sumaN();
                }
                break;
            case 1:
                for (int i = 0; i < vueltas; i++) synchronized(lock) {
                    restaN();
                }
                break;
            }
    }
}