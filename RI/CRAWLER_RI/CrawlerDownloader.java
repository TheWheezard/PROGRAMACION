import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * CrawlerDownloader
 */
public class CrawlerDownloader {
    static int tamTotal = 15000;
    static int cont = 0;
    static ArrayList<String> colaWeb;
    static LinkedHashSet<String> listaVisitadas;

    public static void main(String[] args) {
        colaWeb = new ArrayList<String>();
        listaVisitadas = new LinkedHashSet<String>();
        ArrayList<String> colaAux = new ArrayList<String>();
        String aux = new String("/wiki/Natural_language");
        // colaWeb.add(aux);
        // String web = new String("/wiki/Natural_language");
        listaVisitadas.add(aux);
        // haremos una primera pasada
        try {
            colaAux = getURLs(aux);
        } catch (IOException e) {
            e.printStackTrace();
        }
        // hacer doble bucle (comprobar num visitadas(comprobar cola))
        while (listaVisitadas.size() <= tamTotal) {
            // comprobamos si ya tenemos los links recogidos
            for (int k = 0; k < colaAux.size(); k++) {
                // en caso de ser nuevos, los añadimos a la cola
                if (!listaVisitadas.contains(colaAux.get(k))) {
                    colaWeb.add(colaAux.get(k));
                    listaVisitadas.add(colaAux.get(k));
                }
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
        for (String string : colaWeb) {
            System.out.println(string);
        }
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

        File fich = new File("direcciones.txt"); // cambiar para crear fichero unico html
        FileWriter writer = new FileWriter(fich);
        // System.out.println("Extrayendo direcciones...");
        while ((cadURL = br.readLine()) != null) {
            mat = patLinksValidos.matcher(cadURL);
            if (mat.matches()) {
                String cad = mat.group(1);
                matWebAct = patWebActual.matcher(cad);
                matWebPpal = patPagPpal.matcher(cad);
                if (!(matWebAct.matches() || matWebPpal.matches())) {
                    colaCandidatos.add(mat.group(1));
                    //writer.write(mat.group(1) + "\n");
                }
            }
        }
        writer.close();
        return colaCandidatos;
    }
}

/**
 * NOTAS:
 * Debo crear una cola que mantenga los links en lugar de volcarlos en ficheros
 * Debo crear un fichero por web para volcar contenido
 * Probar a sacar solo txt
 */