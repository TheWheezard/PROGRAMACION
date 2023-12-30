import mpi.*;
import java.util.Arrays;

public class escalaMultiple {
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        if (rank == 0) {
            int bufer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            MPI.COMM_WORLD.Bcast(bufer, 0, bufer.length, MPI.INT, 0);

            System.out.println("Vector original: " + Arrays.toString(bufer));

        } else {
            int revbufer[] = new int[10];

            MPI.COMM_WORLD.Bcast(revbufer, 0, revbufer.length, MPI.INT, 0);

            scaleVector(revbufer, rank);
            System.out.println("Proceso slave con ID=" + rank + ": " + Arrays.toString(revbufer));
        }

        MPI.Finalize();
    }

    private static void scaleVector(int[] vector, int scale) {
        for (int i = 0; i < vector.length; i++) {
            vector[i] *= scale;
        }
    }
}

