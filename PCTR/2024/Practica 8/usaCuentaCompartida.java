public class usaCuentaCompartida implements Runnable {
    private static cuentaCompartida cuenta;
    private boolean esIngreso;

    public usaCuentaCompartida(boolean esIngreso) {
        this.esIngreso = esIngreso;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10000; i++) {
            if (esIngreso) {
                cuenta.ingreso(100); // Ingresar 100 unidades
            } else {
                try {
                    cuenta.reintegro(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } // Retirar 50 unidades
            }
        }
    }

    public static void main(String[] args) {
        cuenta = new cuentaCompartida(1000); // Valor inicial de la cuenta

        Thread hilo1 = new Thread(new usaCuentaCompartida(true));
        Thread hilo2 = new Thread(new usaCuentaCompartida(false));
        Thread hilo3 = new Thread(new usaCuentaCompartida(true));
        Thread hilo4 = new Thread(new usaCuentaCompartida(false));

        hilo1.start();
        hilo2.start();
        hilo3.start();
        hilo4.start();

        try {
            hilo1.join();
            hilo2.join();
            hilo3.join();
            hilo4.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Saldo final: " + cuenta.getSaldo());
    }
}
