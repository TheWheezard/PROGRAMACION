/**
 * La clase Sem recrea el funcionamiento de un semáforo para controlar el
 * acceso de hilos a una Sección Crítica.
 * 
 * @author Javier López Sierra
 */
public class Sem {
    private int s;

    /**
     * Constructor para la clase semáforo, inicializa el valor.
     * 
     * @param s valor inicial de la variable señalizadora.
     */
    public Sem(int s) {
        this.s = s;
    }

    /**
     * Función synchronized que comprueba si debe hacer la espera o indica que
     * accede a la sección crítica.
     */
    public synchronized void waitS() {
        while (s == 0) { // mientras el semáforo esté cerrado
            try {
                wait(); // se quedará en espera
            } catch (InterruptedException e) {}
        }
        s -= 1; // notifica que está accediendo a la SC
    }

    /**
     * Función synchronized que indica a todos los hilos que esperan en el semáforo
     * que la SC queda libre.
     */
    public synchronized void signalS() {
        s += 1; // se señala en el semáforo
        notifyAll(); // se notifica a todos los hilos
    }
}
