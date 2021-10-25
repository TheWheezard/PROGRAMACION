import java.io.IOException;
import java.util.Scanner;

/**
 * @Clase Practica1
 * @author Javier Lopez Sierra
 * 
 * @modo_de_empleo: Se introduce inicialmente una cadena de texto que se evaluará para TODOS 
 * los ejercicios que requieran una cadena de entrada. El ejercicio 14 y los ejercicios del 16
 * al 20 crean ficheros de texto, recomiendo comentarlos mientras no se evalúan o borrar
 * los ficheros generados cada vez que se haga una prueba, para evitar errores o sobreescrituras
 * 
 */

public class Practica1 {
    public static void main(String[] args) throws IOException {
        boolean test = true;
        String cadena;
        while (test) {
            Scanner scan = new Scanner(System.in);

            System.out.println("Introduzca cadena de texto:");
            cadena = scan.nextLine();

            /* Ejercicios del 1 al 10 */

            // 1-ES 'abc'
            Ejercicio1al10.ejercicio1(cadena);

            // 2-Empieza por 'abc' O 'Abc'
            Ejercicio1al10.ejercicio2(cadena);

            // 3-NO empieza por un dígito
            Ejercicio1al10.ejercicio3(cadena);

            // 4-NO termina por un dígito
            Ejercicio1al10.ejercicio4(cadena);

            // 5-Contiene solo "a" o "l"
            Ejercicio1al10.ejercicio5(cadena);

            // 6-Contiene un 2 y no está seguido por un 6
            Ejercicio1al10.ejercicio6(cadena);

            // 7-Contiene entre 5 y 10 letras mayúsculas o minúsculas
            Ejercicio1al10.ejercicio7(cadena);

            // 8-Es una direccion web española que empieza por 'www'
            Ejercicio1al10.ejercicio8(cadena);

            // 9-Es una fecha en formato dd/mm/yy
            Ejercicio1al10.ejercicio9(cadena);

            // 10-Es una dirección IP xxx.xxx.xxx.xxx
            Ejercicio1al10.ejercicio10(cadena);

            /* Ejercicios del 11 al 15 */

            // 11-Es un teléfono fijo español
            Ejercicio11al15.ejercicio11(cadena);

            // 12-Numero de pedido
            Ejercicio11al15.ejercicio12(cadena);

            // 13-Prevención de spam 'viagra'
            Ejercicio11al15.ejercicio13(cadena);

            // 14-Localizar imágenes en html de uca.es
            Ejercicio11al15.ejercicio14();

            // 15-Extraer contenido de tags de una cadena
            Ejercicio11al15.ejercicio15();

            /* Ejercicios del 16 al 20 */
            //*
            // 16-Eliminar los símbolos (:,.;?¿¡!…”’<<>>) de EjercicioExpresiones.txt
            Ejercicio16al20.ejercicio16();

            // 17-Eliminar las tildes de EjercicioExpresiones16.txt (resultado del 16)
            Ejercicio16al20.ejercicio17();

            // 18-Eliminar los números que no están en palabras de EjercicioExpresiones17.txt (resultado del 17)
            Ejercicio16al20.ejercicio18();

            // 19-Convertir todo el texto en mayúsculas en EjercicioExpresiones18.txt (resultado del 18 )
            Ejercicio16al20.ejercicio19();

            // 20-Eliminar espacios extra en EjercicioExpresiones19.txt (resultado del 19 )
            Ejercicio16al20.ejercicio20();
            // */

            /* Control de aplicación */
            Scanner scann = new Scanner(System.in);
            System.out.println("Repetir? (y/n)");
            String cad = scann.nextLine();
            if (cad.equals("y")) {
                scann = null;
                scan = null;
            } else {
                test = false;
                scan.close();
                scann.close();
            }
        }
    }
}