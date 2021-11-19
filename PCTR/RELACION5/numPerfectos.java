/**
 * La clase numPerfectos recorre un rango de números entre el 1 y un número
 * recibido por consola y contabiliza cuántos de ellos son perfectos de forma
 * secuencial.
 * 
 * @author Javier López Sierra
 */
public class numPerfectos {
    public static void main(String[] args) {
        long rango = 100000;//Long.parseLong(args[0]);
        int cont = 0;

        long inicTiempo = System.nanoTime(); // empezamos cronómetro
        for (long i = 1; i <= rango; i++) {
            if (esPerfecto(i)) {
                cont += 1;
            }
        }
        double tiempoTotal = (double) (System.nanoTime() - inicTiempo) / (long) 1.0e9; // fin cronómetro
        System.out.println("Encontrados " + cont + " números perfectos en " + tiempoTotal + " segundos");
    }

    /**
     * Función que determina si un número cumple con la condición para considerarse
     * perfecto.
     * 
     * @param num (long) El número que vamos a evaluar.
     * @return Devolvemos si es perfecto (true) o no (false).
     */
    private static boolean esPerfecto(long num) {
        long aux = 0;
        for (long i = 1; i < num; i++) {
            if (num % i == 0) { // si es divisor de num
                aux += i; // lo añadimos a la suma de divisores
            }
        }

        if (aux == num) { // si la suma de divisores equivale a num
            return true; // es perfecto
        } else {
            return false;
        }
    }
}
