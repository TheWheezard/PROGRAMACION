import java.util.Scanner;
import java.text.*;
import java.util.Date;

/**
 * La clase prodEscalarParalelo crea dos vectores de tipo double de misma
 * longitud y los divide en partes que se multiplican de forma concurrente
 * mediante el uso de la clase prodEscalarParalelo.
 * 
 * @author Javier López Sierra
 * @see EscalarParalelo
 */
public class prodEscalarParalelo {
    static double[] vec1 = new double[(int) Math.pow(10, 6)];
    static double[] vec2 = new double[(int) Math.pow(10, 6)];
    
    /**
     * <p>
     * La función main rellena dos vectores de tipo <b>double</b> con números
     * aleatorios, para acto seguido dividirlos en tantas partes como indique el
     * usuario por teclado. Dichas partes se enviarán a hebras de tipo
     * EscalarParalelo, que se ejecutarán al mismo tiempo.
     * </p>
     * <p>
     * Esta clase main recibirá los resultados y terminará la operación de producto
     * escalar realizando la suma de éstos. Toda la operación de producto escalar
     * será controlada por un cronómetro. Se devuelve por pantalla el resultado, así
     * como fecha, hora y tiempo que se ha tardado en completar la operación.
     * </p>
     * 
     * @param args No se emplea
     */
    public static void main(String[] args) {
        for (int i = 0; i < vec1.length; i++) { // rellenamos vec1 y vec2
            vec1[i] = vec2[i] = Math.random();
        }
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca numero de partes en que partir los vectores:");
        int partes = scan.nextInt();
        EscalarParalelo[] productos = new EscalarParalelo[partes];
        Thread[] hilos = new Thread[partes];
        int j = 0;
        for (int i = 0; i < partes; i++) { // creamos los hilos con los rangos que van a usar
            hilos[i] = productos[i] = new EscalarParalelo(i, j, vec1.length * (i + 1) / partes);
            j = vec1.length * (i + 1) / partes;
        }

        /* Mediremos exclusivamente el producto escalar */
        Date d = new Date();
        DateFormat df = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom = System.currentTimeMillis(); // se prepara el cronometro
        d.setTime(inicCronom); // se activa el cronometro

        // inicio y fin de la ejecución de los hilos
        for (int i = 0; i < hilos.length; i++) {
            hilos[i].start();
        }
        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // recuperando resultados parciales de los hilos en el vector productoParcial
        double[] productoParcial = new double[partes];
        for (int i = 0; i < partes; i++) {
            System.out.println("Recuperando resultado del hilo " + productos[i].getIdHebra());
            productoParcial[productos[i].getIdHebra()] = productos[i].getRes();
        }

        // cálculo del resultado final
        double res = 0;
        for (int i = 0; i < productoParcial.length; i++) {
            res += productoParcial[i];
        }
        System.out.println("Resultado = " + res);

        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d.setTime(finCronom);
        System.out.println("Calculo finalizado a las " + df.format(d) + " tras " + (finCronom - inicCronom) + " milisegundos");
        scan.close();

        System.out.println("Fin.");
    }
}

/**
 * La clase EscalarParalelo crea un hilo con un vector auxiliar donde
 * efectuará el producto escalar entre los elementos comprendidos entre dos
 * posiciones dadas de dos vectores principales.
 * 
 * @author Javier López Sierra
 * @see Java.lang.Thread
 */
class EscalarParalelo extends Thread {
    double res; //almacenará el resultado del cálculo
    int idHebra, inicio, fin;

    /**
     * Constructor de la clase prodEscalarParalelo.
     * 
     * @param idHebra Parámetro de tipo Int que identificará el número de
     *                hebra/vector.
     * @param inicio  Parámetro de tipo Int que indicará la posición inicial del
     *                rango de posiciones en los vectores principales donde se hará
     *                el cálculo.
     * @param fin     Parámetro de tipo Int que indicará la posición final del rango
     *                de posiciones en los vectores principales donde se hará el
     *                cálculo.
     */
    public EscalarParalelo(int idHebra, int inicio, int fin) {
        this.idHebra = idHebra;
        this.inicio = inicio;
        this.fin = fin;
    }

    /**
     * Método observador que devuelve el identificador de la hebra/vector
     * resultante.
     * 
     * @return <b>int</b> identificador de la hebra/vector resultante.
     */
    public int getIdHebra() {
        return idHebra;
    }

    /**
     * Método observador que devuelve el valor de la variable resultante del
     * producto escalar sobre el rango indicado anteriormente.
     * 
     * @return <b>double</b> Resultado del producto escalar parcial.
     */
    public double getRes() {
        return res;
    }

    /**
     * Método que toma un rango del vector comprendido entre las posiciones inicio y
     * fin de dos vectores de la clase ClasePrincipalEscalar en la forma
     * [inicio,fin) y los multiplica entre sí, guardando el resultado en una
     * variable auxiliar.
     * 
     * @see prodEscalarParalelo
     */
    public void calcular() {
        res = 0;
        for (int i = inicio; i < fin; i++) {
            res = res + prodEscalarParalelo.vec1[i] * prodEscalarParalelo.vec2[i];
        }
    }

    /**
     * Sobrecarga del método run() de la clase Thread que llama al método calcular
     * de la clase prodEscalarParalelo.
     * 
     * @see Java.lang.Thread.run
     */
    public void run() {
        calcular();
    }
}