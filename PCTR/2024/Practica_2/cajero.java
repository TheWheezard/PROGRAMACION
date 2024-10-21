import java.util.Scanner;

/**
 * La clase cajero imita el funcionamiento más básico de un cajero: extraer y
 * depositar dinero en una cuenta bancaria.
 * 
 * @author Javier López Sierra.
 * @see cuentaCorriente
 * @see Runnable
 */
public class cajero implements Runnable {
    private cuentaCorriente cuenta;
    private int operacion = 0;
    private double cantidad = 0;

    /**
     * Constructor de la clase cajero.
     * 
     * @param cuenta    Objeto de tipo cuentaCorriente sobre el que va a operar el
     *                  cajero.
     * @param operacion Entero que indicará la operación a realizar: (1) para
     *                  ingresar dinero. (2) para extraer dinero.
     * @param cantidad  Double que tiene la cantidad de dinero con la que se hará la
     *                  operación.
     */
    public cajero(cuentaCorriente cuenta, int operacion, double cantidad) {
        this.cuenta = cuenta;
        this.operacion = operacion;
        this.cantidad = cantidad;
    }

    /**
     * Método modificador para ingresar dinero en la cuenta.
     * 
     * @param cantidad Double que determina la cantidad de dinero que se va a
     *                 ingresar en la cuenta.
     */
    public void ingresarEnCuenta(double cantidad) {
        cuenta.deposito(cantidad);
    }

    /**
     * Método modificador para extraer dinero de la cuenta.
     * 
     * @param cantidad Double que determina la cantidad de dinero que se va a
     *                 extraer de la cuenta.
     */
    public void extraerDeCuenta(double cantidad) {
        cuenta.reintegro(cantidad);
    }

    /**
     * Método que determina qué operación se va a hacer (ingresar/extraer) y con qué
     * cantidad de dinero.
     * 
     * @param operacion Entero que determina si se ingresa (1) o extrae (2) dinero
     *                  de la cuenta. Por defecto (0) exigirá que se introduzca un
     *                  valor correcto (1 ó 2) y una cantidad de dinero.
     * @param cantidad  Double que determina la cantidad de dinero con la que se
     *                  hará la consecuente operación (ingresar o extraer).
     */
    public void seleccionarOperacion(int operacion, double cantidad) {
        this.operacion = operacion;
        this.cantidad = cantidad;
        switch (operacion) {
        case 1:
            ingresarEnCuenta(cantidad);
            break;
        case 2:
            extraerDeCuenta(cantidad);
            break;
        default:
            Scanner scan = new Scanner(System.in);
            System.out.println("Hace falta indicar una operación válida:\n 1- Ingreso\n 2-Reintegro");
            int op = scan.nextInt();
            System.out.println("y una cantidad de dinero:");
            int cant = scan.nextInt();
            seleccionarOperacion(op, cant);
            break;
        }
    }

    /**
     * Sobrecarga del método run() de la interfaz Runnable
     * 
     * @see Runnable#run()
     */
    public void run() {
        seleccionarOperacion(this.operacion, this.cantidad);
    }
}
