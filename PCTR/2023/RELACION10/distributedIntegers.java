import mpi.*;

public class distributedIntegers {
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        // En lugar de calcular el rango de números a comprobar en el proceso 0 y
        // enviarlo a los demás procesos, cada proceso calcula su propio rango.
        int rangeStart = rank * (int) Math.pow(10, 7) / size;
        int rangeEnd = (rank + 1) * (int) Math.pow(10, 7) / size;

        int[] primeCounts = new int[1];
        int[] localPrimeCounts = new int[1];

        if (rank == 0) {
            primeCounts[0] = 0;
        }

        for (int i = rangeStart; i < rangeEnd; i++) {
            if (esPrimo(i)) {
                localPrimeCounts[0]++;
            }
        }

        MPI.COMM_WORLD.Reduce(localPrimeCounts, 0, primeCounts, 0, 1, MPI.INT, MPI.SUM, 0);

        if (rank == 0) {
            System.out.println("Total prime numbers found: " + primeCounts[0]);
        }

        MPI.Finalize();
    }

    private static boolean esPrimo(int num) {
        if (num <= 1) {
            return false;
        }

        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }

        return true;
    }
}
