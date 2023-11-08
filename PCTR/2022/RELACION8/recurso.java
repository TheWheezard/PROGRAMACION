/**
 * La clase <b>recurso</b> ofrece una variable de tipo long y los recursos para
 * modificarla y devolverla.
 * 
 * @author Javier López Sierra
 */
public class recurso {
    private long n;

    /**
     * Constructor de la clase recurso.
     */
    public recurso() {
        n = 0;
    }

    /**
     * La función <b>inc()</b> es un método modificador que incrementa en 1 el valor de la
     * variable interna.
     */
    public void inc() {
        n++;
    }

    /**
     * La función <b>observer()</b> es un método observador que devuelve el valor actual de
     * la variable interna.
     * 
     * @return : valor <b>long</b>
     */
    public long observer() {
        return n;
    }
}
