/**
 * Algoritmo de exclusión mutua para dos hebras.
 * 
 * Este algoritmo garantiza la exclusión mutua, ya que las hebras se turnan para
 * entrar a la sección crítica.
 * 
 * Sin embargo, este algoritmo no garantiza terminar en un tiempo finito
 * medible, ya que las hebras pueden quedar en espera ilimitada (no confundir
 * con espera infinita) si ejecutan la primera parte del protocolo al mismo
 * tiempo.
 */
public class AlgMUTEX5 {
    // Enumerado para representar los posibles estados de la variable global
    private enum Estado {
        quiereentrar, restoproceso
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
                        C0 = Estado.quiereentrar;
                        while (C1 == Estado.quiereentrar) {
                            C0 = Estado.restoproceso;
                            try {
                                this.wait(500);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            C0 = Estado.quiereentrar;
                        }
                        break;

                    case 1:
                        C1 = Estado.quiereentrar;
                        while (C0 == Estado.quiereentrar) {
                            C1 = Estado.restoproceso;
                            try {
                                this.wait(500);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            C1 = Estado.quiereentrar;
                        }
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
