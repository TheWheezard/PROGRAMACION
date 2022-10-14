/** 
 * Leon
 * @author Javier Lopez Sierra
*/
public class Leon extends Carnivoro{
    String color;
    public Leon(int edad_, String nombre_, char sexo_, String color_){
        super(edad_, nombre_, sexo_);
        color = color_;
    }
    public void color() {
        System.out.println("Su pelaje es de color " + color + ".");
    }
}
