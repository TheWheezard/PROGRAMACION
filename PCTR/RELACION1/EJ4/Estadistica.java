import java.util.Arrays;
import java.util.Scanner;

/**
 * Estadistica
 * @author Javier Lopez Sierra
 */
public class Estadistica {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Cálculo de parámetros estadísticos.");
        System.out.println("Indique número de valores que se van a introducir:");
        int n = scan.nextInt();
        System.out.println("Introduzca de uno en uno los valores:");
        double valores[] = new double[n];
        for (int i = 0; i < n; i++) { //introducimos valores en el array
            valores[i] = scan.nextDouble();
        }
        boolean check = true;
        while (check) {
            System.out.print("Seleccione una opción:\n 1- Media\n 2- Mediana\n 3- Moda\n 4- Varianza\n 5- Desviación típica\n 0- Salir\n");
            int opcion = scan.nextInt();
            switch (opcion) {
                case 0: check = false;
                    break;
                case 1: System.out.println("La media aritmética es: " + media(valores));
                    break;
                case 2: System.out.println("La mediana es: " + mediana(valores));
                    break;
                case 3: moda(valores);
                    break;
                case 4: System.out.println("La varianza es: " + varianza(valores));
                    break;
                case 5: System.out.println("La desviación típica es: " + desviacion_t(valores));
                    break;
                default: System.out.println("ERROR. Introduce una opción válida.");
                    break;
            } 
        }
        scan.close();
    }

    public static double media(double[] valores) {
        double res = 0;
        for (int i = 0; i<valores.length; i++) {
            res = res + valores[i];
        }
        res = res / valores.length;
        return res;
    }
    
    public static double mediana(double[] valores) {
        double res;
        Arrays.sort(valores);//ordenamos el array de forma ascendente
        if (valores.length % 2 == 0) { //es PAR
            res = (valores[valores.length/2] + valores[(valores.length/2)+1]) / 2; //las fórmulas representan las dos posiciones centrales de un array PAR
        } else { //es IMPAR
            res = valores[(valores.length/2)]; //representa la posición central del array IMPAR
        }
        return res;
    }

    public static void moda(double[] valores) {
        int contMax = 0;
        double valorMax = 0;
        Arrays.sort(valores);//ordenamos el array de forma ascendente
        for (int i = 0; i < valores.length; ++i) {
            int cont = 0; //cont -> veces que sale un valor
            for (int j = 0; j < valores.length; ++j) {
                if (valores[j] == valores[i]) {
                    cont += 1;
                }
            }
            if (cont > contMax) {
                contMax = cont;
                valorMax = valores[i];
            }
        }
        System.out.println("La moda es: " + valorMax + " y se repite " + contMax + " veces.");
    }

    public static double varianza(double[] valores) {
        double m = media(valores);
        double res = 0;
        for (int i = 0; i < valores.length; i++) {
            res += Math.pow(valores[i] - m, 2);
        }
        res = res / valores.length;
        return res;
    }

    public static double desviacion_t(double[] valores) {
        double res = Math.sqrt(varianza(valores));
        return res;
    }
}
