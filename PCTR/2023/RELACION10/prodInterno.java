import mpi.*;
import java.util.Arrays;

public class prodInterno {
    static int[] array1 = {1,2,3,4};
    static int[] array2 = {4,3,2,1};
    public static void main(String args[]) throws Exception {
		MPI.Init(args);
		int rank = MPI.COMM_WORLD.Rank();
		int size = MPI.COMM_WORLD.Size();
		int master = 0;
		int slave = 1;
		int tag = 100;
		int unitSize = 4;
		if (rank == master) { // codigo del emisor
			int bufer[] = array1;
			MPI.COMM_WORLD.Send(bufer, 0, unitSize, MPI.INT, slave, tag);
            System.out.println("Emisor ha enviado array1: " + Arrays.toString(bufer));
            bufer = array2;
			MPI.COMM_WORLD.Send(bufer, 0, unitSize, MPI.INT, slave, tag);
            System.out.println("Emisor ha enviado array2: " + Arrays.toString(bufer));

			MPI.COMM_WORLD.Recv(bufer, 0, unitSize, MPI.INT, slave, tag);
			System.out.println("Emisor ha recibido: " + Arrays.toString(bufer));
		} else { // codigo del receptor
			int revbufer[] = new int[4];
            int res[] = new int[4];
			MPI.COMM_WORLD.Recv(revbufer, 0, unitSize, MPI.INT, master, tag);
			System.out.println("Receptor ha recibido array1");
			MPI.COMM_WORLD.Recv(res, 0, unitSize, MPI.INT, master, tag);
            System.out.println("Receptor ha recibido array2");
			int k = 10;
			for (int i = 0; i < revbufer.length; i++)
				res[i] = res[i] * revbufer[i];
			MPI.COMM_WORLD.Send(res, 0, unitSize, MPI.INT, master, tag);
		}
		MPI.Finalize();
	}
}
