/* Blaine Myers
   CS 2420-002
 
   BStack generic stack for reuse.
 */

package bcol;

/* The BStack class containsa BList rather than extending it, to insure
   that BList methods cannot be called on a BStack.
 */
public class BStack <T>{
   private BList<T> m_listStack;
   
   /* PRE: N/A
   POST: Creates a new instance of BStack.
    */
   public BStack() {
      m_listStack=new BList<T>();
   }
   
   /* PRE: N/A
   POST: Returns true if the stack is empty.
    */
   public boolean isEmpty(){
      return m_listStack.isEmpty();
   }
   
   /*PRE: c is a character.
    POST: c is pushed onto the top of the stack.
    */
   public void push(T c) {
      m_listStack.insert(c);
   }
   
   /* PRE: The stack is not empty.
   POST: The object on the top of the stack is removed and returned.
    */
   public T pop() throws BColException{
      T obj=peek();
      m_listStack.remove(obj);
      return obj;
   }
   
   /* PRE: The stack is not empty.
   POST: The object on the top of the stack is returned, but is left on
   the top of the stack.
    */
   public T peek() throws BColException{
      T t=m_listStack.getFirst();
      
      if(t==null){
	 throw new BColException("Empty Stack (Underflow).");
      }
      return t;
   }
   
   /* PRE: N/A
   POST: A string representation of the stack is returned.
    */
   public String toString(){
      return m_listStack.toString();
   }
}


