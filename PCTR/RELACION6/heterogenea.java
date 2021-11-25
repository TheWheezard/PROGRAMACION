/** */
public class heterogenea {
    long n, m;

    public heterogenea() {
        n = m = 0;
    }

    public synchronized void sumN() {
        n++;
    }

    public void sumM() {
        m++;
    }

    public long getN() {
        return n;
    }

    public long getM() {
        return m;
    }
}
