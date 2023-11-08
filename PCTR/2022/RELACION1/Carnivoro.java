/** 
 * Carnivoro
 * @author Javier Lopez Sierra
*/
public class Carnivoro extends Animal{
    public Carnivoro(int edad_, String nombre_, char sexo_){//Constructor
        super(edad_, nombre_, sexo_); //llamada a constructor de Animal
    }
    public void comer(){
        System.out.println("Come carne.");
    }
}
