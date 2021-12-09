import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * CrawlerDownloader
 */
public class CrawlerDownloader {
    public static void main(String[] args) {
        String web = new String("https://en.wikipedia.org/wiki/Natural_language");
        try {
            getURLs(web);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void getURLs(String dirWeb) throws IOException {
        URL web = new URL(dirWeb);
        URLConnection conectar = web.openConnection();
        BufferedReader br = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String cadURL = new String();
        Pattern pat = Pattern.compile(".*href=\"(/wiki/\\w*(?![:])\\w*)\".*");
        //Pattern pat2 = Pattern.compile(".*https://en.wikipedia.org/wiki/(.*[^:]+.*)");//
        Matcher mat;
        //Matcher mat2;
        File fich = new File("direcciones.txt");
        FileWriter writer = new FileWriter(fich);
        BufferedWriter bfwriter = new BufferedWriter(writer);
        System.out.println("Extrayendo direcciones...");
        while ((cadURL = br.readLine()) != null) {
            //System.out.println(cadURL);
            mat = pat.matcher(cadURL);
            String cad = "";
            if (mat.matches()) {
                cad = cad + mat.group(1);
                System.out.println(cad);
                //bfwriter.append(cad);
                //bfwriter.newLine();
            }
            bfwriter.write(cad);
        }
    }
}