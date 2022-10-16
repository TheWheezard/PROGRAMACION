/**
 * intDefinidaMonteCarlo
 * @author Javier Lopez Sierra
 */
import java.lang.Math;
import java.util.Random;
import java.util.Scanner;

/**
 * <p>La clase {@code intDefinidaMonteCarlo} que, dada una cantidad de puntos a crear, tratará
 * de calcular la integral definida en el rango [0,1] de la función que
 * escojamos previamente. Se ofrece con solo dos funciones:</p>
 *   <p>-- {@code f(x) = sin(x)}</p>
 *   <p>-- {@code f(x) = x}</p>
 * 
 * @author Javier Lopez Sierra
 */
public class intDefinidaMonteCarlo {
    private static int opcion = 0; // variable global privada

    /**
     * Función que permitirá escoger (por teclado) entre dos funciones
     * para calcular su integral definida entre [0,1] por el método Monte-Carlo. A
     * continuación solicitará al usuario la cantidad de puntos aleatorios que se
     * deben crear. Llamará a la función {@link monteCarlo}.
     * 
     * @param args : No se usa.
     * @see #monteCarlo
     */
    public static void main(String[] args) {
        System.out.println("Cálculo de integral definida entre [0-1] mediante método de Monte-Carlo.");
        boolean ok = true;
        Scanner scan = new Scanner(System.in);
        while(ok){
            System.out.print("Elija una función:\n  1- f(x) = sin(x)\n  2- f(x) = x\n");
            opcion = scan.nextInt();
            if (opcion == 1 || opcion == 2){
                ok = false;
            }
            else {
                System.out.println("ERROR, introduzca un valor correcto.");
            }
        }
        
        System.out.println("Introduzca la cantidad de puntos aleatorios que se deben crear:");
        double puntos = scan.nextInt();
        scan.close();
        monteCarlo(puntos);
    }

    /**
     * Función que creará los {@code n} puntos aleatorios indicados por el usuario,
     * y comprobará para cada uno de ellos si se encuentran o no bajo la curva de la
     * función escogida. Devolverá por pantalla el resultado que alcance.
     * 
     * @param n : (<b>double</b>) Cantidad de puntos aleatorios que debe crear la función.
     */
    public static void monteCarlo(double n) {
        double contador_exitos = 0;
        double x, y;
        for (int i = 0; i < n; i++) {
            Random rand = new Random(); // Forma 1 de crear números "aleatorios"
            x = Math.random(); // Forma 2 de crear números "aleatorios"
            y = rand.nextDouble(); // (forma 1-continuación)
            System.out.println("Punto = (" + x + ", " + y + ")");
            if (y <= funcion(x)) {
                contador_exitos += 1;
            }
            System.out.println("Exito = " + contador_exitos);
        }
        double res = contador_exitos / n;
        System.out.println("Integral aproximada: " + res);
    }

    /**
     * Función privada que resuelve la función escogida por el usuario para la ordenada {@code x} de un punto aleatorio.
     * @param x : (<b>double</b>) parámetro para resolver la función.
     * @return <b>double</b> que es resultado de la función que se haya aplicado a {@code x}.
     */
    public static double funcion(double x) {
        if (opcion == 1) {
            return Math.sin(x);
        } else {
            return x;
        }        
    }
}
