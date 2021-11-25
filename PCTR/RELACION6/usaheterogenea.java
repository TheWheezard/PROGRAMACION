/**La clase usaheterogenea crea un par de hilos que prueban el funcionamiento de las funciones de la clase heterogenea de forma concurrente, heredando de la clase Thread.
 * @author Javier López Sierra
 * @see heterogenea
 * @see Thread
 */
public class usaheterogenea extends Thread{
    int numVueltas = 10000;
    heterogenea het;

    /**
     * Constructor de la clase usaheterogenea.
     * @param het Objeto de tipo "heterogenea".
     */
    public usaheterogenea(heterogenea het) {
        this.het = het;
    }

    /**
     * Sobrecarga del método run de la interfaz Runnable. Ejecuta un bucle que llama a los métodos sumN y sumM de la clase heterogenea.
     * @see heterogenea#sumN()
     * @see heterogenea#sumM()
     * @see Runnable#run()
     */
    public void run() {
        for (int i = 0; i < numVueltas; i++) {
            het.sumN();
            het.sumM();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        heterogenea aux = new heterogenea();
        usaheterogenea A = new usaheterogenea(aux);
        usaheterogenea B = new usaheterogenea(aux);
        A.start();
        B.start();
        A.join();
        B.join();
        System.out.println("Variable n = " + aux.getN());
        System.out.println("Variable m = " + aux.getM());
    }
}
