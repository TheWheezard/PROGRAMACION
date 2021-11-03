public class matVectorConcurrente implements Runnable {
    static int[][] matrizCuadrada;
    static int[] matrizB;
    static int[] matRes;
    int filas;

    public matVectorConcurrente(int filas) {
        this.filas = filas;
        matRes = new int[filas];
        matrizCuadrada = new int[filas][filas];
        matrizB = new int[filas];
    }

    public void calcular() {
        int res = 0;
        for (int i = 0; i < matrizB.length; i++) {
            res = res + matrizCuadrada[i][i] * matrizB[i];
        }
    }
    @Override
    public void run() {
        // TODO Auto-generated method stub
        
    }
}
