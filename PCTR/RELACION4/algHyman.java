/**
 * Clase que controla el acceso a una variable n mediante la implementación del
 * algoritmo incorrecto de Hyman
 * 
 * @author Javier López Sierra
 * @see Runnable
 */
public class algHyman implements Runnable {
    private static volatile int nVueltas = 10000;
    private static volatile boolean C1 = false;// T=quiereentrar F=restoproceso
    private static volatile boolean C2 = false;// T=quiereentrar F=restoproceso
    private static volatile int turno = 0;
    private static int n = 0;
    private int tipoHilo;

    /**
     * Constructor para la clase algHyman
     * 
     * @param tipoHilo Entero que identifica al hilo en el algoritmo (0 o 1)
     */
    public algHyman(int tipoHilo) {
        this.tipoHilo = tipoHilo;
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable que implementa el
     * algoritmo incorrecto de Hyman para comprobar si el hilo tiene turno para
     * poder modificar una variable n
     * 
     * @see Runnable#run()
     */
    public void run() {
        switch (tipoHilo) {
        case 1:
            for (int i = 0; i < nVueltas; i++) {
                C1 = true; // Señala que quiere acceder a SC
                while (turno != 0) { // Mientras no sea su turno
                    while (C2 == true) { // No sale del bucle mientras el otro hilo esté en SC
                        turno = 0; // Toma control del turno
                    }
                }

                n++; // Sección Crítica

                C1 = false; // Sale de la SC, cede el turno
            }
            break;
        case 2:
            for (int i = 0; i < nVueltas; i++) {
                C2 = true; // Señala que quiere acceder a SC
                while (turno != 1) { // Mientras no sea su turno
                    while (C1 == true) { // No sale del bucle mientras el otro hilo esté en SC
                        turno = 1; // Toma control del turno
                    }
                }

                n--; // Sección Crítica

                C2 = false; // Sale de la SC, cede el turno
            }
            break;
        }
    }

    /**
     * Función principal que crea los hilos que prueban el algoritmo incorrecto de
     * Hyman
     * 
     * @throws InterruptedException gestiona los potenciales errores al lanzar o
     *                              terminar los hilos
     */
    public static void main(String[] args) throws InterruptedException {
        Runnable alg1 = new algHyman(1);
        Runnable alg2 = new algHyman(2);
        Thread h1 = new Thread(alg1);
        Thread h2 = new Thread(alg2);
        h1.start();
        h2.start();
        h1.join();
        h2.join();
        System.out.println(n);
    }
}
