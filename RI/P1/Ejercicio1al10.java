import java.util.regex.*;

/**
 * @Clase Ejercicio 1 al 20
 * 
 * @author Javier Lopez Sierra
 */

public class Ejercicio1al10 {
    public static void ejercicio1(String cadena) {
        System.out.print("Ejercicio 1: ");
        Pattern pat = Pattern.compile("^abc.*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio2(String cadena) {
        System.out.print("Ejercicio 2: ");
        Pattern pat = Pattern.compile("^[aA]bc.*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio3(String cadena) {
        System.out.print("Ejercicio 3: ");
        Pattern pat = Pattern.compile("^[^0-9].*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio4(String cadena) {
        System.out.print("Ejercicio 4: ");
        Pattern pat = Pattern.compile(".*[^0-9]$");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio5(String cadena) {
        System.out.print("Ejercicio 5: ");
        Pattern pat = Pattern.compile("[al]+");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio6(String cadena) {
        System.out.print("Ejercicio 6: ");
        Pattern pat = Pattern.compile(".*2(?!6).*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio7(String cadena) {
        System.out.print("Ejercicio 7: ");
        Pattern pat = Pattern.compile("(?:[a-z]|[A-Z]){5,10}");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio8(String cadena) {
        System.out.print("Ejercicio 8: ");
        Pattern pat = Pattern.compile("^www\\..*\\.es$");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio9(String cadena) {
        System.out.print("Ejercicio 9: ");
        Pattern pat = Pattern.compile(
                "^((0[1-9]|(1|2)[0-9]|3(0|1))/(0(1|3|5|7|8)|1(0|2))|(0[1-9]|(1|2)[0-9]|30)/(0(4|6|9)|11)|(0[1-9]|(1|2)[0-9])/02)/\\d{2}$");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }

    public static void ejercicio10(String cadena) {
        System.out.print("Ejercicio 10: ");
        // pat = Pattern.compile("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
        Pattern pat = Pattern.compile(
                ".*(([1]?[0-9]?\\d)|(2[0-4]{1}\\d)|25[0-5]{1})\\.(([1]?[0-9]?\\d)|(2[0-4]{1}\\d)|25[0-5]{1})\\.(([1]?[0-9]?\\d)|(2[0-4]{1}\\d)|25[0-5]{1})\\.(([1]?[0-9]?\\d)|(2[0-4]{1}\\d)|25[0-5]{1}).*");
        Matcher mat = pat.matcher(cadena);
        if (mat.matches()) {
            System.out.println("ACIERTO");
        } else {
            System.out.println("ERROR");
        }
    }
}
