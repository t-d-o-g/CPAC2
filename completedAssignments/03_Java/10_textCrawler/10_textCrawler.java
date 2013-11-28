import java.util.*;
import java.io.*;

/* Travis Collins
 * 5/6/04
 *
 * I chose to store all of my data in separate hash sets because it has 
 * all the functionality required to store the data efficiently and was
 * reusable.  
*/


public class Crawler
{
   public static void main(String[] args) throws IOException
   {
	ConsoleReader cr = new ConsoleReader(System.in);
	JQueue que = new JQueue();
	File ef = new File("emails.txt");       
        FileWriter efw = new FileWriter(ef);
	PrintWriter epw = new PrintWriter(efw);
	File tf = new File("hashtable.txt");       
        FileWriter tfw = new FileWriter(tf);
	PrintWriter tpw = new PrintWriter(tfw);
	File wf = new File("webpages.txt");       
        FileWriter wfw = new FileWriter(wf);
	PrintWriter wpw = new PrintWriter(wfw);
	HashSet tset = new HashSet();
	HashSet eset = new HashSet();
	HashSet wset = new HashSet();
	String s;

	if (args.length > 1 )
	{
	   System.out.print("Too many arguments.");
	   System.exit(0);
	}
	else if (args.length < 1)
 	{
	   System.out.print("Requires a seed file argument.");
	   System.exit(0);
	}
	  
	que.enqueue(args[0]);
	tset.add(args[0]);
	
	do
	{ 
	   try 
	   { 
	      File seedFile = new File(que.dequeue().toString());
	      FileReader fr = new FileReader(seedFile);
	      StreamTokenizer st = new StreamTokenizer(fr);
	      st.wordChars('!', '@');
       	      int token = 1;
		
	      while(token != StreamTokenizer.TT_EOF)
	      {
 		token = st.nextToken();

		if (token == StreamTokenizer.TT_WORD)
	        {  
		   s = st.sval;
		   if (s.endsWith(".txt"))
		   { 
		      File tempFile = new File(s);
		      if(tempFile.exists())
		      {
			if(!tset.contains(s))
			{
		      	   tset.add(s);
			   que.enqueue(s);
			}
		      }
		      else
		      {
			System.out.println();
		   	System.out.println("  " + tempFile + " does not exist.");
		      }
		   }
		   else if (((s.indexOf(".com") != -1) || (s.indexOf(".edu") != -1) || // 
			(s.indexOf(".mil") != -1) || (s.indexOf(".gov") != -1) ||   //
			(s.indexOf(".org") != -1)) && (s.indexOf('@') != -1))
		   {
		   	if(!eset.contains(s))
		  	{
	  	   	   eset.add(s);
	         	}
		   }
		   else if ((s.indexOf("http://") != -1) || (s.indexOf("www.") != -1))
		   {
			if(!wset.contains(s))
		   	{
		      	   wset.add(s);
		   	}
		   }
		}
	      }
	      fr.close();
    	   }
	   catch (IOException e) 
	   {  System.out.print("  FILE IO ERROR.");
   	      System.exit(0);
	   }
	}
	while(!que.empty_q()); 

	Iterator ti = tset.iterator();
	Iterator ei = eset.iterator();
	Iterator wi = wset.iterator();	
	System.out.println();
      	System.out.println("  Files read:");
        while(ti.hasNext())
        {
           System.out.println("  " + ti.next());
        }
	ti = tset.iterator();
	while(ti.hasNext())
        {
           tfw.write("" + ti.next());
           tpw.println();
        }
	while(ei.hasNext())
        {
           efw.write("" + ei.next());
           epw.println();
        }
	while(wi.hasNext())
        {
           wfw.write("" + wi.next());
           wpw.println();
        }
	System.out.println();
      	System.out.println("  The contents have been printed to separate files.");
	efw.close();
	tfw.close();
	wfw.close();
   }
}

	   	