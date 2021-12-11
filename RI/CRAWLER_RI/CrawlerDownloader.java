import java.io.*;
import java.net.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * CrawlerDownloader
 */
public class CrawlerDownloader {
    public static void main(String[] args) {
        String web = new String("/wiki/Natural_language");
        try {
            getURLs(web);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void getURLs(String dirWeb) throws IOException {
        URL web = new URL("https://en.wikipedia.org" + dirWeb);
        URLConnection conectar = web.openConnection();
        BufferedReader br = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String cadURL = new String();

        Pattern patLinksValidos = Pattern.compile(".*href=\"(/wiki/\\w*(?![:])\\w*)\".*"); //comprueba si es un link de interés
        Pattern patWebActual = Pattern.compile(dirWeb); //guarda patrón de web actual
        Pattern patPagPpal = Pattern.compile("/wiki/Main_Page"); //guarda patrón de página principal
        Matcher mat, matWebAct, matWebPpal; // matchers

        File fich = new File("direcciones.txt");
        FileWriter writer = new FileWriter(fich);
        System.out.println("Extrayendo direcciones...");
        while ((cadURL = br.readLine()) != null) {
            mat = patLinksValidos.matcher(cadURL);
            if (mat.matches()) {
                String cad = mat.group(1);
                matWebAct = patWebActual.matcher(cad);
                matWebPpal = patPagPpal.matcher(cad);
                if (!(matWebAct.matches() || matWebPpal.matches())) {
                    writer.write(mat.group(1) + "\n");
                }
            }
        }
        writer.close();
    }
}