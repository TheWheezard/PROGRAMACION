/**
 * Clase que usa la clase Sem para controlar el acceso a una variable estática n
 * entre dos hilos.
 * 
 * @author Javier López Sierra
 * @see Sem
 */
public class usaSem extends Thread {
    public static int n = 0;
    public Sem semaforo;

    /**
     * Constructor de la clase usaSem, se le asocia un semáforo de clase Sem.
     * 
     * @param semaforo semáforo que se va a utilizar para el control.
     */
    public usaSem(Sem semaforo) {
        this.semaforo = semaforo;
    }

    /**
     * Sobrecarga del método run de la clase Thread que permite modificar el valor n
     * solo si el semáforo le da acceso.
     */
    @Override
    public void run() {
        for (int i = 0; i < 100000; i++) {
            semaforo.waitS();
            n++;
            semaforo.signalS();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Sem mon_sem = new Sem(1);
        usaSem A = new usaSem(mon_sem);
        usaSem B = new usaSem(mon_sem);
        A.start();
        B.start();
        A.join();
        B.join();
        System.out.println(n);
    }
}
