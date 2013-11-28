import java.util.*;

public 
class JQueue extends Vector {
   public JQueue(){
   }

   public Object enqueue(Object item)
   {  /**
     * Adds the specified component to the end of this vector
     */
      addElement(item);
      return item;
   }

   public synchronized Object dequeue()
   {
      Object obj;
 
      obj = firstElement();
     /**
     * Removes the first (lowest-indexed) occurrence of the argument 
     * from this vector. 
     */
      removeElement(obj);

      return obj;
   }

   public boolean empty_q()
   {
      return size() == 0;
   }

   public synchronized int search (Object o)
   {
      int i = lastIndexOf(o);

      if(i >= 0)
      {
         return size() - i;
      }
      
      return -1;
   }
   private static final long serialVersionUID = 1224463164541339165L;
}  