/**
 * Clase que usa el monitor <b>lectorEscritor</b> para controlar el acceso
 * concurrente a un objeto de clase <b>recurso</b> de acuerdo al problema de
 * lectores y escritores.
 * 
 * @author Javier López Sierra
 */
public class usalectorEscritor implements Runnable{
    private int tipo; // tipo puede ser escritor->(0) o lector->(1)
    private lectorEscritor monitor;
    private recurso rec;

    /**
     * Constructor para la clase <b>usalectorEscritor</b>.
     * 
     * @param tipo    (<b>int</b>) : Indica el tipo de hebra. 0 para escritor; 1
     *                para lector.
     * @param monitor (<b>lectorEscritor</b>) : El tipo de monitor que empleamos
     *                para gestionar el control de acceso al recurso.
     * @param r       (<b>recurso</b>) : El recurso sobre el que tenemos que aplicar
     *                el control de acceso.
     */
    public usalectorEscritor(int tipo, lectorEscritor monitor, recurso r) {
        this.tipo = tipo;
        this.monitor = monitor;
        this.rec = r;
    }

    /**
     * Función que realiza el acceso controlado al recurso en función de si la hebra
     * es de lectura o de escritura. Se ha añadido una llamada a la función
     * Thread.sleep() con un milisegundo para conceder un retraso en la ejecución de
     * la siguiente vuelta que se realice. Esto permitirá observar debidamente el
     * funcionamiento del monitor (cómo crece la variable y es observada por los
     * lectores). Sin ello, los lectores pueden acaparar de forma permanente el
     * recurso e impedir al escritor acceder para actualizarlo hasta el final.
     */
    public void usaMonitor() {
        switch (tipo) {
            case 0:
                monitor.iniciaEscritura();
                rec.inc();
                monitor.acabarEscritura();
                break;
        
            case 1:
                monitor.iniciaLectura();
                System.out.println(rec.observer() + " por hebra: " + Thread.currentThread());
                monitor.acabarLectura();
                break;
            default:
                break;
        }
        // Esta llamada a sleep() permite observar más cómodamente el funcionamiento del monitor
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {}
    }

    /**
     * Sobrecarga de la función <b>run()</b> de la interfaz <b>Runnable</b>.
     */
    @Override
    public void run() {
        for (int i = 0; i < 1000000; i++) {
            usaMonitor();
        }
    }

    /**
     * Función de inicio. Creará los recursos para probar el ejercicio.
     * @param args No se usa.
     * @throws InterruptedException Excepción causada por la función <b>join()</b> de la clase <b>Thread</b>.
     */
    public static void main(String[] args) throws InterruptedException {
        lectorEscritor m = new lectorEscritor();
        recurso r = new recurso();
        // Crear lectores
        Thread l1 = new Thread(new usalectorEscritor(1, m, r));
        Thread l2 = new Thread(new usalectorEscritor(1, m, r));
        Thread l3 = new Thread(new usalectorEscritor(1, m, r));
        // Crear escritores
        Thread e1 = new Thread(new usalectorEscritor(0, m, r));
        //Thread e2 = new Thread(new usalectorEscritor(0, m, r));
        // Thread e3 = new Thread(new usalectorEscritor(0, m, r));

        e1.start();
        //e2.start();
        //e3.start();
        l1.start();
        l2.start();
        l3.start();
        l1.join();
        l2.join();
        l3.join();
        e1.join();
        //e2.join();
        //e3.join();
        System.out.println("El valor final del recurso es: " + r.observer());
    }
}
