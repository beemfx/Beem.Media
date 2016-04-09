/*
 Blaine Myers
 CS 2420-002
 
 Generic Linked List Class For Re-Use
 */

package bcol;

public class BList <T>{
   private BListNode<T> m_nodeFirst;
   private BListNode<T> m_nodeLast;
   private BListNode<T> m_nodeLastGotten;
   
   /* BList() (Constructor)
   PRE: N/A
   POST: BList is constructed and ready for use, the
   list is empty.
    */
   public BList() {
      m_nodeFirst=null;
      m_nodeLast=null;
      m_nodeLastGotten=null;
   }
   
   /* PRE: Objects should have been inserted into the list.
   POST: The first item in the list is returned, or null is returned
   if there was no first item.
    */
   public T getFirst(){
      m_nodeLastGotten=m_nodeFirst;
      return m_nodeFirst==null?null:m_nodeFirst.m_Object;
   }
   
   /* PRE: Objects are in the list.
   POST: The last item in the list is returned, or null if there is
   no items in the list.
    */
   public T getLast(){
      m_nodeLastGotten=m_nodeLast;
      return m_nodeLast==null?null:m_nodeLast.m_Object;
   }
   
   /* PRE: getFirst should have been called at some point.
   POST: returns the next node in line since that last node that
   wast gotten (whether that nod was gotten from getFirst, or
   from a previous call to getNext.  If we reached the end of the
   list, or if getFirst had never been called, null is returned.
    */
   public T getNext(){
      T obj=null;
      
      if(m_nodeLastGotten!=null){
	 m_nodeLastGotten=m_nodeLastGotten.m_Next;
      }
      
      if(m_nodeLastGotten!=null){
	 obj=m_nodeLastGotten.m_Object;
      }else {
	 obj=null;
      }
      return obj;
   }
   
   /* PRE: getFirst should have been called at some point.
   POST: returns the previous node in line since that last node that
   wast gotten (whether that nod was gotten from getFirst, or
   from a previous call to getNext.  If we reached the end of the
   list, or if getLast had never been called, null is returned.
    */
   public T getPrev(){
      T obj = null;
      
      if(m_nodeLastGotten!=null){
	 m_nodeLastGotten=m_nodeLastGotten.m_Prev;
      }
      
      if(m_nodeLastGotten!=null){
	 obj=m_nodeLastGotten.m_Object;
      }else{
	 obj=null;
      }
      
      return obj;
   }
   
   /* PRE: obj != NULL
   POST: If a matching object is found in the list then the matching object
   is returned. If no matching object is found null is returned.
    
   Note that the Object.equals method is used to compare nodes,
   objects must determine how the equals method will compare them.
   In some cases it will only compare references.
    */
   public T findSimilar(T obj) {
      T objResult=null;
      
      //Loop through the list, or until we find the result we want.
      for(BListNode<T> n=m_nodeFirst; (n!=null) && objResult==null; n=n.m_Next) {
	 if(n.m_Object.equals(obj)) {
	    objResult=n.m_Object;
	 }
      }
      
      //Note that if no matching node was found objResult will still be
      //set to null.
      return objResult;
   }
   
      /*PRE: n/a
      POST: Retrns true if the list is empty.
       */
   public boolean isEmpty() {
      return m_nodeFirst==null?true:false;
   }
   
   /* PRE: obj is similar to a node that is to be removed.
   POST: If a node can be found that is similar to node, that node
   will be removed from the list and true is returned.  If no node
   was found, then false is returned.
    */
   public boolean removeSimilar(T obj) {
      //To remove a similar node we need only find a similar node
      //then pass that node to the remove method.  Note that remove
      //handles the node if it is null so it doesn't matter if we find
      //a node or get a null reference.
      obj=findSimilar(obj);
      return remove(obj);
   }
   
   /* PRE: obj, should be an object that is actually in the list.
   POST: If the object was in the list, the node containing it is returned.
   if not, null is returned.  Only to be called internally by the list.
    */
   private BListNode findNode(T obj){
      BListNode node=null;
      
      for(BListNode n=m_nodeFirst; n!=null && node==null; n=n.m_Next){
	 if(obj==n.m_Object){
	    node=n;
	 }
      }
      
      return node;
   }
   /* PRE: node is a node in the list.
   POST: If the node was in the list it will be removed and true
   will be returned.  If the node was null or was not in the list
   false will be returned.
    */
   public boolean remove(T obj) {
      boolean bRemoved=false;
      
      BListNode node=findNode(obj);
      
      if(node==null) {
	 bRemoved=false;
      } else if(node==m_nodeFirst) {
	 //If we are removing the first node we are dealing with a special
	 //case.
	 m_nodeFirst=node.m_Next;
	 
	 //If first node was the last node then we also need to set
	 //m_nodeLast to null.
	 if(m_nodeFirst==null) {
	    m_nodeLast=null;
	 } else {
	    //Make sure the first node's prev is null.
	    m_nodeFirst.m_Prev=null;
	 }
	 
	 bRemoved=true;
      } else if(node==m_nodeLast) {
	 //The last node is a special case, but we know it isn't the only
	 //node in the list because that would have been checked above.
	 m_nodeLast=m_nodeLast.m_Prev;
	 m_nodeLast.m_Next=null;
	 bRemoved=true;
      } else {
	 //If the node in the list has no previous
	 //and it wasn't the first node (see above)
	 //then the the node isn't in the list and hsould
	 //have never been passed to this method.
	 if((node.m_Prev!=null) && (node.m_Next!=null)) {
	    node.m_Prev.m_Next=node.m_Next;
	    node.m_Next.m_Prev=node.m_Prev;
	    bRemoved=true;
	 }
      }
      
      return bRemoved;
   }
   
