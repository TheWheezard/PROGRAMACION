public class redCajeros {
    public static void main(String[] args) throws InterruptedException {
        cuentaCorriente cuenta = new cuentaCorriente("CUENTA1", 30000);
        Runnable[] depositos = new Runnable[100]; // creamos array de 100 objetos runnable para depósitos (300)
        for (int i = 0; i < depositos.length; i++) {
            depositos[i] = new cajero(cuenta, 1, 3000);
        }

        Runnable[] reintegros = new Runnable[50]; // creamos array de 50 objetos runnable para reintegros (600)
        for (int i = 0; i < reintegros.length; i++) {
            reintegros[i] = new cajero(cuenta, 2, 6000);
        }

        Thread[] operaciones = new Thread[150]; // creamos array de 150 threads
        int i;
        for (i = 0; i < depositos.length; i++) {
            operaciones[i] = new Thread(depositos[i]); // introducimos los objetos runnable de depósito
        }
        for (int j = 0; j < reintegros.length && i < operaciones.length; j++, i++) {
            operaciones[i] = new Thread(reintegros[j]); // introducimos los objetos runnable de reintegro
        }
        // iniciamos los threads
        for (int j = 0; j < operaciones.length; j++) {
            operaciones[j].start();
        }
        for (int j = 0; j < operaciones.length; j++) {
            operaciones[j].join();
        }
        
        // imprimimos el resultado
        System.out.println("La cuenta " + cuenta.verNumCuenta() + " tiene un saldo de " + cuenta.verSaldo() + " €");
    }
}
