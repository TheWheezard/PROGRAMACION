/**
 * Esta clase implementa el algoritmo de Dekker para exclusión mutua.
 * El algoritmo permite que dos hilos accedan a una sección crítica de manera mutuamente excluyente.
 * El algoritmo utiliza dos variables compartidas C0 y C1 para representar los estados de los hilos.
 * El algoritmo también utiliza una variable compartida Turno para determinar qué hilo tiene el turno de entrar en la sección crítica.
 * El algoritmo sigue los siguientes pasos:
 * 1. Cada hilo establece su respectiva variable C a "quiereentrar" (desea entrar).
 * 2. Cada hilo entra en un bucle while y verifica si el otro hilo también desea entrar en la sección crítica.
 * 3. Si el otro hilo desea entrar y no es el turno del hilo actual, el hilo actual establece su variable C a "restoproceso" y espera su turno.
 * 4. Una vez que es el turno del hilo actual, establece su variable C nuevamente en "quiereentrar" y entra en la sección crítica.
 * 5. Después de ejecutar la sección crítica, el hilo establece su variable C nuevamente en "restoproceso" y sale de la sección crítica.
 * 6. Luego, el hilo entra en la sección no crítica y continúa con su ejecución normal.
 * El método main crea dos hilos y los inicia. Espera a que los hilos terminen y luego imprime un mensaje indicando el final del programa.
 */
public class AlgDEKKER {
    // Enumerado para representar los posibles estados de la variable global
    private enum Estado {
        quiereentrar, restoproceso
    }
    private static volatile int Turno = 0;

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
            int i = 5000;
            while (i > 0) {
                // Sección no crítica
                // ...

                // Protocolo de acceso a la sección crítica
                switch (id) {
                    case 0:
                        C0 = Estado.quiereentrar;
                        while (C1 == Estado.quiereentrar) {
                            if (Turno == 1) {
                                C0 = Estado.restoproceso;
                                while (Turno == 1) {
                                    // Esperar el turno
                                }
                                C0 = Estado.quiereentrar;
                                Turno = 0;
                            }
                            C0 = Estado.restoproceso;
                        }
                        break;

                    case 1:
                        C1 = Estado.quiereentrar;
                        while (C0 == Estado.quiereentrar) {
                            if (Turno == 0) {
                                C1 = Estado.restoproceso;
                                while (Turno == 0) {
                                    // Esperar el turno
                                }
                                C1 = Estado.quiereentrar;
                                Turno = 1;
                            }
                            C1 = Estado.restoproceso;
                        }
                        break;
                }
                // Sección crítica
                // Realizar operaciones de la sección crítica
                System.out.println("Hebra " + id + " está en la sección crítica");

                // Protocolo de salida de la sección crítica
                switch (id) {
                    case 0:
                        C0 = Estado.restoproceso;
                        Turno = 1;
                        break;
                    case 1:
                        C1 = Estado.restoproceso;
                        Turno = 0;
                        break;
                }

                // Sección no crítica
                // System.out.println("Hebra " + id + " está en la sección no crítica");
                i--;
            }

        }
    }

    public static void main(String[] args) {
        // Crear los hilos
        Thread thread1 = new Thread(new Hebra(0));
        Thread thread2 = new Thread(new Hebra(1));

        // Iniciar los hilos
        thread1.start();
        thread2.start();

        // Esperar a que los hilos terminen
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Fin del programa");
    }
}