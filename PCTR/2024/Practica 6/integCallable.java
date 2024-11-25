import java.util.*;
import java.util.concurrent.*;

/**
 * La clase integCallable pide por pantalla la cantidad de puntos aleatorios que
 * se desean generar para calcular la integral aproximada en f(x) = cos(x)
 * mediante el método de MonteCarlo, de forma paralela.
 * 
 * @author Javier López Sierra
 * @see MonteCarlo
 */
public class integCallable {
    /**
     * Función principal que pide por terminal el número de puntos.
     * 
     * @param args No se hace uso.
     */
    public static void main(String[] args) {
        System.out.println("Cálculo de integral definida entre [0-1] mediante método de Monte-Carlo para f(x) = cos(x).");
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca la cantidad de puntos aleatorios que se deben crear:");
        Random rand = new Random();
        long nPuntos = scan.nextLong(); // número de puntos total a probar
        int nTareas = Runtime.getRuntime().availableProcessors();
        long tVentana = nPuntos / nTareas; // número de puntos por tarea
        int contTotal = 0; // número total de éxitos
        ArrayList<Future<Long>> contParcial = new ArrayList<Future<Long>>(); // array con el conjunto de éxitos parciales
        ThreadPoolExecutor ept = new ThreadPoolExecutor(nTareas, nTareas, 0L, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
        for (int i = 0; i < nTareas; i++) {
            contParcial.add(ept.submit(new MonteCarlo(rand, tVentana)));
        }
        for (Future<Long> future : contParcial) {
            try {
                contTotal += future.get(); // sumamos el número de éxitos parcial de cada tarea
            } catch (InterruptedException | ExecutionException | CancellationException e) {
                e.printStackTrace();
            }
        }
        ept.shutdown();
        System.out.println("La integral aproximada es: " + (double) contTotal / (double) nPuntos);
        scan.close();
    }
}

/**
 * La clase MonteCarlo crea una cantidad de puntos aleatorios igual a
 * puntosParcial y devuelve el número de puntos bajo la curva de la función.
 * 
 * @author Javier López Sierra
 * @see integCallable
 * @see Callable
 */
class MonteCarlo implements Callable {
    Random rand;
    long contador_exitos;
    long puntosParcial;

    /**
     * Constructor para la clase MonteCarlo.
     * 
     * @param rand          Objeto de tipo Random.
     * @param puntosParcial Cantidad total de puntos que calcular (long).
     */
    public MonteCarlo(Random rand, long puntosParcial) {
        this.rand = rand;
        this.puntosParcial = puntosParcial;
        this.contador_exitos = 0;
    }

    /**
     * Método que crea un double aleatorio para la ordenada X de un punto (no está
     * protegido con synchronized).
     * 
     * @return valor double de una posición en el eje X de coordenadas.
     */
    private double nuevoDoubleX() {
        return rand.nextDouble();
    }

    /**
     * Método que crea un double aleatorio para la ordenada Y de un punto (está
     * protegido con synchronized).
     * 
     * @return valor double de una posición en el eje Y de coordenadas.
     */
    private synchronized double nuevoDoubleY() {
        return rand.nextDouble();
    }

    /**
     * Sobrecarga de la función call() de la interfaz Callable en la que generamos
     * el número total de puntos aleatorios asignados y devolvemos cuántos se
     * encuentran bajo la curva de la función.
     * 
     * @return Objeto Long con el número de puntos creados que se encuentran bajo la
     *         curva de la función f(x) = cos(x).
     * @see Callable#call()
     */
    public Long call() {
        double x, y;
        // hasta que calculemos el número total de puntos asignados hacer
        for (int i = 0; i < puntosParcial; i++) {
            x = nuevoDoubleX(); // creamos nuevo
            y = nuevoDoubleY(); // punto aleatorio
            if (y <= Math.cos(x)) { // si está por debajo de la curva
                contador_exitos += 1;
            }
        }
        return contador_exitos;
    }
}