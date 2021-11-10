/**
 * Clase que emplea la cuarta aproximación al algoritmo de Dekker, en el que se
 * elimina el problema de espera infinita (livelock) pero de forma poco elegante
 * 
 * @author Javier López Sierra
 * @see Java.lang.Thread
 */
public class tryFour extends Thread {
    private int tipoHilo;
    private static volatile int nVueltas = 10000;
    private static volatile int n = 0;
    private static volatile boolean C1 = false;
    private static volatile boolean C2 = false;

    /**
     * Constructor para la clase tryThree
     * 
     * @param tipoHilo
     */
    public tryFour(int tipoHilo) {
        this.tipoHilo = tipoHilo;
    }

    /**
     * Sobrecarga del método run() de la clase Thread que cambia el valor de una
     * variable n, pero comprobando si puede hacerlo mediante la cuarta
     * aproximación del algoritmo de Dekker
     * 
     * @see Java.lang.Thread.run
     */
    public void run() {
        switch (tipoHilo) {
        case 1:
            for (int i = 0; i < nVueltas; i++) {
                C1 = true;
                while (C2 == true){
                    C1 = false; //ceder el paso
                    int k = i; // operaciones que solo ocupan tiempo
                    k = k-i;
                    C1 = true; //pedir acceso de nuevo
                }
                n++;
                C1 = false;
            }
            break;
        case 2:
            for (int i = 0; i < nVueltas; i++) {
                C2 = true;
                while (C1 == true){
                    C2 = false; // ceder el paso
                    int k = 0; // operaciones que solo ocupan tiempo
                    k = k+i;
                    C2 = true; // pedir acceso de nuevo
                }
                n--;
                C2 = false;
            }
            break;
        }
    }

    /**
     * Función que crea los hilos que prueban la cuarta aproximación de Dekker
     * 
     * @throws InterruptedException gestión de posibles errores al lanzar o terminar
     *                              los hilos
     */
    public static void main(String[] args) throws InterruptedException {
        tryFour h1 = new tryFour(1);
        tryFour h2 = new tryFour(2);
        h1.start();
        h2.start();
        h1.join();
        h2.join();
        System.out.println(n);
    }
}

