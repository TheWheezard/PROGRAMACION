
/**
 * Algoritmo de exclusión mutua con variable global compartida
 * 
 * Este algoritmo implementa la exclusión mutua mediante una variable global compartida.
 * 
 * La variable global es de tipo enumerado y puede tener dos valores: sclibre y scocupada.
 * 
 * La variable global se inicializa a sclibre.
 * 
 * Cada hebra ejecuta un bucle infinito en el que intenta entrar a la sección crítica.
 * 
 * Para entrar a la sección crítica, la hebra debe esperar a que la variable global esté en sclibre.
 * 
 * Una vez que la hebra entra a la sección crítica, la variable global se pone a scocupada.
 * 
 * Este algoritmo no garantiza realizar la exclusión mutua, ya que dos hebras pueden entrar a la sección crítica al mismo tiempo.
 */
public class AlgMUTEX1 {
    // Enumerado para representar los posibles estados de la variable global
    private enum Estado {sclibre, scocupada}
    
    // Variable global compartida
    private static volatile Estado estado = Estado.sclibre;

    // Clase para representar una hebra
    private static class Hebra implements Runnable {
        private final int id;

        public Hebra(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            while (true) {
                // Entrada a la sección crítica
                while (estado == Estado.scocupada) {/* Esperar hasta que la variable global esté libre */}
                estado = Estado.scocupada;

                // Sección crítica
                System.out.println("Hebra " + id + " está en la sección crítica");

                // Salida de la sección crítica
                estado = Estado.sclibre;

                // Sección no crítica
                System.out.println("Hebra " + id + " está en la sección no crítica");

                // Esperar un tiempo antes de volver a intentar entrar a la sección crítica
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        // Crear las dos hebras
        Thread hebra1 = new Thread(new Hebra(1));
        Thread hebra2 = new Thread(new Hebra(2));

        // Iniciar las hebras
        hebra1.start();
        hebra2.start();

        // Esperar a que las hebras terminen
        try {
            hebra1.join();
            hebra2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Fin del programa");
    }
}