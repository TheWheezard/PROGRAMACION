import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * CrawlerDownloader
 */
public class CrawlerDownloader {
    public static void main(String[] args) throws IOException {
        URL web = new URL("https://en.wikipedia.org/wiki/Natural_language");
        URLConnection conectar = web.openConnection();
        BufferedReader br = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String cadURL = new String();
        Pattern pat = Pattern.compile(".*(href=\"/wiki/\\w*(?![:])\\w*\").*");
        Pattern pat2 = Pattern.compile(".*https://en.wikipedia.org/wiki/(.*[^:]+.*)");//
        Matcher mat;
        Matcher mat2;
        while ((cadURL = br.readLine()) != null) {
            //System.out.println(cadURL);
            mat = pat.matcher(cadURL);
            if (mat.matches()) {
                System.out.println(mat.group(1));
            }
        }
    }
}