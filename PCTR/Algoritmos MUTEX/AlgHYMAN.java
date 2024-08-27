/**
 * Esta clase implementa el algoritmo Hyman para exclusión mutua.
 * El algoritmo es incorrecto y no proporciona una exclusión mutua adecuada.
 * Utiliza una variable compartida y un protocolo basado en turnos para
 * controlar el acceso a la sección crítica.
 * Cada hilo entra en un bucle donde establece su propia bandera para indicar su
 * deseo de entrar en la sección crítica.
 * Luego espera hasta que sea su turno de entrar, según el valor de la variable
 * de turno compartida.
 * Sin embargo, este algoritmo no garantiza la exclusión mutua porque no evita
 * que dos hilos entren en la sección crítica simultáneamente.
 * El algoritmo sufre la posibilidad de una condición de carrera donde ambos
 * hilos establecen sus banderas y verifican la variable de turno
 * simultáneamente, lo que lleva a una violación de la exclusión mutua.
 * Además, el algoritmo no maneja la inanición, ya que un hilo puede bloquearse
 * indefinidamente esperando su turno.
 * Este algoritmo no debe usarse en entornos de producción donde se requiera
 * exclusión mutua.
 */
/**
 * Clase que implementa el algoritmo HYMAN para el acceso a una sección crítica por parte de dos hebras.
 * El algoritmo utiliza una variable global compartida y un protocolo de turno para garantizar la exclusión mutua.
 */
public class AlgHYMAN {
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
                        while (Turno != 0) {
                            while (C1 == Estado.quiereentrar)
                                ;
                            Turno = 0;
                        }
                        break;

                    case 1:
                        C1 = Estado.quiereentrar;
                        while (Turno != 1) {
                            while (C0 == Estado.quiereentrar)
                                ;
                            Turno = 1;
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
