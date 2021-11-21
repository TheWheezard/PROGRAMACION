import java.util.ArrayList;
import java.util.concurrent.*;

/**
 * La clase numPerfectosParalelo hace la búsqueda de números perfectos de forma
 * paralela en un rango dado por consola y dividiendo las tareas de acuerdo a la
 * ecuación de Subramanian con Coeficiente de Bloqueo = 0.
 * 
 * @author Javier López Sierra
 * @see InnerNumPefectosParalelo
 */
public class numPerfectosParalelo {
    /**
     * Función Main de numPerfectosParalelo en un rango [1-args].
     * 
     * @param args Valor numérico que determina el máximo del rango a comprobar.
     */
    public static void main(String[] args) {
        long nPuntos = Long.parseLong(args[0]); // rango de la muestra
        int nTareas = Runtime.getRuntime().availableProcessors();
        long tVentana = nPuntos / nTareas;
        int contTotal = 0;
        long linf = 0;
        long lsup = tVentana;
        ArrayList<Future<Integer>> contParcial = new ArrayList<Future<Integer>>();

        long inicTiempo = System.nanoTime();
        ThreadPoolExecutor ept = new ThreadPoolExecutor(nTareas, nTareas, 0L, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
        for (int i = 0; i < nTareas; i++) {
            contParcial.add(ept.submit(new InnerNumPerfectosParalelo(linf, lsup)));
            linf = lsup + 1;
            lsup += tVentana;
        }

        for (Future<Integer> future : contParcial) {
            try {
                contTotal += future.get(); // sumamos el conteo de cada tarea
            } catch (InterruptedException | ExecutionException | CancellationException e) {
                e.printStackTrace();
            }
        }
        ept.shutdown();

        double tiempoTotal = (double) (System.nanoTime() - inicTiempo) / (long) 1.0e9;
        System.out.println("Hallados " + contTotal + " números perfectos en " + tiempoTotal + " segundos");
    }
}

/**
 * La clase InnerNumPerfectosParalelo recibe el intervalo dentro del rango
 * general en el que debe hacer la búsqueda de números perfectos y devuelve
 * cuántos ha hallado.
 * 
 * @author Javier López Sierra
 * @see Callable
 */
class InnerNumPerfectosParalelo implements Callable {
    private long ini;
    private long fin;
    private int total = 0;

    /**
     * Constructor para la clase InnerNumPerfectosParalelo.
     * 
     * @param ini Inicio del intervalo dentro del rango principal.
     * @param fin Final del intervalo dentro del rango principal.
     */
    public InnerNumPerfectosParalelo(long ini, long fin) {
        this.ini = ini;
        this.fin = fin;
    }

    /**
     * Función que determina si un número cumple con la condición para considerarse
     * perfecto.
     * 
     * @param num (long) El número que vamos a evaluar.
     * @return Devolvemos si es perfecto (true) o no (false).
     */
    private static boolean esPerfecto(long num) {
        long aux = 0;
        for (long i = 1; i < num; i++) {
            if (num % i == 0) { // si es divisor de num
                aux += i; // lo añadimos a la suma de divisores
            }
        }

        if (aux == num) { // si la suma de divisores equivale a num
            return true; // es perfecto
        } else {
            return false;
        }
    }

    /**
     * Sobrecarga de la función call() de la interfaz Callable que realiza el conteo
     * de números perfectos.
     * 
     * @return Entero con el total de números perfectos hallados en el intervalo.
     * @see Callable#call()
     */
    public Integer call() {
        for (long i = ini; i < fin; i++) {
            if (esPerfecto(i)) {
                total += 1;
            }
        }
        return total;
    }
}