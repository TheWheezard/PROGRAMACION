import java.util.Scanner;
import java.lang.Math;

/**
 * Esta clase pedirá al usuario que indique en cuántas partes se deberá dividir
 * el VectorPrueba, y creará los hilos necesarios para hacer las
 * multiplicaciones de diferentes rangos en paralelo
 * 
 * @author Javier López Sierra
 */
public class escalaVPar {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca partes en las que dividir el array");
        int partes = scan.nextInt(); // Indicamos en cuántas partes se va a dividir el array de VectorPrueba
        Runnable[] tareas = new Runnable[partes];
        Thread[] hilos = new Thread[partes];
        int j = 0;
        System.out.println("Creando array runnable");
        for (int i = 0; i < partes; i++) {
            tareas[i] = new VectorPrueba(j, VectorPrueba.vector.length * (i + 1) / partes); // tamVec * (i+1)/partes nos
            j = VectorPrueba.vector.length * (i + 1) / partes; // dará el final y principio de cada parte
        }

        System.out.println("Creando array de hilos");
        for (int i = 0; i < hilos.length; i++) {
            hilos[i] = new Thread(tareas[i]);
        }

        System.out.println("Iniciando hilos");
        for (int i = 0; i < hilos.length; i++) {
            hilos[i].start();
        }

        System.out.println("Esperando hilos");
        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Fin ejecucion");
        scan.close();
    }
}

/**
 * Esta clase crea un vector con 10^6 posiciones llenas de números aleatorios
 * que serán multiplicados por un mismo escalar.
 * 
 * @author Javier López Sierra
 * @see Runnable
 */
class VectorPrueba implements Runnable {
    static double[] vector = new double[(int) Math.pow(10, 6)];
    static private double escalar = 2;
    int inicio, fin = vector.length;

    /**
     * Constructor para la clase VectorPrueba.
     * 
     * @param inicio Parámetro que definirá la posición desde donde comenzará las
     *               multiplicaciones en 'cálculo'.
     * @param fin    Parámetro que indicará la posición donde terminará de
     *               realizarse la secuencia de multiplicaciones en 'cálculo'. Debe
     *               cumplirse fin > inicio para que sea un rango válido. En caso de
     *               no cumplirlo, su valor será el tamaño del vector
     *               (vector.length).
     */
    public VectorPrueba(int inicio, int fin) {
        this.inicio = inicio;
        if (fin > inicio) {
            this.fin = fin; // fin debe cumplir fin > inicio para que sea un rango
        } else {
            this.fin = vector.length; // en caso de no cumplirlo, su valor será el tamaño del vector
        }
        for (int i = 0; i < vector.length; i++) {
            vector[i] = Math.random();
        }
    }

    /**
     * Método que toma un rango del vector comprendido entre las posiciones inicio y
     * fin en la forma [inicio,fin) y los multiplica por un escalar.
     */
    public void calcular() {
        for (int i = inicio; i < fin; i++) {
            vector[i] = vector[i] * escalar;
        }
    }

    /**
     * Sobrecarga del método run() de la clase Thread que llama al método calcular.
     * 
     * @see Runnable#run()
     */
    public void run() {
        calcular();
    }

}