import java.lang.Math;

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
        for (int i = 0; i < vec1.length; i++) { // hacemos el producto escalar
            vec1[i] = vec1[i] * vec2[i];
        }
        System.out.println("Fin.");
    }
}
