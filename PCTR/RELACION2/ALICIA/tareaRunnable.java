public class tareaRunnable implements Runnable
{
	private Critica n;
	private boolean incr = true;
	
	tareaRunnable (Critica n, boolean inc)
	{
		this.n = n;
		this.incr = inc;
	}
	
	public void run () 
	{
		if(incr)
		{
			for(int i=0; i<=1000000; i++)
			{
				n.incremento();
			}
		}
		else
		{
			for(int i=0; i<=1000000; i++)
			{
				n.decremento();
			}
		}
	}
}