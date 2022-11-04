/**
 * Clase que emplea el <b>algoritmo de Dekker</b> en su forma final, en el que se
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
     * Función que emplea la aproximación final del algoritmo de Dekker para
     * comprobar si el hilo tiene el turno de paso para modificar una variable n.
     */
    public void exclusionMutua(){
        switch (tipoHilo) {
            case 1:
                C1 = true; // Solicita acceso a la SC
                while (C2 == true) { // Si ya fue solicitado por el otro hilo
                    if (turno == 2) { // y es turno del otro hilo
                        C1 = false; // ceder el paso
                        turno = 1;
                        C1 = true; // pedir acceso de nuevo
                    }
                }

                n++; // Sección Crítica

                turno = 2; // Fin de la SC, cede el turno
                C1 = false; // Señala que ha finalizado su uso del recurso

            break;
            case 2:
                C2 = true; // Solicita acceso a la SC
                while (C1 == true) { // Si ya fue solicitado por el otro hilo
                    if (turno == 1) { // y es turno del otro hilo
                        C2 = false; // ceder el paso
                        turno = 2;
                        C2 = true; // pedir acceso de nuevo
                    }
                }

                n--; // Sección Crítica

                turno = 1; // Fin de la SC, cede el turno
                C2 = false; // Señala que ha finalizado su uso del recurso

            break;
        }
    }

    /**
     * Sobrecarga del método {@code run()} de la clase <b>Thread</b> que, mediante
     * un bucle, realiza varios accesos a una variable compartida mediante la
     * función {@code exclusionMutua()}.
     * 
     * @see Thread#run()
     * @see algDekker#exclusionMutua()
     */
    @Override
    public void run() {
        for (int i = 0; i < nVueltas; ++i) {
            exclusionMutua();
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
