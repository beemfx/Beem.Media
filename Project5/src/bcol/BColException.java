/* Blaine Myers
   CS 2420-002

   BStackException - an Exception calss for BStack.
*/

package bcol;

public class BColException extends Exception{
   private String m_strError;
   /* POST: Creates a new instance of BStackException */
   public BColException() {
      m_strError="Unknown Error";
   }
   
   /* POST: Creates a new instance of BStackException 
      with str as the error message.*/
   public BColException(String str){
      m_strError=str;
   }
   
   /* POST:Returns a string representation of the error. */
   public String toString(){
      return "BStack ERROR: " + m_strError;
   }
}
