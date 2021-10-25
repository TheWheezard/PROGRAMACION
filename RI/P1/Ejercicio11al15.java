import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.regex.*;

/**
 * @Clase Ejercicio 11 al 15
 * 
 * @author Javier Lopez Sierra
 *
 * @Importante: El método/ejercicio 14 crea un fichero de texto con los resultados
 */

public class Ejercicio11al15 {
    public static void ejercicio11(String cadena) {
        System.out.print("Ejercicio 11: ");
        Pattern pat = Pattern.compile("^\\+34956\\d{6}$");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio12(String cadena) {
        System.out.print("Ejercicio 12: ");
        Pattern pat = Pattern.compile("^P(\\s|-|#(\\s)?)\\d{2}(-|\\s)?\\d{4}$");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio13(String cadena) {
        System.out.print("Ejercicio 13: ");
        Pattern pat = Pattern.compile(".*[Vv][iIl!1][aA4@]gr[aA4@].*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }
    /**
     * @return muestra por pantalla un contador con el total y crea un fichero con todas las coincidencias
     */
    public static void ejercicio14() {
        System.out.print("Ejercicio 14: ");
        try { // Crear fichero para las soluciones
            File newfich = new File("Ejercicio14.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
        int cont = 0; // Inicializamos contador de imágenes
        try {
            File fichero = new File("uca.txt");
            FileWriter entrada = new FileWriter("Ejercicio14.txt");
            Scanner fich = new Scanner(fichero);
            Pattern pat = Pattern.compile(".*\\<img.*\\>");
            Matcher mat;
            String cadena;
            while (fich.hasNextLine()) {
                cadena = fich.nextLine();
                mat = pat.matcher(cadena);
                if (mat.matches()) {
                    cont += 1;
                    entrada.write(cadena + "\n");
                }
            }
            fich.close();
            entrada.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
        System.out.println("Total: " + cont);
    }

    public static void ejercicio15() {
        System.out.println("Ejercicio 15: ");
        String cadena = "<a>uno</a><b>dos</b><c>tres</c><d>cuatro</d><e>cinco</e>";
        String[] cadena2;
        // PATRONES REGEX
        Pattern pat = Pattern.compile("<[^>]*>([^<]*)</[^>]*>");
        Pattern pat2 = Pattern.compile("<.*>(.*)<\\/.*>");
        Pattern pat3 = Pattern.compile("<.*?>(.*?)<\\/.*?>");
        Matcher mat;

        // PATRÓN 1
        System.out.println("Pat1:");
        mat = pat.matcher(cadena);
        if (mat.find()) {
            System.out.println(mat.group(1));
        }
        System.out.println("Corrección Pat1:");
        cadena2 = cadena.split("(?<=(</[\\w]>))");// partimos la cadena ...</_>|aquí|<...
        for (String string : cadena2) {
            mat = pat.matcher(string);
            if (mat.matches()) {
                string = mat.group(1);
                System.out.println(string);
            }

        }

        // PATRÓN 2
        System.out.println("Pat2:");
        mat = pat2.matcher(cadena);
        if (mat.matches()) {
            System.out.println(mat.group(1));
        }
        System.out.println("Corrección Pat2:");
        cadena2 = cadena.split("(?<=(</[\\w]>))");
        for (String string : cadena2) {
            mat = pat2.matcher(string);
            if (mat.matches()) {
                string = mat.group(1);
                System.out.println(string);
            }

        }

        // PATRÓN 3
        System.out.println("Pat3:");
        mat = pat3.matcher(cadena);
        if (mat.matches()) {
            System.out.println(mat.group(1));
        }
        System.out.println("Corrección Pat3:");
        cadena2 = cadena.split("(?<=(</[\\w]>))");
        for (String string : cadena2) {
            mat = pat3.matcher(string);
            if (mat.matches()) {
                string = mat.group(1);
                System.out.println(string);
            }

        }
    }
}
