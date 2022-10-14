/** 
 * Hombre
 * @author Javier Lopez Sierra
*/
public class Hombre extends Omnivoro{
    private String dni;

    public Hombre(int edad_, String nombre_, char sexo_, String dni_){
        super(edad_, nombre_, sexo_);
        this.dni = dni_;
    }
    public void mostrarDNI(){
        System.out.println("Su DNI es " + dni + ".");
    }
}
