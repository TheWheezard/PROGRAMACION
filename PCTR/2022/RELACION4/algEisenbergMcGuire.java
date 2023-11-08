/**
 * Clase que emplea el algoritmo Eisenberg-McGuire para controlar el acceso y
 * modificación de una variable común en más de dos hilos (realizamos una prueba
 * con cuatro hilos)
 * 
 * @author Javier López Sierra
 * @see Thread
 */
public class algEisenbergMcGuire extends Thread {
    public static int n = 0;
    private static volatile int numVueltas = 10000;
    private enum estado {IDLE, WAIT, ACTIVE};
    private static volatile estado[] flags;
    private static volatile int turno;
    int numHilo;

    /**
     * Constructor de la clase algEisenbergMcGuire
     * 
     * @param numHilo Entero que identifica al hilo en todo el algoritmo
     */
    public algEisenbergMcGuire(int numHilo) {
        this.numHilo = numHilo;
        if (flags == null) {
            flags = new estado[4]; // Vector flags para 4 hilos
        }
        flags[numHilo] = estado.IDLE;
    }

    /**
     * Sobrecarga del método run() de la clase Thread que emplea el algoritmo de
     * Eisenberg-McGuire para controlar el acceso a una sección crítica, en este
     * caso modificar una variable común
     * 
     * @see Thread#run()
     */
    public void run() {
        int index;
        for (int i = 0; i < numVueltas; i++) {
            do {
                flags[numHilo] = estado.WAIT; // se pone en espera
                index = turno;
                while (index != numHilo) { // hasta que no llegue su turno
                    if (flags[index] != estado.IDLE) {
                        index = turno;
                    } else {
                        index = (index + 1) % flags.length;
                    }
                }

                flags[numHilo] = estado.ACTIVE; // hilo pasa a ACTIVO
                index = 0;
                while ((index < flags.length) && ((index == numHilo) || (flags[index] != estado.ACTIVE))) { // comprueba que es el único hilo activo
                    index = index + 1;
                }
            } while ( !((index >= flags.length) && ((turno == numHilo) || (flags[turno] == estado.IDLE))) ); // si hilo es el único activo y con turno,
                                                                                 // o los demás están en IDLE, pasa a la Sección Crítica
            turno = numHilo; // toma el turno
            /* Sección Crítica */
            if (numHilo / 2 == 0) {
                n++;
            } else {
                n--;
            }
            /* Fin Sección Crítica */

            index = (turno + 1) % flags.length;
            while (flags[index] == estado.IDLE) { // buscamos procesos que no estén en IDLE
                index = (index + 1) % flags.length;
            }
            turno = index; // les pasamos el turno
            flags[numHilo] = estado.IDLE; // el hilo pasa a IDLE
        }
    }

    /**
     * Función principal que crea los hilos que prueban la implementación del
     * algoritmo de Eisenberg-McGuire
     *
     * @throws InterruptedException gestión de mensajes de error al lanzar o
     *                              terminar los hilos de prueba
     */
    public static void main(String[] args) throws InterruptedException {
        turno = 1;
        algEisenbergMcGuire h0 = new algEisenbergMcGuire(0);
        algEisenbergMcGuire h1 = new algEisenbergMcGuire(1);
        algEisenbergMcGuire h2 = new algEisenbergMcGuire(2);
        algEisenbergMcGuire h3 = new algEisenbergMcGuire(3);
        h0.start();
        h1.start();
        h2.start();
        h3.start();
        h0.join();
        h1.join();
        h2.join();
        h3.join();
        System.out.println(n);
    }
}
