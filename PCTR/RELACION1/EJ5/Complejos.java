/**
 * Complejos
 * @author Javier Lopez Sierra
 * @precondiciones: debe recibir dos parámetros de tipo double O un array double[] de tamaño 2
 * @postcondicion: crea un Complejo en forma (real, imaginario)
 */
public class Complejos {
    private double[] complejo;
    public Complejos(double real_, double imaginario_){// Constructor doubles
        complejo = new double[2];
        complejo[0] = real_;
        complejo[1] = imaginario_;
    }
    public Complejos(double[] complejo_){// Constructor array double[2]
        assert(complejo_.length == complejo.length);
        complejo = complejo_;
    }
    public void verComplejo() {// muestra complejo por pantalla con formato (a,b)
        System.out.print("(" + complejo[0] + ", " + complejo[1] + ")");
    }
    public double[] getComplejos() {// devuelve array double[] complejo
        return complejo;
    }
    public double[] sumaComplejos(double[] otro_complejo) {// (a,b) + (c,d)
        double[] res = new double[2];
        res[0] = complejo[0] + otro_complejo[0]; // a + c
        res[1] = complejo[1] + otro_complejo[1]; // b + d
        return res;
    }
    public double[] restaComplejos(double[] otro_complejo) {// (a,b) - (c,d)
        double[] res = new double[2];
        res[0] = complejo[0] - otro_complejo[0]; // a - c
        res[1] = complejo[1] - otro_complejo[1]; // b - d
        return res;
    }
    public double[] prodEscalarComplejo(double esc) {// c * (a,b)
        double[] res = new double[2];
        res[0] = complejo[0] * esc; // a * c
        res[1] = complejo[1] * esc; // b * c
        return res;
    }
    public double[] productoComplejos(double[] otro_complejo) {// (a,b) * (c,d)
        double[] res = new double[2];
        res[0] = complejo[0] * otro_complejo[0] - complejo[1] * otro_complejo[1]; // a * c - b * d
        res[1] = complejo[0] * otro_complejo[1] + complejo[1] * otro_complejo[0]; // a * d + b * c
        return res;
    }
    public double[] divisionComplejos(double[] otro_complejo) {// (a,b) / (c,d)
        double[] res = new double[2];
        res[0] = (complejo[0] * otro_complejo[0] + complejo[1] * otro_complejo[1]) / (Math.pow(otro_complejo[0], 2) + Math.pow(otro_complejo[1], 2)); // (ac+bd)/(c^2+d^2)
        res[1] = (complejo[1] * otro_complejo[0] - complejo[0] * otro_complejo[1]) / (Math.pow(otro_complejo[0], 2) + Math.pow(otro_complejo[1], 2)); // (bc-ad)/(c^2+d^2)
        return res;
    }
    public double moduloComplejos() {// |(a,b)|
        return Math.sqrt(Math.pow(complejo[0], 2) + Math.pow(complejo[1], 2)); // sqrt(a^2 + b^2)
    }
}