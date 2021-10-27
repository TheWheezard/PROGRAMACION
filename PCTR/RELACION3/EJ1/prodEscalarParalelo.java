/** */
public class prodEscalarParalelo extends Thread {
    static double[] vec1 = new double[(int) Math.pow(10, 6)];
    static double[] vec2 = new double[(int) Math.pow(10, 6)];
    int idHebra, inicio, fin;
    
    public prodEscalarParalelo(int idHebra, int inicio, int fin) {
        this.idHebra = idHebra;
        this.inicio = inicio;
        this.fin = fin;
    }
}
/* continuar desde escalaVPar y VectorPrueba */