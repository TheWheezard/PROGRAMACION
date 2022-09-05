import java.util.Random;

/**
 * La clase resImagen realiza la función de resaltado de forma secuencial y nos
 * indica el tiempo que ha tardado en terminar
 * 
 * @author Javier López Sierra
 */
public class resImagen {
    public static void main(String[] args) {
        int n = 30000;
        int[][] matriz = new int[n][n];
        Random ran = new Random();
        // Llenamos la matriz con valores aleatorios entre 0 y 255
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz.length; j++) {
                matriz[i][j] = ran.nextInt() % 255;
            }
        }

        long inicTiempo = System.nanoTime(); // iniciar cuenta de tiempo

        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[i].length; j++) {
                matriz[i][j] = 4 * matriz[i][j];

                if (i + 1 < matriz.length) {
                    matriz[i][j] = matriz[i][j] - matriz[i + 1][j];
                }
                if (i - 1 >= 0) {
                    matriz[i][j] = matriz[i][j] - matriz[i - 1][j];
                }

                if (j + 1 < matriz[i].length) {
                    matriz[i][j] = matriz[i][j] - matriz[i][j + 1];
                }
                if (j - 1 >= 0) {
                    matriz[i][j] = matriz[i][j] - matriz[i][j - 1];
                }

                matriz[i][j] = matriz[i][j] / 8;
            }
        }

        double tiempoTotal = (double) (System.nanoTime() - inicTiempo) / (long) 1.0e9;
        System.out.println("Tiempo: " + tiempoTotal);
    }
}
