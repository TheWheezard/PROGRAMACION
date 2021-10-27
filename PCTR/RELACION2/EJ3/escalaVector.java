/**
 * Esta clase creará un array de nuestra clase VectorPrueba y llamará a su
 * método para multiplicarlo de forma secuencial por el escalar.
 * 
 * @author Javier López Sierra
 */
public class escalaVector {

    public static void main(String[] args) {
        VectorPrueba prueba = new VectorPrueba(0, 0); // Llamamos al constructor con ambos parámetros a 0 para recorrer
                                                      // todo el vector
        System.out.println("Calculando resultado");
        prueba.calcular();
    }
}