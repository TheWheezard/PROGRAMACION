/** 
 * Animal
 * @author Javier Lopez Sierra
*/

public class Animal{
    private int edad;
    private String nombre;
    private char sexo;

    
    public Animal(int edad_, String nombre_, char sexo_){//Constructor
        this.edad = edad_;
        this.nombre = nombre_;
        this.sexo = sexo_;
    }
    public void describir(){
        System.out.print("Se llama " + nombre + ", tiene " + edad + " años");
        if (sexo == 'm') {
            System.out.println(" y es macho.");
        } else if (sexo == 'f'){
            System.out.println(" y es hembra.");
        } else{
            System.out.println(" y desconocemos su sexo.");
        }
    }
}