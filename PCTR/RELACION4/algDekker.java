/**
 * Clase que emplea el algoritmo de Dekker en su forma final, en el que se
 * elimina el problema de espera infinita (livelock) y se evita el problema de
 * postergación indefinida mediante una variable que ayuda a desempatar al
 * competir por el turno
 * 
 * @author Javier López Sierra
 * @see Thread
 */
public class algDekker extends Thread {
    private int tipoHilo;
    private static volatile int nVueltas = 10000;
    private static volatile int n = 0;
    private static volatile boolean C1 = false;
    private static volatile boolean C2 = false;
    private static volatile int turno = 1;

    /**
     * Constructor para la clase algDekker
     * 
     * @param tipoHilo Entero que identifica al hilo en el algoritmo
     */
    public algDekker(int tipoHilo) {
        this.tipoHilo = tipoHilo;
    }

    /**
     * Sobrecarga del método run() de la clase Thread que emplea la aproximación
     * final del algoritmo de Dekker para comprobar si el hilo tiene el turno de
     * paso para modificar una variable n
     * 
     * @see Thread#run()
     */
    public void run() {
        switch (tipoHilo) {
        case 1:
            for (int i = 0; i < nVueltas; i++) {
                C1 = true;
                while (C2 == true) {
                    if (turno == 2) {
                        C1 = false; // ceder el paso
                        turno = 1;
                        C1 = true; // pedir acceso de nuevo
                    }
                }
                n++;
                turno = 2;
                C1 = false;
            }
            break;
        case 2:
            for (int i = 0; i < nVueltas; i++) {
                C2 = true;
                while (C1 == true) {
                    if (turno == 1) {
                        C2 = false; // ceder el paso
                        turno = 2;
                        C2 = true; // pedir acceso de nuevo
                    }
                }
                n--;
                turno = 1;
                C2 = false;
            }
            break;
        }
    }

    /**
     * Función que crea los hilos que prueban la aproximación final del algoritmo de
     * Dekker
     * 
     * @throws InterruptedException gestión de posibles errores al lanzar o terminar
     *                              los hilos
     */
    public static void main(String[] args) throws InterruptedException {
        algDekker h1 = new algDekker(1);
        algDekker h2 = new algDekker(2);
        h1.start();
        h2.start();
        h1.join();
        h2.join();
        System.out.println(n);
    }
}
