/** 
 * Hiena
 * @author Javier Lopez Sierra
*/
public class Hiena extends Carnivoro {
    private static String especie;
    public Hiena(int edad_, String nombre_, char sexo_, String especie_){
        super(edad_, nombre_, sexo_);
        especie = especie_;
    }
    public void especie() {
        System.out.println("Es de especie " + especie + ".");
    }
}
