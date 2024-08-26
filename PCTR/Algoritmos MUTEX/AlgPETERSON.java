/**
 * La clase AlgPETERSON implementa el algoritmo de Peterson para exclusión mutua.
 * Este algoritmo permite que dos hilos accedan a una sección crítica de código sin interferencias.
 * El algoritmo utiliza variables compartidas y un protocolo basado en turnos para garantizar la exclusión mutua.
 * 
 * La clase contiene una clase anidada Hebra que representa un hilo. Cada hilo ejecuta un bucle infinito
 * donde ejecuta código de sección no crítica, entra en la sección crítica utilizando el algoritmo de Peterson,
 * realiza operaciones de la sección crítica y sale de la sección crítica.
 * 
 * El algoritmo de Peterson funciona de la siguiente manera:
 * - Cada hilo establece su bandera de desea-entrar a verdadero y establece el turno al otro hilo.
 * - El hilo espera hasta que el otro hilo desee entrar o sea su turno.
 * - Una vez dentro de la sección crítica, el hilo realiza las operaciones de la sección crítica.
 * - Después de salir de la sección crítica, el hilo establece su bandera de desea-entrar a falso.
 * 
 * El método main crea dos hilos y los inicia. Luego espera a que los hilos terminen la ejecución.
 * Finalmente, imprime un mensaje indicando el fin del programa.
 */
public class AlgPETERSON {
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
            while (true) {
                // Sección no crítica
                // ...

                // Protocolo de acceso a la sección crítica
                switch (id) {
                    case 0:
                        C0 = Estado.quiereentrar;
                        Turno = 1;
                        while ((C1 == Estado.quiereentrar) && (Turno == 1)) {
                            // Esperar el turno
                        }
                        break;

                    case 1:
                        C1 = Estado.quiereentrar;
                        Turno = 0;
                        while ((C0 == Estado.quiereentrar) && (Turno == 0)) {
                            // Esperar el turno
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
                        break;
                    case 1:
                        C1 = Estado.restoproceso;
                        break;
                }

                // Sección no crítica
                System.out.println("Hebra " + id + " está en la sección no crítica");
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
