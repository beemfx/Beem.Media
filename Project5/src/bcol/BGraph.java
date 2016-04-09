/* Blaine Myers
CS 2420-002
 
Graph Class
 */

package bcol;


public class BGraph <T> {
   private T[] m_objs;
   private int[][] m_bAdjMatrix;
   private int m_nSize;
   
/* PRE: N/A
POST: Creates a new instance of graph and allocates memory as necessary.
 */
   public BGraph(int nSize) {
      m_objs = (T[]) new Object[nSize];
      m_bAdjMatrix = new int[nSize][nSize];
//Make sure the adjacency matrix is set to infinity.
      for(int i=0; i<nSize; i++){
	 for(int j=0; j<nSize; j++){
	    m_bAdjMatrix[i][j]=Integer.MAX_VALUE;
	 }
      }
      m_nSize=nSize;
   }
   
/* PRE: N/A
POST: Returns the number of nodes in the graph.
 */
   public int size(){
      return m_nSize;
   }
   
/* PRE: Called only internally by shortestPath
POST: returns the minium unvisitted vertex for use
in shortestPath() (see shortestPath below.
 */
   private static int findMin(int[] nVerts, boolean[] bAllowed){
      int min=Integer.MAX_VALUE;
      int index=-1;
      for(int i=0; i<nVerts.length; i++){
	 if(!bAllowed[i] && (nVerts[i]<min)){
	    index=i;
	    min=nVerts[i];
	 }
      }
      if(index!=-1)
	 bAllowed[index]=true;
      
      return index;
   }
/* PRE: 0<= nStart <size().
POST: Returns and array specifying the shortest path from node nStart
to all other nodes, note that if a path includes Integer.MAX_VALUE,
then there is no path.
 */
   public int[] shortestPath(int nStart) throws BColException{
//We need some arrays to store some information.
      int[] nDist = new int[size()];
      int[] nPrev = new int[size()];
      boolean[] bAllowed = new boolean[size()];
      
//Initialze the arrays.
      for(int i=0; i<size(); i++){
	 nDist[i]=Integer.MAX_VALUE;
	 nPrev[i]=-1;
	 bAllowed[i]=false;
      }
//Where we are starting from is always short.
      nDist[nStart]=0;
      
      int nNext=0;
//We'll loop through all the adjacent vertexes, when
//nNext==-1 it means that there are no more close vertexes
//and hence all shortest paths have been found.
      while(nNext!=-1){
//Extract the vertext witht he shortest distance
//that hasn't been visited.
	 nNext=findMin(nDist, bAllowed);
	 if(nNext!=-1){
//Check all the neighbors of that vertex to see
//if there is a shorter path than previously set.
	    int[] n = neighbors(nNext);
	    for(int v: n){
	       int sum = nDist[nNext]+m_bAdjMatrix[nNext][v];
	       if(sum<nDist[v]){
		  nDist[v]=sum;
		  nPrev[v]=nNext;
	       }
	    }
	 }
      }
//nPrev contains the array with shortest paths.
      return nPrev;
   }
   
/* PRE: 0<= n <size()
POST: o is now in the graph at the specified position.
 */
   public void setData(int n, T o) throws BColException{
      if(n<0 || n>=size()) {
	 throw new BColException(
	    "BGraph::setData must set data to a valid location.");
      }
      
      m_objs[n]=o;
   }
   
/* PRE: n1 and n1 must be greater than or equal to 0 and less than size()
POST: An edge is added between the specified nodes, note that this is
not a two way edge, it only links n1 to n2 and not the other way around.  The
weight of the edge defaults to zero.
 */
   public void addEdge(int n1, int n2)throws BColException{
      addEdge(n1, n2, 0);
   }
   
/* PRE: n1 and n2 must be greater than or equal to 0 and less than size().
nWeight >=0 and != Integer.MAX_VALUE.
POST: The edge is added with the specified wieght.
 */
   public void addEdge(int n1, int n2, int nWeight)throws BColException{
      if((n1<0 || n1>size()) || (n2<0 || n2>size()) || (nWeight<0)){
	 throw new BColException(
	    "BGraph::addEdge edge must be at valid location.");
      }
      
      m_bAdjMatrix[n1][n2]=nWeight;
   }
   
/* PRE: n must be >=0 and <size().
POST: The desired vector data is returned.
 */
   public T getData(int n) throws BColException{
      if(n<0 || n>size()){
	 throw new BColException("BRaph::getData not in graph.");
      }
      
      return m_objs[n];
   }
   
/* PRE: n1 and n2 within the range of the graph.
POST: returns the distance between n1 and n2 or Integer.MAX_VALUE if they
are not connected.
 */
   public int distance(int n1, int n2)throws BColException{
      try{
	 return m_bAdjMatrix[n1][n2];
      }catch(ArrayIndexOutOfBoundsException e){
	 throw new BColException("BGraph::distance data not in graph.");
      }
   }
   
/* PRE: n is from 0 to size()
POST: Returns an integer array of the neighbors of n.
 */
   public int[] neighbors(int n) throws BColException{
      if(n<0 || n>size()){
	 throw new BColException(
	    "BGraph::neighbors must get neighbors of a valid node.");
      }
      
//First thing to do is count how many neighbors there are.
      int nCount=0;
      for(int i=0; i<m_nSize; i++){
	 if(m_bAdjMatrix[n][i]!=Integer.MAX_VALUE)
	    nCount++;
      }
      
//Now create the array and store the neighbors.
      int[] nResult = new int[nCount];
      for(int i=m_nSize-1; i>=0 && nCount>=0; i--){
	 if(m_bAdjMatrix[n][i]!=Integer.MAX_VALUE){
	    nResult[--nCount]=i;
	 }
      }
      
      return nResult;
   }
   
/* PRE: N/A
POST: Returns a string representation of the graph using depth first
traversal.
 */
   public String toString(){
//We'll use the depth traversal string option.
      return toStringDepth();
   }
   
/* PRE: N/A
POST: Returns a string rep of the graph is depth first traversal.*/
   public String toStringDepth(){
      String s="";
      try{
//We need a stack to store explorations.
	 BStack <Integer> stack = new BStack<Integer>();
//We need an array to determine what has been explored.
	 boolean[] bExpList = new boolean[m_nSize];
//Make sure the exploredlist is false.
	 for(int i=0; i<m_nSize; i++){
	    bExpList[i]=false;
	 }
	 
//Do the traversal, start with the first node.
	 for(int nNode=0; nNode<m_nSize; nNode++) {
	    if(bExpList[nNode]==false){
//Now to explore the connected nodes.
	       stack.push(nNode);
	       while(!stack.isEmpty()){
//Get the item on the top of the stack
//and process it.
		  int nCurrent=stack.pop();
		  
//We only need to worry about the node if
//we haven't processed it yet (technically
//this check isn't necessary since dublicate
//nodes are never pushed onto the stack.
		  if(!bExpList[nCurrent]){
//Process the node by marking it as processed,
//and doing the process (in this case appending a string)
		     bExpList[nCurrent]=true;
		     s += "" + m_objs[nCurrent] + "\n";
		     
//Get all the neighbors of the node we
//are processessing and push them onto the stack
//in reverse order, so that they can then processed
//on the next iteration.
		     int[] neighbors = neighbors(nCurrent);
		     for(int j=neighbors.length-1; j>=0; j--){
//We'll only push neighbors that haven't
//been processed so there will be no
//duplicates on the stack.
			if(!bExpList[neighbors[j]]){
			   stack.push(neighbors[j]);
			}
		     }
		  }
//Loop back up, and if there is stuff on the stack,
//then there are more nodes to be processed.
	       }
	    }
//Loop back up for any nodes that might not
//have been connected yet.
	 }
	 
      }catch (BColException e){
	 s = "BGraph::toStringDepth: INTERNAL LOGIC ERROR.";
      }
      return s;
   }
   
}
