/**
 * Clase que modela el funcionamiento de un monitor para el problema de
 * Productor-Consumidor. El recurso compartido consiste en un array de enteros
 * llamado <b>buffer</b>.
 * 
 * @author Javier López Sierra
 */
public class prodCon {
    private final int n = 100000; // tamaño del buffer
    private int buffer[] = new int[n];
    private volatile int antiguo = 0, nuevo = 0; // punteros de lectura y escritura en el buffer
    private volatile int contLecturas = 0; // Controla la cantidad de nuevas lecturas (para no eliminar contenido sin leer o leer contenido sin actualizar)

    /**
     * La función <b>leer()</b> permite a un consumidor solicitar turno para leer un
     * dato de la posición más antigua sin leer del buffer. Actualiza el contador de
     * lecturas pendientes y notifica al final del proceso de lectura. Controla que
     * se accede a dicho buffer solo si hay contenido por leer.
     * 
     * @return <b>int</b> : valor más antiguo sin leer almacenado en el buffer.
     */
    public synchronized int leer(){
        while (contLecturas == 0){ //comprobamos si hay productores activos o lecturas disponibles
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        int temp = buffer[antiguo];
        antiguo = (antiguo + 1) % n;
        contLecturas--;
        notifyAll();
        return temp;
    }
    
    /**
     * La función <b>escribir()</b> permite a un productor escribir en el buffer.
     * Solo podrá hacerlo en la posición ya leída que lleve más tiempo sin ser
     * actualizada.
     * 
     * @param valor : (<b>int</b>) Valor que se va a introducir en el buffer.
     */
    public synchronized void escribir(int valor){
        while (contLecturas == n){
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        buffer[nuevo] = valor;
        nuevo = (nuevo + 1) % n;
        contLecturas++;
        notifyAll();
    }
}
