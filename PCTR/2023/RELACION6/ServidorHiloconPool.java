import java.net.*;
import java.util.concurrent.*;
import java.io.*;

/**
 * La clase ServidorHiloconPool recibe valores enteros por el puerto 2001,
 * tratando cada conexión en un hilo independiente y gestionando dichos hilos
 * mediante un ejecutor.
 * 
 * @author Javier López Sierra
 * @see Runnable
 */
public class ServidorHiloconPool implements Runnable {
    Socket enchufe;

    /**
     * Constructor de la clase ServidorHiloconPool.
     * 
     * @param s Objeto de tipo Socket
     */
    public ServidorHiloconPool(Socket s) {
        this.enchufe = s;
    }

    /**
     * Sobrecarga del método run de la clase Runnable. Recibe un valor entero desde
     * un Socket y lo muestra por pantalla indicando qué hilo se ha ocupado de
     * realizar la tarea.
     * 
     * @see Runnable#run()
     */
    public void run() {
        try {
            BufferedReader entrada = new BufferedReader(new InputStreamReader(enchufe.getInputStream()));
            String datos = entrada.readLine();
            int j;
            int i = Integer.valueOf(datos).intValue();
            for (j = 1; j <= 4; j++) {
                System.out.println("El hilo " + Thread.currentThread().getName() + " escribiendo el dato " + i);
                Thread.sleep(1000);
            }
            enchufe.close();
            System.out.println("El hilo " + Thread.currentThread().getName() + " cierra su conexion...");
        } catch (Exception e) {
            System.out.println("Error...");
        }
    }// run

    public static void main(String[] args) {
        int puerto = 2001;
        int nTareas = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor ept = new ThreadPoolExecutor(nTareas, nTareas, 0L, TimeUnit.MILLISECONDS,
                new LinkedBlockingQueue<Runnable>());
        ept.prestartAllCoreThreads();
        try {
            ServerSocket chuff = new ServerSocket(puerto, 3000);

            while (true) {
                System.out.println("Esperando solicitud de conexion...");
                Socket cable = chuff.accept();
                System.out.println("Recibida solicitud de conexion...");
                ept.execute(new ServidorHiloconPool(cable));
            } // while
              // ept.shutdown();
        } catch (Exception e) {
            System.out.println("Error en sockets...");
        }
    }// main

}// Servidor_Hilos
