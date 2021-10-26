import java.lang.Math;
import java.util.Scanner;

/**
 * NewtonRaphson
 * @author Javier Lopez Sierra
 */
public class NewtonRaphson {
    public static void main(String[] args) {
        System.out.println("Método de Newton-Raphson");
        System.out.println("Seleccione una ecuación:");
        System.out.println("1) f(x) = cos(x)-x^3  en [0,1]");
        System.out.println("2) f(x) = x^2-5  en [2,3]");
        Scanner scan = new Scanner(System.in);
        int op = scan.nextInt();
        boolean ok = true;
        double x0 = 0.0;
        Scanner scanD = new Scanner(System.in);
        while(ok){
            System.out.println("Introduzca aproximación inicial: ");
            x0 = scanD.nextDouble();
            scanD.reset();
            if ((op == 1 && x0 >= 0.0 && x0 <= 1.0) || (op == 2 && x0 >= 2.0 && x0 <= 3.0)) {
                ok = false;
            } else {
                System.out.println("ERROR, introduzca un valor correcto.");
            }
        }
        System.out.println("Introduzca máximo de iteraciones: ");
        int iteraciones = scan.nextInt();
        newtonRaphson(x0, iteraciones);
        scan.close(); scanD.close();
    }
    public static void newtonRaphson(double x0, int iteraciones) {
        double xN1;
        double xN = x0;
        for (int i = 0; i < iteraciones; i++) {
            if (f_derivada(xN) != 0) {
                xN1 = xN - f(xN) / f_derivada(xN);
                System.out.println("Iteración " + (i+1) + ". Valor de x = " + xN + ". Resultado = " + xN1);
                xN = xN1;
            }
        }
    }
    public static double f(double x){
        if (x >= 0.0 && x <= 1.0) {
            double res = (Math.cos(x) - Math.pow(x, 3));
            return res;
        } else {
            double res = (Math.pow(x, 2) - 5);
            return res;
        }
    }
    public static double f_derivada(double x){
        if (x >= 0.0 && x <= 1.0) {
            double res = (Math.sin(x)*-1 - 3 * Math.pow(x, 2));
            return res;
        } else {
            double res = (2 * x);
            return res;
        }
    }
    
}