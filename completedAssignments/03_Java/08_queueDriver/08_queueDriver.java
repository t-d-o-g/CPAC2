import java.util.*;

public class QueueDriver
{
   private static void printMenu()
   {
      System.out.println();
      System.out.println("  a)  Initialize the queue.");
      System.out.println("  b)  Add element to the queue. ");
      System.out.println("  c)  Remove element from the queue. ");
      System.out.println("  d)  Check if queue is empty. ");
      System.out.println("  e)  Display all elements in queue. ");
      System.out.println("  f)  Quit ");
   }


   private static void addElement(JQueue que, ConsoleReader cr)
   {
      String s;
      System.out.println();
      System.out.print("  Element: "); 
      que.enqueue(cr.readLine());
   }

   private static void removeElement(JQueue que)
   {  
      if(!que.empty_q())
         System.out.println("  Element removed: "+que.dequeue());
      else
         System.out.println("  Queue is empty."); 
   }

   private static void showAll(JQueue que)
   {
      Iterator it = que.iterator();
      int i = 1;
      if(!que.empty_q())
      {
      while (it.hasNext())
         System.out.println("  " + i++ + ": " + it.next());
      }
      else
        System.out.println("  Queue is empty.");
   }

   public static void main(String[] args)
   {
      JQueue que = null;
      ConsoleReader cr = new ConsoleReader(System.in);

      while(true)
      {  
         try
         {  
            printMenu();
            System.out.println();
            System.out.print("  Make selection: ");
            String choice = cr.readLine();
        
            if(choice.equals("a"))
               que = new JQueue();    
            else if(choice.equals("b"))
               addElement(que, cr);
            else if(choice.equals("c"))
               removeElement(que);
            else if(choice.equals("d") && que.empty_q())
               System.out.println("  Queue is empty.");
            else if(choice.equals("d") && !que.empty_q())
               System.out.println("  Queue is not empty.");
	    else if(choice.equals("e"))
	       showAll(que); 
            else if(choice.equals("f"))
               break;
            else
               System.out.println("  Invalid selection");
          }  
          catch (NullPointerException e)
          {
             System.out.println("  Forgot to initialize the queue?");
          }  
           
       }  
    }
 }

               