/**
 * Esta clase no es funcional, solo guarda una muestra de las 
 * funciones serialize y deserialize para transformar objetos
 * en cadenas String y viceversa.
 *  
 * @author Javier López Sierra
 */
public class Serializer {
    /**
     * Función privada que serializa y transforma un objeto en String.
     * 
     * @param o El objeto que vamos a serializar.
     * @return String serializado del objeto.
     * @throws IOException
     */
    private static String serialize(Serializable o) throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(o);
        oos.close();
        return Base64.getEncoder().encodeToString(baos.toByteArray());
    }

    /**
     * Función privada que deserializa y transforma una cadena String a un tipo
     * Object. Se puede castear al objeto original del que fue serializado. (Usar
     * con cuidado, genera warning)
     * 
     * @param s La cadena que conforma el objeto serializado.
     * @return Object con el objeto deserializado, se puede castear al original.
     * @throws IOException
     * @throws ClassNotFoundException
     */
    private static Object deserialize(String s) throws IOException, ClassNotFoundException {
        byte[] data = Base64.getDecoder().decode(s);
        ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(data));
        Object o = ois.readObject();
        ois.close();
        return o;
    }
}