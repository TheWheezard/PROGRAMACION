public class TADListaSegura extends Thread {
    private static int[] lista;
    public static Object lock = new Object();
    private int option;
    private int vueltas = 1000000;

    public TADListaSegura(int option) {
        this.option = option;
    }

    public synchronized static int[] getLista() {
        return lista;
    }

    public synchronized static void setLista(int[] lista) {
        TADListaSegura.lista = lista;
    }

    public synchronized void insert(int pos, int valor) {
        lista[pos] = valor;
    }

    public synchronized int get(int pos) {
        return lista[pos];
    }

    @Override
    public synchronized void run() {

        switch (option) {
            case 0:
                for (int i = 0; i < vueltas; i++) { 
                    synchronized (lock) { 
                        int pos = i % lista.length; // ensure index is within bounds
                        insert(pos, get(pos) + 1); 
                    } 
                    // synchronized (lock) { 
                    //     int pos = i % lista.length; // ensure index is within bounds
                    //     System.out.println("1.Valor de la lista en la posición " + pos + " = " + get(pos)); 
                    // }
                }

                break;
                case 1:
                for (int i = 0; i < vueltas; i++) { 
                    synchronized (lock) { 
                        int pos = i % lista.length; // ensure index is within bounds
                        insert(pos, get(pos) - 1); 
                    } 
                    // synchronized (lock) { 
                    //     int pos = i % lista.length; // ensure index is within bounds
                    //     System.out.println("1.Valor de la lista en la posición " + pos + " = " + get(pos)); 
                    // }
                }

                break;
                default:
                System.out.println("Operación no válida");
                break;
        }
    }
}

