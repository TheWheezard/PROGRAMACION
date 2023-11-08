/** 
 * Conejo
 * @author Javier Lopez Sierra
*/
public class Conejo extends Herbivoro {
    private String vida; //doméstico o salvaje

    public Conejo(int edad_, String nombre_, char sexo_, String vida_){
        super(edad_, nombre_, sexo_);
        this.vida = vida_;
    }

    public void vida(){
        System.out.println("Es " + vida + ".");
    }
}
