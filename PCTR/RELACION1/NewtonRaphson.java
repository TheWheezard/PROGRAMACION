import java.lang.Math;
import java.util.Scanner;

/**
 * <p>La clase {@code NewtonRaphson} que, usando el método del mismo nombre,
 * tratará de calcular el valor x para el cual la función f(x) da como resultado
 * el valor 0 (o lo más aproximado posible). Se ofrece con solo dos funciones:<p>
 *   <p>-- {@code f(x) = cos(x)-x^3  en [0,1]}</p>
 *   <p>-- {@code f(x) = x^2-5  en [2,3]}</p>
 * 
 * @author Javier Lopez Sierra
 */
public class NewtonRaphson {
    /**
     * <p>
     * Función que permitirá escoger (por teclado) entre dos funciones para calcular
     * el valor x para el que f(x) se acerca más a 0 por el método de
     * Newton-Raphson.
     * </p>
     * <p>
     * Solicitará al usuario la aproximación inicial y el número máximo de
     * iteraciones. Para la aproximación inicial, debe introducirse un valor que
     * esté dentro del intervalo especificado para la función escogida.
     * </p>
     * 
     * Llamará a la función {@link newtonRaphson}.
     * 
     * @param args : No se usa.
     * @see #newtonRaphson
     */
    public static void main(String[] args) {
        System.out.println("Método de Newton-Raphson");
        System.out.println("Seleccione una ecuación:");
        System.out.println("1) f(x) = cos(x)-x^3  en [0,1]");
        System.out.println("2) f(x) = x^2-5  en [2,3]");
        Scanner scan = new Scanner(System.in);
        int op = scan.nextInt(); //selección de función
        boolean ok = true; //control de entrada correcta
        double x0 = 0.0; //valor de x en la aproximación inicial
        Scanner scanD = new Scanner(System.in);

        while(ok){ // el bucle se termina al introducir los datos de acuerdo a la especificación
            System.out.println("Introduzca aproximación inicial: ");
            x0 = scanD.nextDouble();
            scanD.reset();
            // verificamos qué función escoge y si la aproximación inicial está en el rango
            if ((op == 1 && x0 >= 0.0 && x0 <= 1.0) || (op == 2 && x0 >= 2.0 && x0 <= 3.0)) {
                ok = false;
            } else {
                System.out.println("ERROR, introduzca un valor correcto.");
            }
        }
        System.out.println("Introduzca máximo de iteraciones: ");
        int iteraciones = scan.nextInt();
        scan.close(); scanD.close();
        newtonRaphson(x0, iteraciones);
    }

    /**
     * <p>
     * Función que aplica el método Newton-Raphson a la función escogida
     * anteriormente. De forma iterativa aplica la ecuación:
     * </p>
     * xN1 = xN - f(xN) /
     * f_derivada(xN) .
     * <p>
     * Se imprimirán por pantalla las aproximaciones que se vayan
     * calculando.
     * <p/>
     * 
     * @param x0          : (<b>double</b>) Aproximación inicial. Debe estar dentro
     *                    del intervalo de la función escogida (entre 0 y 1 ó entre
     *                    2 y 3).
     * @param iteraciones : (<b>int</b>) Número de iteraciones total.
     * @see #f(double)
     * @see #f_derivada(double)
     */
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

    /**
     * <p>
     * Función privada que, según el intervalo en el que se encuentre el valor de
     * {@code x} resolverá una de las siguientes funciones:
     * </p>
     * <p>
     * -- {@code f(x) = cos(x)-x^3} si se cumple {@code 0 <= x <= 1}
     * </p>
     * <p>
     * -- {@code f(x) = x^2-5} si se cumple {@code 2 <= x <= 3}
     * </p>
     * 
     * @param x (<b>double</b>) valor de x en la función.
     * @return (<b>double</b>) valor resultante de aplicar f(x).
     */
    private static double f(double x){
        if (x >= 0.0 && x <= 1.0) {
            double res = (Math.cos(x) - Math.pow(x, 3));
            return res;
        } else {
            double res = (Math.pow(x, 2) - 5);
            return res;
        }
    }

    /**
     * <p>
     * Función privada que, según el intervalo en el que se encuentre el valor de
     * {@code x} resolverá una de las siguientes funciones:
     * </p>
     * <p>
     * -- {@code f(x) = (sen(x) * -1) - 3x^2} si se cumple {@code 0 <= x <= 1}
     * </p>
     * <p>
     * -- {@code f(x) = 2x} si se cumple {@code 2 <= x <= 3}
     * </p>
     * 
     * Estas funciones son las funciones derivadas (respectivamente) de las funciones
     * que aparecen en {@link #f(double)}.
     * 
     * @param x (<b>double</b>) valor de x en la función.
     * @return (<b>double</b>) valor resultante de aplicar f(x).
     */
    private static double f_derivada(double x){
        if (x >= 0.0 && x <= 1.0) {
            double res = (Math.sin(x)*-1 - 3 * Math.pow(x, 2));
            return res;
        } else {
            double res = (2 * x);
            return res;
        }
    }
}