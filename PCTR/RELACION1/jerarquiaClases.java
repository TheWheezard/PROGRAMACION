import java.util.Scanner;

/**
 * jerarquiaClases
 * 
 * @author Javier Lopez Sierra
 */
public class jerarquiaClases {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        Scanner scan_nombre = new Scanner(System.in);
        System.out.println("Cree uno de los animales disponibles:\n 1- Leon\n 2- Hiena\n 3- Conejo\n 4- Hombre ");
        int opcion = scan.nextInt();
        System.out.println("Introduzca edad: ");
        int edad_ = scan.nextInt();
        System.out.println("Introduzca nombre: ");
        String nombre_ = scan_nombre.nextLine();
        System.out.println("Indique sexo:\n 1- Masculino\n 2- Femenino");
        int opcion2 = scan.nextInt();
        char sexo_ = 'd'; // desconocido por ahora
        switch (opcion2) {
            case 1:
                sexo_ = 'm'; // macho
                break;
            case 2:
                sexo_ = 'f'; // hembra
                break;
            default:
                break;
        }
        switch (opcion) {
            case 1:
                String color_ = "desconocido";
                System.out.println("Indique el tono de color del pelaje:\n 1- Claro\n 2- Oscuro");
                opcion = scan.nextInt();
                switch (opcion) {
                    case 1:
                        color_ = "claro";
                        break;
                    case 2:
                        color_ = "oscuro";
                        break;
                    default:
                        break;
                }
                Leon leon = new Leon(edad_, nombre_, sexo_, color_);
                leon.describir();
                leon.comer();
                leon.color();
                break;
            case 2:
                String especie_ = "desconocida";
                System.out.println(
                        "Indique la especie a la que pertenece:\n 1- Rayada\n 2- Parda\n 3- Moteada\n 4- Proteles");
                opcion = scan.nextInt();
                switch (opcion) {
                    case 1:
                        especie_ = "rayada";
                        break;
                    case 2:
                        especie_ = "parda";
                        break;
                    case 3:
                        especie_ = "moteada";
                        break;
                    case 4:
                        especie_ = "proteles";
                        break;
                    default:
                        break;
                }
                Hiena hiena = new Hiena(edad_, nombre_, sexo_, especie_);
                hiena.describir();
                hiena.comer();
                hiena.especie();
                break;
            case 3:
                System.out.println("Indique si es:\n 1- Doméstico\n 2- Salvaje");
                String vida_ = "doméstico o salvaje";
                opcion = scan.nextInt();
                switch (opcion) {
                    case 1:
                        vida_ = "doméstico";
                        break;
                    case 2:
                        vida_ = "salvaje";
                        break;
                    default:
                        break;
                }
                Conejo conejo = new Conejo(edad_, nombre_, sexo_, vida_);
                conejo.describir();
                conejo.comer();
                conejo.vida();
                break;
            case 4:
                String dni_ = "000000000";
                System.out.print("Introduzca un DNI: ");
                dni_ = scan_nombre.nextLine();
                System.out.println(".");
                Hombre hombre = new Hombre(edad_, nombre_, sexo_, dni_);
                hombre.describir();
                hombre.comer();
                hombre.mostrarDNI();
                break;

            default:
                break;
        }
        scan.close();
        scan_nombre.close();
    }
}
