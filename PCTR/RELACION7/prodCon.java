/**
 * Clase que modela el funcionamiento de un monitor para el problema de
 * Productor-Consumidor. El recurso compartido consiste en un array de enteros
 * llamado <b>buffer</b>.
 * 
 * @author Javier López Sierra
 */
public class prodCon {
    private final int n = 100; // tamaño del buffer
    private volatile int contLecturas = 0; // Controla la cantidad de lecturas realizadas (para no eliminar contenido sin leer o leer contenido sin actualizar)
    private volatile int antiguo = 0, nuevo = 0; // punteros de lectura y escritura en el buffer
    private int buffer[] = new int[n];
    private int consumidores = 0; // número de consumidores concurrentes
    private boolean escribiendo = false; // productor activo (true) o inactivo (false)

    public prodCon() {}

    /**
     * La función <b>solicitarLeer()</b> permite a un consumidor solicitar el acceso
     * al buffer para leer, incrementando el contador de consumidores.
     * Controla que se accede a dicho buffer solo si no se está escribiendo en él y
     * además hay contenido por leer.
     */
    public synchronized void solicitarLeer(){
        while (escribiendo || contLecturas == 0){ //comprobamos si hay productores activos o lecturas disponibles
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        ++consumidores; // incorporamos consumidor
        notifyAll();
    }

    /**
     * La función <b>leer()</b> permite a un consumidor tomar y extraer el valor más
     * antiguo del buffer. Actualiza el contador de lecturas disponibles.
     * 
     * @return <b>int</b> : valor más antiguo almacenado en el buffer.
     */
    public int leer(){
        int temp = buffer[antiguo];
        return temp;
    }

    /**
     * La función <b>finLeer()</b> decrementa el número de consumidores activos y,
     * si ese contador llega a 0, notifica a todos los hilos.
     */
    public synchronized void finLeer(){
        antiguo = (antiguo + 1) % n;
        contLecturas--;
        consumidores--;
        if (consumidores == 0){
            notifyAll();
        }
    }
    
    /**
     * La función <b>solicitarEscribir()</b> permite dar paso a un productor para
     * escribir en el buffer. Solo podrá hacerlo si no hay lectores o productores
     * accediendo al buffer.
     */
    public synchronized void solicitarEscribir(){
        while (consumidores > 0 && contLecturas == n){
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        escribiendo = true;
    }

    /**
     * La función <b>escribir()</b> permite a un productor escribir en el buffer en la
     * posición que lleve más tiempo sin haber sido reescrita.
     * 
     * @param valor : (<b>int</b>) Valor que se va a introducir en el buffer.
     */
    public void escribir(int valor){
        buffer[nuevo] = valor;
    }

    /**
     * La función <b>finEscribir()</b> pone a false la bandera de productores
     * escribiendo y notifica a todos los hilos.
     */
    public synchronized void finEscribir(){
        nuevo = (nuevo + 1) % n;
        contLecturas++;
        escribiendo = false;
        notifyAll();
    }
}