   /* PRE: hasNext()
      POST: Returns true if getNext() will return a non null pointer.
    */
   public boolean hasNext(){
      boolean bResult=false;
      if(m_nodeLastGotten==null)
	 bResult=true;
      else
	 bResult=m_nodeLastGotten.m_Next==null?false:true;
      
      return bResult;
   }
   
   public static <T extends Comparable<T>> void insertInOrder(BList<T> list, T obj){
      //If we are dealing with a node that is previous to the first node, then we
      //have a special case.
      if((list.m_nodeFirst==null) || (obj.compareTo(list.m_nodeFirst.m_Object)<=0)) {
	 list.insert(obj);
      }else{
	BListNode<T> nodeNew=new BListNode<T>(obj);
	BListNode<T> n = null;
	boolean bFound=false;
	for(n=list.m_nodeFirst; !bFound; n=n.m_Next){
	 //If we got to the end of the list then insert
	 //the new node at the end.
	 if(n.m_Next==null){
	    n.m_Next=nodeNew;
	    nodeNew.m_Prev=n;
	    nodeNew.m_Next=null;
	    list.m_nodeLast=nodeNew;
	    bFound=true;
	 }else if(n.m_Next.m_Object.compareTo(obj)>=0){
	    //If the next node is greater than the node we want
	    //to insert then we proceed to insert the node into the
	    //list.  Note that we don't need to worry about n because
	    //that case was taken care of on the previous iteration,
	    //or in the case that the first node was greater as in the
	    //case at the beginning of this method.
	    nodeNew.m_Next=n.m_Next;
	    nodeNew.m_Prev=n;
	    n.m_Next.m_Prev=nodeNew;
	    n.m_Next=nodeNew;
	    bFound=true;
	 }
	}
      }  
   }
   
   /*PRE: obj != null
   POST: The object is inserted at the beginning of the list.
    */
   public void insert(T obj) {
      
      if(obj==null){
	 throw new IllegalArgumentException(
	    "BList ERROR: Cannot insert null objects.");
      }
      
      //Create a new node containing the object.
      BListNode node=new BListNode(obj);
      
      //Then insert it into the list.
      //If there are currently no nodes in the list we need to do
      //a few special things.
      if(m_nodeFirst==null) {
	 m_nodeLast=m_nodeFirst=node;
	 node.m_Prev=null;
	 node.m_Next=null;
      } else {
	 //Set the new nodes next to the current first node.
	 node.m_Next=m_nodeFirst;
	 m_nodeFirst.m_Prev=node;
	 //Reasign the reference of the first node, in this way
	 //the new node is added to the beginning of the list.
	 m_nodeFirst=node;
      }
   }
   
   /* PRE: N/A
   POST: A string is generated containing string representations of all
   the items in the list.  Each item in the list is succeeded by a
   newline ('\n') character.  If there is no items in the list the
   string "EMPTY LIST\n is returned.
    */
   public String toString() {
      String strList="";
      
      if(m_nodeFirst==null) {
	 strList = "=== EMPTY LIST ===\n";
      } else {
	 strList = "=== LIST ===\n";
	 
	 //Loop through each node in the list until we reach a null node
	 //(the end of the list) and for each node in the list add its string
	 //representation to strList plus a newline character (\n).
	 for(BListNode node=m_nodeFirst; node!=null; node=node.m_Next) {
	    strList += node + "\n";
	 }
	 
	 strList += "=== END LIST ===\n";
      }
      
      return strList;
   }
   
   
   
   //The node class holds objects inserted into the list.
   private static class BListNode <T>{
      //Member variables.
      protected T m_Object;
      protected BListNode<T> m_Next;
      protected BListNode<T> m_Prev;
      
      /* BListNode() (Constructor)
      PRE: N/A
      POST: BListNode is initialized.
       */
      public BListNode() {
	 m_Next=null;
	 m_Prev=null;
	 m_Object=null;
      }
      
      /* PRE: obj != null
      POST: BListNode is initialized with the object it contains set. */
      public BListNode(T obj){
	 m_Object=obj;
	 m_Next=null;
	 m_Prev=null;
      }
      
      /* PRE: N/A
      POST: A string representation of the node is returned.
       */
      public String toString(){
	 return m_Object.toString();
      }
   }
}
