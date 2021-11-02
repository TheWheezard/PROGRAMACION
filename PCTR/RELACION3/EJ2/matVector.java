import java.util.Random;
import java.util.Scanner;

public class matVector {
    static int[][] matriz;
    static int[] vector;
    public static void main(String[] args) {
        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca tamaño de vector y matriz:");
        int n = scan.nextInt();
        matriz = new int[n][n];
        vector = new int[n];
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matriz[i][j] = random.nextInt();
            }
            vector[i] = random.nextInt();
            res[i] = 0;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i] += matriz[i][j] * vector[j];
            }
        }

        System.out.println("Fin.");
        scan.close();
    }
}
