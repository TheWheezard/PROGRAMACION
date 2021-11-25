public class usaheterogenea extends Thread{
    int numVueltas = 10000;
    heterogenea het;

    public usaheterogenea(heterogenea het) {
        this.het = het;
    }

    public void run() {
        for (int i = 0; i < numVueltas; i++) {
            het.sumN();
            het.sumM();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        heterogenea aux = new heterogenea();
        usaheterogenea A = new usaheterogenea(aux);
        usaheterogenea B = new usaheterogenea(aux);
        A.start();
        B.start();
        A.join();
        B.join();
        System.out.println("Variable n = " + aux.getN());
        System.out.println("Variable m = " + aux.getM());
    }
}
