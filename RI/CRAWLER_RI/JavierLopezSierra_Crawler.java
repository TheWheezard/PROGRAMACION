import java.io.*;
import java.net.*;
import java.util.*;
import java.util.regex.*;

/**
 * CrawlerDownloader
 */
public class JavierLopezSierra_Crawler {
    static int tamTotal = 7000;
    static int cont = 0;
    static ArrayList<String> colaWeb;
    static LinkedHashSet<String> listaVisitadas;

    public static void main(String[] args) throws IOException {
        System.out.println("Inicio Crawler");
        long inicTiempo = System.nanoTime(); // empezamos cronómetro
        colaWeb = new ArrayList<String>();
        listaVisitadas = new LinkedHashSet<String>();
        ArrayList<String> colaAux = new ArrayList<String>();
        String aux = new String("/wiki/George_Lucas");
        File fich = new File("direcciones.txt"); // observador de direcciones extraídas
        FileWriter writer = new FileWriter(fich);
        listaVisitadas.add(aux);
        // haremos una primera pasada
        try {
            colaAux = getURLs(aux);
        } catch (IOException e) {
            e.printStackTrace();
        }
        // doble bucle (comprobar num visitadas(comprobar cola))
        int contPag = 1;
        while (listaVisitadas.size() < tamTotal) {
            // comprobamos si ya tenemos los links recogidos
            for (int k = 0; k < colaAux.size(); k++) {
                // Si la lista de pags visitadas no ha alcanzado el límite
                if (contPag < tamTotal) {
                    // en caso de ser nuevos, los añadimos a la cola
                    if (!listaVisitadas.contains(colaAux.get(k))) {
                        colaWeb.add(colaAux.get(k));
                        listaVisitadas.add(colaAux.get(k));
                        contPag++;
                    }
                } else {
                    k = colaAux.size();
                }
            }

            colaAux.clear();

            while (!colaWeb.isEmpty()) {    
                // recogemos nuevos links
                ArrayList<String> colaRes = new ArrayList<String>();

                try {
                    colaRes = getURLs(colaWeb.get(0)); 
                } catch (IOException e) {
                    e.printStackTrace();
                }
                colaWeb.remove(0);// colaweb.popFrente

                for (int k = 0; k < colaRes.size(); k++) {
                    colaAux.add(colaRes.get(k));
                }
            }
        }

        for (String string : listaVisitadas) {
            writer.write(string + "\n"); // escribimos la línea en fichero
        }
        writer.close();

        double tiempoTotal = (double) (System.nanoTime() - inicTiempo) / (long) 1.0e9; // fin cronómetro
        System.out.println(listaVisitadas.size() + "\nTiempo: " + tiempoTotal + " segundos");
    }

    public static ArrayList<String> getURLs(String dirWeb) throws IOException {
        ArrayList<String> colaCandidatos = new ArrayList<String>();
        URL web = new URL("https://en.wikipedia.org" + dirWeb);
        URLConnection conectar = web.openConnection();
        BufferedReader br = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String cadURL = new String();

        //Patrones y matchers
        Pattern patLinksValidos1 = Pattern.compile(".*href=\"(/wiki/[\\w\\d#%]*(?![:])[\\w\\d#%]*)\".*"); // comprueba si es un link 
        Pattern patLinksValidos2 = Pattern.compile(".*href=\"(/wiki/(?:[\\w\\d#%]*(?::(?=[_]))[\\w\\d#%]*))\".*"); // de interés
        Pattern patWebActual = Pattern.compile(dirWeb); // guarda patrón de web actual
        Pattern patPagPpal = Pattern.compile("/wiki/Main_Page"); // guarda patrón de página principal
        Matcher mat1, mat2, matWebAct, matWebPpal; // matchers

        String[] nombreDoc = dirWeb.split("/");
        File fich = new File(nombreDoc[2].replace(":", "-") + ".html"); // fichero único nombre_pag.html
        FileWriter writer = new FileWriter(fich);
        while ((cadURL = br.readLine()) != null) {
            mat1 = patLinksValidos1.matcher(cadURL); //toma la cadena
            String cad = new String();
            if (mat1.matches()) {//si es link
                cad = mat1.group(1);
                matWebAct = patWebActual.matcher(cad);
                matWebPpal = patPagPpal.matcher(cad);
                if (!(matWebAct.matches() || matWebPpal.matches())) {
                    colaCandidatos.add(mat1.group(1)); // añadimos a cola de págs
                }
            }
            mat2 = patLinksValidos2.matcher(cadURL); //toma la cadena
            if (mat2.matches()) {//si es link
                cad = mat2.group(1);
                matWebAct = patWebActual.matcher(cad);
                matWebPpal = patPagPpal.matcher(cad);
                if (!(matWebAct.matches() || matWebPpal.matches())) {
                    colaCandidatos.add(mat2.group(1)); // añadimos a cola de págs
                }
            }
            writer.write(cadURL + "\n"); // escribimos la línea en fichero
        }
        writer.close(); // cerrar fichero
        return colaCandidatos;
    }
}