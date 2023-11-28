import java.util.Random;

/**
 * Clase que usa la clase <b>prodCon</b> para controlar el acceso a un buffer
 * entre cuatro hilos.
 * 
 * @author Javier López Sierra
 * @see prodCon
 * @see Thread
 */
public class usaprodCon extends Thread {
    public prodCon monitor;
    private int opcion;
    Random rand;

    /**
     * Constructor de la clase <b>usaProdCon</b>, inicializa el monitor que se usará en el proceso.
     * 
     * @param monitor : monitor de clase <prodCon>.
     */
    public usaprodCon(prodCon monitor, int opcion) {
        this.monitor = monitor;
        this.opcion = opcion;
        this.rand = new Random();
    }

    /**
     * La función <b>usaMonitor()</b> permitirá que, en función de la opción que
     * introduzcamos, el hilo realizará la función leer o escribir del monitor.
     * Para escribir, se utilizarán valores generados por la clase <b>Random</b>.
     * 
     * @param opcion : <b>int</b> valor entero, solo se admite 0 ó 1.
     * 
     * @see Random
     */
    public void usaMonitor(int opcion){
            switch (opcion) {
                case 0:
                    int valorEntrada = rand.nextInt();
                    monitor.escribir(valorEntrada);
                    break;
                case 1:
                    int valorSalida = monitor.leer();
                    System.out.println(valorSalida);
                    break;
                default:
                    break;
            }
    }

    /**
     * Sobrecarga del método run de la clase Thread con un bucle finito que repetirá
     * la llamada a la función <b>usaMonitor</b>.
     * 
     * @see usaProdCon.usaMonitor
     */
    @Override
    public void run() {
        for (int i = 0; i < 100000; i++) {
            usaMonitor(opcion);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        prodCon monitor = new prodCon();
        usaprodCon A = new usaprodCon(monitor, 0);
        usaprodCon B = new usaprodCon(monitor, 1);
        usaprodCon C = new usaprodCon(monitor, 0);
        usaprodCon D = new usaprodCon(monitor, 1);
        
        A.start();
        B.start();
        C.start();
        D.start();
        A.join();
        B.join();
        C.join();
        D.join();

        System.out.println("Fin programa.");
    }
}
