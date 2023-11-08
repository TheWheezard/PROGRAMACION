/**La clase <b>lectorEscritor</b> recrea el funcionamiento de un monitor para el paradigma de lectores y escritores.
 * @author Javier López Sierra
*/
public class lectorEscritor {
    private int nLectores; // nº lectores activos
    private boolean escribiendo; // T-> escritor activo; F-> escritores inactivos

    /**
     * Constructor de la clase <b>lectorEscritor</b>.
     */
    public lectorEscritor() {
        nLectores = 0;
        escribiendo = false;
    }

    /**
     * La función <b>iniciaLectura</b> comprueba si hay escritores activos, en caso
     * de no haberlos, incrementa en 1 el número de lectores activos.
     */
    public synchronized void iniciaLectura() {
        while (escribiendo){
            try { wait();} catch(InterruptedException e) {}
        }
        ++nLectores;
        notifyAll();
    }

    /**
     * La función <b>acabarLectura</b> decrementa en 1 el número de escritores
     * activos. Si llega a 0, notifica a todos los hilos.
     */
    public synchronized void acabarLectura() {
        nLectores--;
        if (nLectores == 0) {
            notifyAll();
        }
    }

    /**
     * La función <b>iniciaEscritura</b> comprueba si hay lectores o escritores
     * activos. En caso de no haberlos, activa el flag para indicar que un escritor
     * está activo.
     */
    public synchronized void iniciaEscritura() {
        while (nLectores != 0 || escribiendo) {
            try {wait();} catch (InterruptedException e) {}
        }
        escribiendo = true;
    }

    /**
     * La función <b>acabarEscritura</b> cambia el flag para indicar que ya no hay
     * escritor activo, y notifica a todos los hilos.
     */
    public synchronized void acabarEscritura() {
        escribiendo = false;
        notifyAll();
    }

}