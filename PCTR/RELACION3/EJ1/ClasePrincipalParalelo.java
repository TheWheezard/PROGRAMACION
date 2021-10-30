import java.util.Scanner;
import java.text.*;
import java.util.Date;

/**
 * La clase ClasePrincipalParalelo crea dos vectores de tipo double de misma
 * longitud y los divide en partes que se multiplican de forma concurrente
 * mediante el uso de la clase prodEscalarParalelo.
 * 
 * @author Javier López Sierra
 * @see prodEscalarParalelo
 */
public class ClasePrincipalParalelo {
    static double[] vec1 = new double[(int) Math.pow(10, 6)];
    static double[] vec2 = new double[(int) Math.pow(10, 6)];

    public static void main(String[] args) {
        for (int i = 0; i < vec1.length; i++) { // rellenamos vec1 y vec2
            vec1[i] = vec2[i] = Math.random();
        }
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca número de partes en que partir los vectores:");
        int partes = scan.nextInt();
        prodEscalarParalelo[] productos = new prodEscalarParalelo[partes];
        Thread[] hilos = new Thread[partes];
        int j = 0;
        for (int i = 0; i < partes; i++) { // creamos los hilos con los rangos que van a usar
            hilos[i] = productos[i] = new prodEscalarParalelo(i, j, vec1.length * (i + 1) / partes);
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

        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d.setTime(finCronom);
        System.out.println("Cálculo finalizado a las " + df.format(d) + " tras " + (finCronom - inicCronom) + " milisegundos");

        // recuperando resultados de los hilos en el vector productoParcial
        double[] productoParcial = new double[(int) Math.pow(10, 6)];
        int iteradorParcial = 0;
        int i = 0;
        // primer bucle: se ejecuta mientras no lleguemos al final del array productos o de productoParcial
        while (i < productos.length && iteradorParcial < productoParcial.length) {
            System.out.println("Recuperando resultados del hilo " + productos[i].getIdHebra());
            int k = 0;
            // segundo bucle: se ejecuta mientras no lleguemos al final del array interno de productos[i] o de productoParcial
            while (k < productos[i].getTam() && iteradorParcial < productoParcial.length) {
                productoParcial[iteradorParcial] = productos[i].getRes(k);
                k++;
                iteradorParcial++;
            }
            i++;
        }
        scan.close();
        System.out.println("Fin.");
    }
}
