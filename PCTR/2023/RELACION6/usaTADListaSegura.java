import java.util.Scanner;

public class usaTADListaSegura {
    private static int tam = 10;
    public static void main(String[] args) throws InterruptedException {
        int[] lista = new int[tam]; // creamos un array de tamaño tam
        for (int i = 0; i < tam; i++) { // inicializamos el array a 0
            lista[i] = 0;
        }
        TADListaSegura.setLista(lista); // inicializamos la lista
        
        TADListaSegura hSube = new TADListaSegura(0); // sube el valor de res.
        TADListaSegura hBaja = new TADListaSegura(1); // baja el valor de res.
        hSube.start(); // inicia hilo
        hBaja.start();
        hSube.join(); // termina hilo
        hBaja.join();
        lista = TADListaSegura.getLista(); // obtenemos el array de la lista
        for (int i = 0; i < tam; i++) { // imprimimos por pantalla el resultado final de n
            System.out.println("Valor de la lista en la posicion " + i + " = " + lista[i]);
        }
    }
}
