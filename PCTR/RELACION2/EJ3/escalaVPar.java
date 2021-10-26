import java.util.Scanner;

/**
 * Esta clase pedirá al usuario que indique en cuántas partes se deberá dividir
 * el VectorPrueba, y creará los hilos necesarios para hacer las
 * multiplicaciones de diferentes rangos en paralelo
 */
public class escalaVPar {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduzca partes en las que dividir el array");
        int partes = scan.nextInt(); // Indicamos en cuántas partes se va a dividir el array de VectorPrueba
        Runnable[] tareas = new Runnable[partes];
        Thread[] hilos = new Thread[partes];
        int j = 0;
        System.out.println("Creando array runnable");
        for (int i = 0; i < partes; i++) {
            tareas[i] = new VectorPrueba(j, VectorPrueba.vector.length * (i + 1) / partes); // tamVec * (i+1)/partes nos
            j = VectorPrueba.vector.length * (i + 1) / partes;                              // dará el final y principio de cada parte
        }

        System.out.println("Creando array de threads");
        for (int i = 0; i < hilos.length; i++) {
            hilos[i] = new Thread(tareas[i]);
        }

        System.out.println("Iniciando threads del array");
        for (int i = 0; i < hilos.length; i++) {
            hilos[i].start();
        }

        System.out.println("Esperando hilos");
        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Fin ejecución");
        scan.close();
    }
}
