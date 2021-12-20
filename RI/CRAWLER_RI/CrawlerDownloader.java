import java.io.*;
import java.net.*;
import java.util.*;
import java.util.regex.*;

/**
 * CrawlerDownloader
 */
public class CrawlerDownloader {
    static int tamTotal = 15000;
    static int cont = 0;
    static ArrayList<String> colaWeb;
    static LinkedHashSet<String> listaVisitadas;

    public static void main(String[] args) throws IOException {
        System.out.println("Inicio Crawler");
        long inicTiempo = System.nanoTime(); // empezamos cronómetro
        colaWeb = new ArrayList<String>();
        listaVisitadas = new LinkedHashSet<String>();
        ArrayList<String> colaAux = new ArrayList<String>();
        //String aux = new String("/wiki/Natural_language");
        String aux = new String("/wiki/Rock_music");
        File fich = new File("direcciones.txt"); // observador de direcciones extraídas
        FileWriter writer = new FileWriter(fich);
        listaVisitadas.add(aux);
        // haremos una primera pasada
        try {
            colaAux = getURLs(aux);
        } catch (IOException e) {
            e.printStackTrace();
        }
        // hacer doble bucle (comprobar num visitadas(comprobar cola))
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
                        System.out.println(listaVisitadas.size() + " " + contPag);
                    }
                } else {
                    k = colaAux.size();
                }
                //System.out.println(listaVisitadas.size());
            }
            colaAux.clear();
            while (!colaWeb.isEmpty()) {    
                // recogemos nuevos links
                ArrayList<String> colaRes = new ArrayList<String>();
                try {
                    colaRes = getURLs(colaWeb.remove(0)); // colaweb.popFrente
                } catch (IOException e) {
                    e.printStackTrace();
                }
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
        System.out.println(listaVisitadas.size() + " " + colaWeb.size() + "\nTiempo: " + tiempoTotal + " segundos");
    }

    public static ArrayList<String> getURLs(String dirWeb) throws IOException {
        ArrayList<String> colaCandidatos = new ArrayList<String>();
        URL web = new URL("https://en.wikipedia.org" + dirWeb);
        URLConnection conectar = web.openConnection();
        BufferedReader br = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String cadURL = new String();

        Pattern patLinksValidos = Pattern.compile(".*href=\"(/wiki/\\w*(?![:])\\w*)\".*"); // comprueba si es un link de
                                                                                           // interés
        Pattern patWebActual = Pattern.compile(dirWeb); // guarda patrón de web actual
        Pattern patPagPpal = Pattern.compile("/wiki/Main_Page"); // guarda patrón de página principal
        Matcher mat, matWebAct, matWebPpal; // matchers

        //String[] nombreDoc = dirWeb.split("/");
        //File fich = new File(nombreDoc[2] + ".html"); // fichero único nombre_pag.html
        //FileWriter writer = new FileWriter(fich);
        while ((cadURL = br.readLine()) != null) {
            mat = patLinksValidos.matcher(cadURL); //toma la cadena
            if (mat.matches()) {//si es link
                String cad = mat.group(1);
                matWebAct = patWebActual.matcher(cad);
                matWebPpal = patPagPpal.matcher(cad);
                if (!(matWebAct.matches() || matWebPpal.matches())) {
                    colaCandidatos.add(mat.group(1)); // añadimos a cola de págs
                    //writer.write(mat.group(1) + "\n");
                }
            }
            //writer.write(cadURL + "\n"); // escribimos la línea en fichero
        }
        //writer.close(); // cerrar fichero
        return colaCandidatos;
    }
}