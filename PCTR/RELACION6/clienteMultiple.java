import java.net.*;
import java.io.*;

/**
 * La clase clienteMultiple trata de realizar una conexión con un servidor en el
 * puerto 2001 para enviar un valor entero aleatorio varias veces
 * 
 * @author Javier López Sierra
 */
public class clienteMultiple {
    public static void main(String[] args) {
        int i = (int) (Math.random() * 10);
        int puerto = 2001;
        for (int j = 0; j < 16; j++) {
            try {
                System.out.println("Realizando conexion...");
                Socket cable = new Socket("localhost", 2001);
                System.out.println("Realizada conexion a " + cable);
                PrintWriter salida = new PrintWriter(
                        new BufferedWriter(new OutputStreamWriter(cable.getOutputStream())));
                salida.println(i);
                salida.flush();
                System.out.println("Cerrando conexion...");
                cable.close();

            } // try
            catch (Exception e) {
                System.out.println("Error en sockets...");
            }
        }
    }// main
}// Cliente_Hilos
