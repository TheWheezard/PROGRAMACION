/**
 * AlgMUTEX3.java
 * 
 * Tercera implementación del algoritmo de exclusión mutua para dos procesos.
 * 
 * Este algoritmo no garantiza la exclusión mutua, ya que dos hebras pueden
 * entrar a la sección crítica al mismo tiempo.
 */
public class AlgMUTEX3 {
    // Enumerado para representar los posibles estados de la variable global
    private enum Estado {
        enSC, restoproceso
    }

    // Variable global compartida
    private static volatile Estado C0 = Estado.restoproceso;
    private static volatile Estado C1 = Estado.restoproceso;

    private static class Hebra implements Runnable {
        private final int id;

        public Hebra(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            while (true) {
                // Non-critical section
                // ...

                // Protocolo de acceso a la sección crítica
                switch (id) {
                    case 0:
                        while (C1 == Estado.enSC) {
                            // Wait for turn
                        }
                        C0 = Estado.enSC;
                        break;

                    case 1:
                        while (C0 == Estado.enSC) {
                            // Wait for turn
                        }
                        C1 = Estado.enSC;
                        break;
                }
                // Critical section
                // Perform critical section operations
                System.out.println("Hebra " + id + " está en la sección crítica");

                // Protocolo de salida de la sección crítica
                switch (id) {
                    case 0:
                        C0 = Estado.restoproceso;
                        break;
                    case 1:
                        C1 = Estado.restoproceso;
                        break;
                }

                // Non-critical section
                System.out.println("Hebra " + id + " está en la sección no crítica");
            }
        }
    }

    public static void main(String[] args) {
        // Create the threads
        Thread thread1 = new Thread(new Hebra(0));
        Thread thread2 = new Thread(new Hebra(1));

        // Start the threads
        thread1.start();
        thread2.start();

        // Wait for the threads to finish
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Fin del programa");
    }
}