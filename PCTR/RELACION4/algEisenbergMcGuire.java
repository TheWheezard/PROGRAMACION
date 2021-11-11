/** */
public class algEisenbergMcGuire {
    public int n = 0;
    private static volatile int numVueltas = 10000;
    public enum estado {IDLE, WAIT, ACTIVE};
    public estado[] flags;
    int turno;
    int tipoHilo;

    public algEisenbergMcGuire(int tipoHilo) {
        this.tipoHilo = tipoHilo;
    }

    public void run() {
        for (int i = 0; i < numVueltas; i++) {
            
        }
    }
}
