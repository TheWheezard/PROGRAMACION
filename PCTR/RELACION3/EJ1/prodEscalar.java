import java.lang.Math;
import java.text.*;
import java.util.Date;

/**
 * La clase prodEscalar multiplica dos vectores de tipo Double y guarda el
 * resultado en el primer vector.
 * 
 * @author Javier López Sierra
 */
public class prodEscalar {
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
        for (int i = 0; i < vec1.length; i++) {
            vec1[i] = vec1[i] * vec2[i];
        }

        long finCronom = System.currentTimeMillis(); // se para el cronometro
        d.setTime(finCronom);
        System.out.println("Cálculo finalizado a las " + df.format(d) + " tras " + (finCronom - inicCronom) + " milisegundos");
        System.out.println("Fin.");
    }
}
