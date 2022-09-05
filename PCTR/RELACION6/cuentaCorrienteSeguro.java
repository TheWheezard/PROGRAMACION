/**
 * La clase cuentaCorriente emula una cuenta corriente básica con solo número de
 * cuenta, saldo y las opciones para introducir, sacar y comprobar la cantidad
 * de dinero que tiene.
 * 
 * @author Javier López Sierra.
 */
public class cuentaCorrienteSeguro {
    private String numCuenta; // número identificador de la cuenta
    private double saldo; // cantidad de dinero de la cuenta

    /**
     * Constructor de cuentaCorriente.
     * 
     * @param numCuenta String que debe contener el número identificativo de la
     *                  cuenta.
     * @param saldo     Double que debe indicar la cantidad de dinero inicial
     *                  asociada a la cuenta.
     */
    public cuentaCorrienteSeguro(String numCuenta, double saldo) {
        this.numCuenta = numCuenta;
        this.saldo = saldo;
    }

    /**
     * Método modificador que permite añadir saldo a la cuenta. Está protegido con
     * synchronized.
     * 
     * @param cantidad Double que representa la cantidad de dinero que se debe sumar
     *                 al saldo de la cuenta.
     */
    public synchronized void deposito(double cantidad) {
        this.saldo = this.saldo + cantidad;
    }

    /**
     * Método modificador que permite retirar saldo de la cuenta. No tiene en cuenta
     * si hay o no saldo, dado que presuponemos que puede ser negativo. Está
     * protegido con synchronized.
     * 
     * @param cantidad Double que representa la cantidad de dinero que se va a
     *                 restar al saldo actual de la cuenta.
     */
    public synchronized void reintegro(double cantidad) {
        this.saldo = this.saldo - cantidad;
    }

    /**
     * Método observador que devuelve el saldo de la cuenta.
     * 
     * @return Double con la cantidad actual de saldo de la cuenta.
     */
    public double verSaldo() {
        return this.saldo;
    }

    /**
     * Método observador que devuelve el identificador de la cuenta.
     * 
     * @return String con el código que identifica la cadena.
     */
    public String verNumCuenta() {
        return this.numCuenta;
    }
}