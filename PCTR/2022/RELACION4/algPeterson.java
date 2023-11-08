/**
 * Clase que controla el acceso a una variable n mediante la implementación del
 * algoritmo conocido como <b>Solución de Peterson</b>.
 * 
 * @author Javier López Sierra
 * @see Runnable
 */
public class algPeterson implements Runnable {
    int numHilo;
    public static int n = 0; //variable que sufrirá las condiciones de concurso que debemos prevenir
    private static volatile int numVueltas = 10000;
    private static volatile boolean bandera0=false, bandera1=false;
    private static volatile int turno;
    
    /**
     * Función principal que crea dos hilos para probar la implementación en Java
     * del <b>algoritmo de Peterson</b>.
     * 
     * @param args No se usa.
     * @throws InterruptedException Control de errores y excepciones asociados al
     *                              manejo de hebras.
     */
    public static void main(String[] args) throws InterruptedException {
        //asignar turno?
        algPeterson tarea0 = new algPeterson(0);
        algPeterson tarea1 = new algPeterson(1);
        Thread h0 = new Thread(tarea0);
        Thread h1 = new Thread(tarea1);
        h0.start();
        h1.start();
        h0.join();
        h1.join();

        System.out.println(n);
    }

    /**
     * Constructor de la clase <b>algPeterson</b>.
     * 
     * @param numHilo Entero que identifica al hilo en todo el algoritmo.
     */
    public algPeterson(int numHilo) {
        this.numHilo = numHilo;
    }

    /**
     * Función que realiza el control de acceso en exclusión mutua a una variable
     * compartida, en la cual un hilo hará crecer el valor y otro lo decrementará,
     * teniendo que ser el resultado final el mismo que al inicio, cero.
     */
    public void exclusionMutua() {
        if (numHilo == 0) {
            bandera0 = true;
            turno = 1;
            while (bandera1 == true && turno == 1); // espera activa
            // sección crítica
            ++n;
            System.out.println(Thread.currentThread().getName()); // nombre hilo
            // fin sección crítica
            bandera0 = false;
        } else {
            bandera1 = true;
            turno = 0;
            while (bandera0 == true && turno == 0); // espera activa
            // sección crítica
            --n;
            System.out.println(Thread.currentThread().getName()); // nombre hilo
            // fin sección crítica
            bandera1 = false;
        }
    }

    /**
     * Sobrecarga del método {@code run()} de la interfaz <b>Runnable</b> que llama
     * a la función de que realiza lo exigido en la actividad mediante el algortimo
     * de Peterson.
     * 
     * @see Runnable#run()
     */
    @Override
    public void run() {
        for (int i = 0; i < numVueltas; ++i) {
            exclusionMutua();
        }
    }
}