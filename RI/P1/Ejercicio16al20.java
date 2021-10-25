import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.Normalizer;
import java.text.Normalizer.Form;
import java.util.Scanner;
import java.util.regex.*;

/**
 * @Clase Ejercicio 16 al 20
 * 
 * @author Javier Lopez Sierra
 *
 * @Importante: Cada método/ejercicio crea un fichero resultado que será usado
 * por el siguiente método/ejercicio (ejercicio16 generará un txt que usará ejercicio17, etc)
 */

public class Ejercicio16al20 {
    public static void ejercicio16() {
        System.out.print("Ejercicio 16: ");
        // Crear fichero para guardar resultado
        try {
            File newfich = new File("EjercicioExpresiones16.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }

        Pattern pat = Pattern.compile("[:,\\.;\\?¿¡!…\"\'<<>>]");
        Matcher mat;

        try {
            File fichero = new File("EjercicioExpresiones.txt");
            FileWriter entradafich = new FileWriter("EjercicioExpresiones16.txt");
            Scanner fich = new Scanner(fichero);
            String cadena;
            while (fich.hasNextLine()) {
                cadena = fich.nextLine();
                mat = pat.matcher(cadena);
                cadena = mat.replaceAll(" ");
                // System.out.println(cadena);
                entradafich.write(cadena + "\n");
            }
            entradafich.close();
           
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
    }

    public static void ejercicio17() {
        System.out.print("Ejercicio 17: ");
        // Crear fichero para guardar resultado
        try {
            File newfich = new File("EjercicioExpresiones17.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }

        Pattern pat = Pattern.compile("[\\p{InCombiningDiacriticalMarks}\\p{IsLm}\\p{IsSk}]+");
        Matcher mat;

        try {
            File fichero = new File("EjercicioExpresiones16.txt");
            FileWriter entradafich = new FileWriter("EjercicioExpresiones17.txt");
            Scanner fich = new Scanner(fichero);
            String cadena;
            while (fich.hasNextLine()) {
                // cadena = fich.nextLine();
                cadena = Normalizer.normalize(fich.nextLine(), Form.NFD);
                // System.out.println(cadena);
                mat = pat.matcher(cadena);
                cadena = mat.replaceAll("");
                // System.out.println(cadena);
                entradafich.write(cadena + "\n");
               
            }
            fich = null;
            entradafich.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
    }

    public static void ejercicio18() {
        System.out.print("Ejercicio 18: ");
        // Crear fichero para guardar resultado
        try {
            File newfich = new File("EjercicioExpresiones18.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }

        Pattern pat = Pattern.compile("\\s(\\d)+\\s");
        Matcher mat;

        try {
            File fichero = new File("EjercicioExpresiones17.txt");
            FileWriter entradafich = new FileWriter("EjercicioExpresiones18.txt");
            Scanner fich = new Scanner(fichero);
            String cadena;
            while (fich.hasNextLine()) {
                cadena = fich.nextLine();
                mat = pat.matcher(cadena);
                cadena = mat.replaceAll(" ");
                // System.out.println(cadena);
                entradafich.write(cadena + "\n");
            }
           
            entradafich.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
    }

    public static void ejercicio19() {
        System.out.print("Ejercicio 19: ");
        // Crear fichero para guardar resultado
        try {
            File newfich = new File("EjercicioExpresiones19.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }

        try {
            File fichero = new File("EjercicioExpresiones18.txt");
            FileWriter entradafich = new FileWriter("EjercicioExpresiones19.txt");
            Scanner fich = new Scanner(fichero);
            String cadena;
            while (fich.hasNextLine()) {
                cadena = fich.nextLine();
                cadena = cadena.toUpperCase();
                // System.out.println(cadena);
                entradafich.write(cadena + "\n");
            }
           
            entradafich.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
    }

    public static void ejercicio20() {
        System.out.print("Ejercicio 20: ");
        // Crear fichero para guardar resultado
        try {
            File newfich = new File("EjercicioExpresiones20.txt");
            if (newfich.createNewFile()) {
                System.out.println("Creado fichero: " + newfich.getName());
            } else {
                System.out.println("Fichero ya existe.");
            }
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }

        Pattern pat = Pattern.compile("(\\s){2,}");
        Matcher mat;

        try {
            File fichero = new File("EjercicioExpresiones19.txt");
            FileWriter entradafich = new FileWriter("EjercicioExpresiones20.txt");
            Scanner fich = new Scanner(fichero);
            String cadena;
            while (fich.hasNextLine()) {
                cadena = fich.nextLine();
                mat = pat.matcher(cadena);
                cadena = mat.replaceAll(" ");
                // System.out.println(cadena);
                entradafich.write(cadena + "\n");
            }
           
            entradafich.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error de fichero");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error.");
            e.printStackTrace();
        }
    }
}
