/**
 * AlgMUTEX2
 * 
 * Implementación de un algoritmo de exclusión mutua para dos hebras.
 * 
 * Este algoritmo garantiza la exclusión mutua, ya que las hebras se turnan para
 * entrar a la sección crítica.
 * 
 * La variable global "turno" indica cuál es el turno de la hebra que puede
 * entrar a la sección crítica.
 * 
 * Inicialmente, el turno es 0, lo que significa que la hebra 0 puede entrar a
 * la sección crítica.
 * 
 * Cuando una hebra entra a la sección crítica, actualiza el turno para que la
 * otra hebra pueda entrar.
 * 
 * Este algoritmo no funciona correctamente si las hebras no se ejecutan en el
 * mismo orden siempre, si una hebra se ejecuta más rápido que la otra, o si una
 * hebra se bloquea. Tampoco si una hebra no se ejecuta nunca.
 */
public class AlgMUTEX2 {
    private static int turno = 0;

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
                while (turno != id) {
                    // Wait for turn
                }
                // Critical section
                // Perform critical section operations
                System.out.println("Hebra " + id + " está en la sección crítica");

                // Protocolo de salida de la sección crítica
                switch (id) {
                    case 0:
                        turno = 1;
                        break;
                    case 1:
                        turno = 0;
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
