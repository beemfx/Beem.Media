/* Blaine Myers
   CS 2420-002
 
   BQueue - Generic Queue for data collections.
 */

package bcol;

public class BQueue <T>{
   protected BList <T> m_listQ;
   
   /* PRE: N/A
      POST: Createa a new instance of BQueue.
    */
   public BQueue() {
      m_listQ = new BList<T>();
   }
   
   /* PRE: N/A
      POST: Returns true if the queue is empty, else false.
    */
   public boolean isEmpty(){
      return m_listQ.isEmpty();
   }
   
   /* PRE: obj != null
      POST: Inserts the specified object in the queue (queues it up)
    */
   public void enqueue(T obj){
      m_listQ.insert(obj);
   }
   
   /* PRE: isEmpty returns false.
      POST: returns the next item from the queue (does not dequeue it though).
    */
   public T next() throws BColException{
      if(m_listQ.isEmpty()){
	 throw new BColException("Queue is empty.");
      }
      return m_listQ.getLast();
   }
   
   /* PRE: isEmpty() returns false.
      POST: REturns the next item to be dequeued then dequeueus that item.
    */
   public T dequeue() throws BColException{
      T obj = next();
      m_listQ.remove(obj);
      return obj;
   }
   
   /* PRE: N/A
      POST: Returns a string representation of the queue.
    */
   public String toString(){
      String s;
      if(m_listQ.isEmpty()){
	 s = "===EMPTY QUEUE===";
      }else{
	 s = "===QUEUE===\n";
	 T obj = m_listQ.getLast();
	 Integer num = 1;
	 while(obj != null){
	    s += num.toString() + ": " + obj.toString() + '\n';
	    obj = m_listQ.getPrev();
	    num++;
	 }
	 s += "===========\n";
      }
      return s;
      //return m_listQ.toString();
   }
}
