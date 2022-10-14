/**
 * intDefinidaMonteCarlo
 * @author Javier Lopez Sierra
 */
import java.lang.Math;
import java.util.Random;
import java.util.Scanner;


public class intDefinidaMonteCarlo {
    private static int opcion = 0;

    public static void main(String[] args) {
        System.out.println("Cálculo de integral definida entre [0-1] mediante método de Monte-Carlo.");
        System.out.print("Elija una función:\n  1- f(x) = sin(x)\n  2- f(x) = x\n");
        Scanner scan = new Scanner(System.in);
        opcion = scan.nextInt();
        System.out.println("Introduzca la cantidad de puntos aleatorios que se deben crear:");
        double puntos = scan.nextInt();
        monteCarlo(puntos);
        scan.close();
    }
    public static void monteCarlo(double n) {
        double contador_exitos = 0;
        double x, y;
        for (int i = 0; i < n; i++) {
            Random rand = new Random();
            x = Math.random();
            y = rand.nextDouble();
            System.out.println("Punto = (" + x + ", " + y + ")");
            if (y <= funcion(x)) {
                contador_exitos += 1;
            }
            System.out.println("Exito = " + contador_exitos);
        }
        double res = contador_exitos / n;
        System.out.println("Integral aproximada: " + res);
    }
    public static double funcion(double x) {
        if (opcion == 1) {
            return Math.sin(x);
        } else {
            return x;
        }        
    }
}
