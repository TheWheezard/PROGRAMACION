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

    public usalectorEscritor(int tipo, lectorEscritor monitor) {
        this.tipo = tipo;
        this.monitor = monitor;
    }

    public void usaMonitor() {}

    @Override
    public void run() {
        for (int i = 0; i < 1000000; i++) {
            usaMonitor();
        }
    }
    //TODO: main, usaMonitor y comentarios
}
