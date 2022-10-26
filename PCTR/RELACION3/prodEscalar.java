import java.lang.Math;
import java.text.*;
import java.util.Date;

/**
 * La clase prodEscalar realiza el producto escalar de dos vectores de tipo
 * Double y guarda el resultado en una variable que muestra por pantalla.
 * 
 * @author Javier López Sierra
 */
public class prodEscalar {
    /**
     * La función main crea dos vectores de tipo <b>double</b> y los inicializa con
     * valores aleatorios. Acto seguido realizaremos el producto escalar de ambos
     * vectores, midiendo el tiempo que tarda en realizarlo. Se imprime por pantalla
     * el resultado de dicho producto, así como fecha, hora y tiempo que se ha
     * tardado.
     * 
     * @param args No se emplea.
     */
    public static void main(String[] args) {
        System.out.println("Iniciando producto escalar secuencial...");
        double[] vec1 = new double[(int) Math.pow(10, 6)]; // declaramos e inicializamos vector 1
        for (int i = 0; i < vec1.length; i++) {
            vec1[i] = Math.random();
        }
        double[] vec2 = new double[(int) Math.pow(10, 6)]; // declaramos e inicializamos vector 2
        for (int i = 0; i < vec2.length; i++) {
            vec2[i] = Math.random();
        }

        /* Mediremos exclusivamente el producto escalar */
        Date d = new Date();
        DateFormat df = new SimpleDateFormat("HH:mm:ss:SSS");
        long inicCronom = System.currentTimeMillis(); // se prepara el cronometro
        d.setTime(inicCronom); // se activa el cronometro

        /* hacemos el producto escalar */
        double res = 0;
        for (int i = 0; i < vec1.length; i++) {
            res = res + vec1[i] * vec2[i];
        }

        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d.setTime(finCronom);
        System.out.println("Calculo finalizado a las " + df.format(d) + " tras " + (finCronom - inicCronom) + " milisegundos");
        System.out.println("Resultado = " + res);
        System.out.println("Fin.");
    }
}
