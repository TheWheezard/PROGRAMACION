public class Usa_tareaRunnable
{
	public static void main (String args[]) throws InterruptedException
	{
		Critica c = new Critica();

		Runnable Hilo1 = new tareaRunnable(c , true);
		Runnable Hilo2 = new tareaRunnable(c , false);

		Thread A = new Thread(Hilo1);
		Thread B = new Thread(Hilo2);

		A.start();
		B.start();

		A.join();
		B.join();
		
		System.out.println("La n vale: "+c.vDato());
	}
}