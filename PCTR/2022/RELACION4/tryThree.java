/**
 * Clase que emplea la tercera aproximación al algoritmo de Dekker, en el que se
 * produce el problema de espera infinita (livelock)
 * 
 * @author Javier López Sierra
 * @see Thread
 */
public class tryThree extends Thread {
    private int tipoHilo;
    private static volatile int nVueltas = 10000;
    private static volatile int n = 0;
    private static volatile boolean C1 = false;
    private static volatile boolean C2 = false;

    /**
     * Función que crea los hilos que prueban la tercera aproximación de Dekker
     * 
     * @throws InterruptedException gestión de posibles errores al lanzar o terminar
     *                              los hilos
     */
    public static void main(String[] args) throws InterruptedException {
        tryThree h1 = new tryThree(1);
        tryThree h2 = new tryThree(2);
        h1.start();
        h2.start();
        h1.join();
        h2.join();
        System.out.println(n);
    }

    /**
     * Constructor para la clase tryThree
     * 
     * @param tipoHilo Entero que identifica al hilo en el algoritmo
     */
    public tryThree(int tipoHilo) {
        this.tipoHilo = tipoHilo;
    }

    /**
     * Sobrecarga del método run() de la clase Thread que emplea la tercera
     * aproximación del algoritmo de Dekker para comprobar si el hilo tiene el turno
     * de paso para modificar una variable n
     * 
     * @see Thread#run()
     */
    public void run() {
        switch (tipoHilo) {
        case 1:
            for (int i = 0; i < nVueltas; i++) {
                C1 = true; // Señala que quiere acceder a la SC
                while (C2 == true); // Espera a que el otro hilo libere la SC

                n++; // Sección Crítica
                System.out.println(getName()); // Nombre hilo
                
                C1 = false; // Fin de SC, libera el recurso
            }
            break;
        case 2:
            for (int i = 0; i < nVueltas; i++) {
                C2 = true; // Señala que quiere acceder a la SC
                while (C1 == true); // Espera a que el otro hilo libere la SC

                n--; // Sección Crítica
                System.out.println(getName()); // Nombre hilo

                C2 = false; // Fin de SC, libera el recurso
            }
            break;
        }
    }
}
