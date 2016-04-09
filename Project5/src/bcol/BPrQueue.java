/* Blaine Myers
   CS 2420-002
   
   BPrQueue Generic Priority Queue.  Objects must use comparable method.
 */

package bcol;

public class BPrQueue <T extends Comparable> extends BQueue<T>{
   /* PRE: obj!=null
      POST: obj will be inserted in the queue according to priority.
   */
   public void enqueue(T obj) {
      m_listQ.insertInOrder(m_listQ, obj);
   }
}
