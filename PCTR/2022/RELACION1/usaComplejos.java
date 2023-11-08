import java.util.Scanner;

/**
 * usaComplejos
 * 
 * @author Javier Lopez Sierra
 */
public class usaComplejos {
    public static void main(String[] args) {
        boolean check = true;
        Scanner scan = new Scanner(System.in);
        // menu
        System.out.println("Operaciones con complejos.");
        int opcion = 8;
        double real_, imaginario_;
        Complejos operando1, operando2;
        while (check) {
            System.out.print(
                "Elije una operación:\n 1- Suma\n 2- Resta\n 3- Producto Escalar\n 4- Producto (entre complejos)\n 5- División\n 6- Módulo\n\n 0- Salir\n> ");
            opcion = scan.nextInt();
            switch (opcion) {
                case 1: // SUMA
                    System.out.println("Primer complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    System.out.println("Segundo complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando2 = new Complejos(real_, imaginario_);
                    sumar(operando1, operando2);
                    break;
                case 2: // RESTA
                    System.out.println("Primer complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    System.out.println("Segundo complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando2 = new Complejos(real_, imaginario_);
                    restar(operando1, operando2);
                    break;
                case 3: // PRODUCTO ESCALAR
                    System.out.println("Número Complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    System.out.println("Número escalar:");
                    double esc = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    producto_escalar(operando1, esc);
                    break;
                case 4: // PRODUCTO
                    System.out.println("Primer complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    System.out.println("Segundo complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando2 = new Complejos(real_, imaginario_);
                    producto(operando1, operando2);
                    break;
                case 5: // DIVISIÓN
                    System.out.println("Primer complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    System.out.println("Segundo complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando2 = new Complejos(real_, imaginario_);
                    division(operando1, operando2);
                    break;
                case 6: // MÓDULO
                    System.out.println("Número complejo:\n Parte real:");
                    real_ = scan.nextDouble();
                    System.out.println("Parte Imaginaria:");
                    imaginario_ = scan.nextDouble();
                    operando1 = new Complejos(real_, imaginario_);
                    modulo(operando1);
                    break;
                case 0: // SALIR
                    check = false;
                    break;
                default: System.out.println("ERROR. Introduzca una opción disponible.");
                    break;
            }
        }
        scan.close();
    }

    

    private static void sumar(Complejos operando1, Complejos operando2) {
        Complejos solucion = new Complejos(operando1.sumaComplejos(operando2.getComplejos()));
        System.out.println("La solución es: "); 
        solucion.verComplejo();
        System.out.println("");
    }
    
    private static void restar(Complejos operando1, Complejos operando2) {
        Complejos solucion = new Complejos(operando1.restaComplejos(operando2.getComplejos()));
        System.out.println("La solución es: "); 
        solucion.verComplejo();
        System.out.println("");
    }
    
    private static void producto_escalar(Complejos operando1, double esc) {
        Complejos solucion = new Complejos(operando1.prodEscalarComplejo(esc));
        System.out.println("La solución es: "); 
        solucion.verComplejo();
        System.out.println("");
    }
    
    private static void producto(Complejos operando1, Complejos operando2) {
        Complejos solucion = new Complejos(operando1.productoComplejos(operando2.getComplejos()));
        System.out.println("La solución es: "); 
        solucion.verComplejo();
        System.out.println("");
    }
    
    private static void division(Complejos operando1, Complejos operando2) {
        Complejos solucion = new Complejos(operando1.divisionComplejos(operando2.getComplejos()));
        System.out.println("La solución es: "); 
        solucion.verComplejo();
        System.out.println("");
    }

    private static void modulo(Complejos operando1) {
        System.out.println("La solución es: " + operando1.moduloComplejos());
    }



}
