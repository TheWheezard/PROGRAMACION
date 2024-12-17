public class cuentaCompartida {
    private int saldo;

    public cuentaCompartida(int saldoInicial) {
        this.saldo = saldoInicial;
    }

    public synchronized void ingreso(int cuantia) {
        saldo += cuantia;
        notifyAll();
    }

    public synchronized void reintegro(int cuantia) throws InterruptedException {
        while (saldo < cuantia) {
            wait();
        }
        saldo -= cuantia;
    }

    public synchronized int getSaldo() {
        return saldo;
    }
}