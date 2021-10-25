import java.util.regex.*;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.Normalizer;
import java.text.Normalizer.Form;

class ejercicios_expresiones_regulares
{
	public static void main(String[] args)	
	{
		boolean seguir = true;
		while(seguir)
		{	
			String cadena;
			System.out.println("Introduzca cadena: ");
			Scanner teclado = new Scanner(System.in);
			cadena = teclado.nextLine();
	
			//Ejercicio_1
			Pattern pat = Pattern.compile("^abc.*");
			Matcher mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 1: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 1: incorrecto");
			}

			//Ejercicio 2
			pat = null;
			mat = null;
			pat = Pattern.compile("(a|A)bc.*");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 2: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 2: incorrecto");
			}

			//Ejercicio 3 
			pat = null;
			mat = null;
			pat = Pattern.compile("\\D.*");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 3: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 3: incorrecto");
			}

			//Ejercicio 4
			pat = null;
			mat = null;
			pat = Pattern.compile(".*[^0-9]$");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 4: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 4: incorrecto");
			}

			//Ejercicio 5 
			pat = null;
			mat = null;
			pat = Pattern.compile("^(a|l)+$");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 5: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 5: incorrecto");
			}
	
			//Ejercicio 6 
			pat = null;
			mat = null;
			pat = Pattern.compile(".*2(?!6).*");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 6: correcto");
			}	 	
			else 
			{
				System.out.println("Ejercicio 6: incorrecto");
			}

			//Ejercicio 7
			pat = null;
			mat = null;
			pat = Pattern.compile("([a-z]|[A-Z]){5,10}");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 7: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 7: incorrecto");
			}

			//Ejercicio 8
			pat = null;
			mat = null;
			pat = Pattern.compile("(www\\.).*(\\.es)$");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 8: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 8: incorrecto");
			}
	
			//Ejercicio 9 //Cambiar igual no valido
			pat = null;
			mat = null;
			//pat = Pattern.compile("([0-2][1-9])/(0[1-9])/([0-9][1-9])|([0-2][1-9])/(1[0-2])/([0-9][1-9])|(3[0-1])/(0[1-9])/([0-9][1-9])|(3[0-1])/(1[0-2])/([0-9][1-9])");
			pat = Pattern.compile("(\\d{2})/(\\d{2})/(\\d{2,4})");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 9: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 9: incorrecto");
			}

			//Ejercicio 10  //Cambiar igual no valido
			pat = null;
			mat = null;
			//pat = Pattern.compile ("(.*(([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))[:.:](([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))[:.:](([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))[:.:](([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5])).*)");
			pat = Pattern.compile ("(.*(([0-2]?[0-9]?[0-9])\\.([0-2]?[0-9]?[0-9])\\.([0-2]?[0-9]?[0-9])\\.([0-2]?[0-9]?[0-9])).*)");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 10: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 10: incorrecto");
			}
			
			//Ejercicio 11
			pat = null;
			mat = null;
			pat = Pattern.compile("^\\+34[[0-9]|\\s]{9,11}");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 11: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 11: incorrecto");
			}

			//Ejercicio 12
			pat = null;
			mat = null;
			pat = Pattern.compile("^P\\s(?:[0-9]{6})|^P\\s(?:[0-9]{2}\\-[0-9]{5})|(?:^P\\-[0-9]{2}\\-[0-9]{4})|(?:^P\\#[0-9]{2}\\-[0-9]{4})|(?:^P\\#\\s[0-9]{2}\\s[0-9]{4})");
			//pat = Pattern.compile("(\W|^)po[#\-]{0,1}\s{0,1}\d{2}[\s-]{0,1}\d{4}(\W|$)");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 12: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 12: incorrecto");
			}

			//Ejercicio 13
			pat = null;
			mat = null;
			pat = Pattern.compile(".*v[i!1][@a]gr[a@].*");
			mat = pat.matcher(cadena);

			if (mat.matches()) 
			{
				System.out.println("Ejercicio 13: correcto");
			} 
			else 
			{
				System.out.println("Ejercicio 13: incorrecto");
			}


			//Ejercicio 14 
			System.out.println("EJERCICIO 14: ");
			pat = null;
			mat = null;
			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN14.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile(".*\\<img.*\\>"); 

			//Abrimos el fichero
			try
			{
				File fichero = new File("uca.txt");
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN14.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					mat = pat.matcher(cadena);
					if(mat.matches())
					{	
						entradafich.write(cadena + "\n");
					}
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			//Ejercicio 15
			System.out.println("EJERCICIO 15: ");
			String ej15 = "<a>uno</a><b>dos</b><c>tres</c><d>cuatro</d><e>cinco</e>";

			//Patron 1
			pat = null;
			mat = null;

			pat = Pattern.compile("<[^>]*>([^<]*)</[^>]*>");
			mat = pat.matcher(ej15);

			System.out.println("PATRON 1 sin arreglar: ");
			while (mat.find())
			{
 				System.out.println(mat.group());
			}
/*
			//patron arreglago
			pat = null;
			mat = null;

			pat = Pattern.compile("");
			mat = pat.matcher(ej15);

			System.out.println("PATRON 1 sin arreglar: ");
			while (mat.find())
			{
 				System.out.println(mat.group());
			}*/

			//Patron 2
			pat = null;
			mat = null;

			pat = Pattern.compile("<.*>(.*)<\\/.*>");
			mat = pat.matcher(ej15);

			System.out.println("PATRON 2: ");
			while (mat.find())
			{
 				System.out.println(mat.group());
			}

			//Patron 3
			pat = null;
			mat = null;

			pat = Pattern.compile("<.*?>(.*?)<\\/.*?>");
			mat = pat.matcher(ej15);

			System.out.println("PATRON 3: ");
			while (mat.find())
			{
 				System.out.println(mat.group());
			}


			//Ejercicio 16
			System.out.println("EJERCICIO 16: ");
			pat = null;
			mat = null;

			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN16.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile("[:,\\.;\\?¿\\!¡\'<>\"]"); 

			//Abrimos el fichero
			try
			{
				File fichero = new File("EjercicioExpresiones.txt");
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN16.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					mat = pat.matcher(cadena);
					cadena = mat.replaceAll(" ");
					entradafich.write(cadena + "\n");
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			//Ejercicio 17
			System.out.println("EJERCICIO 17: ");
			pat = null;
			mat = null;

			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN17.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile("[\\p{InCombiningDiacriticalMarks}\\p{IsLm}\\p{IsSk}]+");

			//Abrimos el fichero
			try
			{
				File fichero = new File("EjercicioExpresionesN16.txt");
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN17.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					cadena = Normalizer.normalize(cadena, Form.NFD);
					mat = pat.matcher(cadena);
					cadena = mat.replaceAll("");
					entradafich.write(cadena + "\n");
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			
			//Ejercicio 18
			System.out.println("EJERCICIO 18: ");
			pat = null;
			mat = null;

			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN18.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile("\\s(\\d)+\\s"); 

			//Abrimos el fichero
			try
			{
				File fichero = new File("EjercicioExpresionesN17.txt");
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN18.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					mat = pat.matcher(cadena);
					cadena = mat.replaceAll(" ");
					entradafich.write(cadena + "\n");
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			//Ejercicio 19
			System.out.println("EJERCICIO 19: ");
			pat = null;
			mat = null;

			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN19.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile("[a-z]");

			//Abrimos el fichero
			try
			{
				File fichero = new File("EjercicioExpresionesN18.txt"); //CAMBIAR EL 16 por 18 cuando este
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN19.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					mat = pat.matcher(cadena);
					cadena = mat.replaceAll(x -> x.group().toUpperCase());
					entradafich.write(cadena + "\n");
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			//Ejercicio 20
			System.out.println("EJERCICIO 20: ");
			pat = null;
			mat = null;

			//Creamos un fichero para almaenar el resultado
			try
			{
				File newfich = new File("EjercicioExpresionesN20.txt");
				if(newfich.createNewFile())
				{
					System.out.println("Creado fichero: "+newfich.getName());
				}
				else
				{
					System.out.println("El fichero ya existe.");
				}
			}
			catch (IOException e)
			{
				System.out.println("Error.");
				e.printStackTrace();
			}	

			pat = Pattern.compile("\\s\\s*");

			//Abrimos el fichero
			try
			{
				File fichero = new File("EjercicioExpresionesN19.txt");
				FileWriter entradafich = new FileWriter("EjercicioExpresionesN20.txt");
				Scanner fich = new Scanner(fichero);

				//Vamos haciendo las sustituciones
				while(fich.hasNextLine())
				{
					cadena = fich.nextLine();
					mat = pat.matcher(cadena);
					cadena = mat.replaceAll(" ");
					entradafich.write(cadena + "\n");
				}

				fich = null;
				entradafich.close();
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("Error de fichero.");
				e.printStackTrace();
			}
			catch (IOException e)
			{
				System.out.println("Error de entrada/salida");
				e.printStackTrace();
			}

			System.out.println("Desea introducir una cadena? (s/n)");
			Scanner scan= new Scanner(System.in);
			String cad = teclado.nextLine();
			if(cad.equals("s"))
			{
				teclado = null;
				
				scan = null;
			}
			else
			{
				seguir = false;
				teclado.close();
				scan.close();
			}
			
		}
	}
}