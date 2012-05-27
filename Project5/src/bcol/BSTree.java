/* Blaine Myers
CS 2420-002
 
bcol collection
 */
package bcol;

public class BSTree <T extends Comparable<T>> {
	private BSNode m_nodeRoot;
	/* PRE: N/A
	POST: Creates a new instance of BSTree.
	 */
	public BSTree() {
		m_nodeRoot = null;
	}
	
	/* PRE: obj should be initialized.
	POST: obj is inserted into the search tree.
	 */
	public void insert(T obj){
		//Create a new node to contain the object.
		BSNode nodeNew=new BSNode(obj);
		
		//If the root node is null it means we just insert the new node
		//into the start of the tree.
		if(m_nodeRoot==null){
			m_nodeRoot = nodeNew;
		}else{
			//We'll loop through the nodes, searching left or right, depending
			//on how the node compares, until we find the sport we're looking for
			//then the node is inserted.  We know that we've inserted the node
			//when n is set to null.
			BSNode n = m_nodeRoot;
			while(n!=null){
				//We perform a compareTo for every iteration.
				int nRes=nodeNew.compareTo(n);
				
				if(nRes<0){
					//If less than we go down the left branch.
					if(n.m_nodeLeft==null){
						//If the left node is null then we found the node
						//we're looking for so we need only assign the left node
						//to the new node, and set n to null to break out of the
						//search.
						n.m_nodeLeft=nodeNew;
						n=null;
					} else{
						//If the node was not blank, we set n to the left node
						//to continue the search.
						n=n.m_nodeLeft;
					}
				}else if(nRes>0){
					//if greater than we go down the right branch.
					if(n.m_nodeRight==null){
						//See the algorithm for left node search.
						n.m_nodeRight=nodeNew;
						n=null;
					} else{
						n=n.m_nodeRight;
					}
				}else{
					//Node is already in the tree.  We'll just set n to null to
					//break out of the loop.
					n=null;
				}
			}
			//We're done searching and the node was inserted in the propper
			//location.
		}
	}
	
	/* PRE: obj != null.
	POST: If an object is found int he tree that results in an
	equal comparison to the object specified (that is compareTo()
	reutrns 0, then that object will be removed from the tree.
	If the object was removed true is returned, if no matching
	object is found in the tree false is returned.
	 */
	
	public boolean remove(T obj){
		SearchRes searchRes = findForDelete(obj);
		boolean bRemoved=false;
		if(searchRes==null){
			bRemoved = false;
		}else{
			if(searchRes.m_Parent==null){
				//If we are deleting the root node it is a special case.
				//We know it is the root node because it has no parent.
				m_nodeRoot = deleteNode(searchRes.m_Result);
			}else if(searchRes.m_nResIs==RES_IS.LEFT){
				//When deleting the left node we use the deleteNode method
				//on the result and reasign its parents node to the new tree
				//returned from deleteNode (see method).
				searchRes.m_Parent.m_nodeLeft = deleteNode(searchRes.m_Result);
			}else if(searchRes.m_nResIs==RES_IS.RIGHT){
				//This is a similar procedure to the left node but
				//we asign the new tree to the right node instead of the left
				//one.
				searchRes.m_Parent.m_nodeRight = deleteNode(searchRes.m_Result);
			}else{
				//This case should never have come up.
			}
			bRemoved = true;
		}
		return bRemoved;
	}
	
	/* PRE: nodeDel is a node in the tree and != null.
		POST: the specified node is deleted from the tree, and a new
	 tree representing the tree that replaces the branch of the
	 tree at nodeDel is returned.  The return value should be assigned
	 to the previous trees left or right node accordingly.  (See
	 remove method.)
	 */
	private BSNode deleteNode(BSNode nodeDel){
		BSNode nodeRes = null;
		if(nodeDel.m_nodeLeft==null){
			nodeRes = nodeDel.m_nodeRight;
		}else if(nodeDel.m_nodeRight==null){
			nodeRes = nodeDel.m_nodeLeft;
		}else{
			nodeRes=nodeDel;
			SearchRes searchRes = findLeftMost(nodeRes.m_nodeRight);
			nodeDel.m_object=searchRes.m_Result.m_object;
			if(searchRes.m_Parent != null){
				//System.out.println("Deleting SUB case.");
				searchRes.m_Parent.m_nodeLeft = deleteNode(searchRes.m_Result);
			}else{
				//System.out.println("Deleting STAND case!");
				nodeDel.m_nodeRight = deleteNode(searchRes.m_Result);
			}
		}
		return nodeRes;
	}
	
	/* PRE: nodeStart != null, called only be deleteNode().
		POST: Returns a SearchRes containing the left most node
	 and the parent of the left most node.  If nodeStart was
	 the left most node then the m_Parent attribute of SearchRes
	 will be null.
	 */
	private SearchRes findLeftMost(BSNode nodeStart){
		SearchRes searchRes = new SearchRes();
		
		searchRes.m_Result=nodeStart;
		if(searchRes.m_Result!=null){
			while(searchRes.m_Result.m_nodeLeft!=null){
				searchRes.m_Parent=searchRes.m_Result;
				searchRes.m_nResIs=RES_IS.LEFT;
				searchRes.m_Result=searchRes.m_Result.m_nodeLeft;
			}
		}
		return searchRes;
	}
	
	/* PRE: obj!=null.
		POST: If a matching object was in the tree the Object is
			returned, if not null is returned.
	 */
	public T find(T obj){
		BSNode n = findNode(obj);
		return n==null?null:n.m_object;
	}
	
	/* PRE: obj != null
	POST: If a matching node is found, that node is returned.
	If no matching node is found null is returned.
	 */
	public BSNode findNode(T obj){
		//We'll create a node to hold the obj to help
		//us with the compareTo process.
		BSNode nodeFind = new BSNode(obj);
		boolean bFound=false;
		//Now search through the tree til we find what we want.
		BSNode n = m_nodeRoot;
		while(!bFound && n!=null){
			int nRes = nodeFind.compareTo(n);
			
			if(nRes < 0){
				n = n.m_nodeLeft;
			} else if(nRes>0){
				n = n.m_nodeRight;
			}else {
				bFound=true;
				nodeFind=n;
			}
		}
		
		//If we never found a matching node,
		//then we need to return null.
		if(!bFound)
			nodeFind=null;
		
		return nodeFind;
	}
	
	/* PRE: obj !=null
		POST: Returns a SearchRes if a comparable object was found
	 in the tree.  SearchRes contains the parent node, the result
	 and wether or not the child is the left or right node.
	 */
	private SearchRes findForDelete(T obj){
		SearchRes searchRes = new SearchRes();
		
		//We'll create a node to hold the obj to help
		//us with the compareTo process.
		BSNode nodeFind = new BSNode(obj);
		boolean bFound=false;
		//Now search through the tree til we find what we want.
		BSNode n = m_nodeRoot;
		BSNode nP = null;
		while(!bFound && n!=null){
			int nRes = nodeFind.compareTo(n);
			
			if(nRes < 0){
				searchRes.m_Parent=n;
				searchRes.m_nResIs=RES_IS.LEFT;
				n = n.m_nodeLeft;
			} else if(nRes>0){
				searchRes.m_Parent=n;
				searchRes.m_nResIs=RES_IS.RIGHT;
				n = n.m_nodeRight;
			}else {
				bFound=true;
				searchRes.m_Result=n;
				nodeFind=n;
			}
		}
		
		//If we never found a matching node,
		//then we need to return null.
		if(!bFound)
			searchRes=null;
		
		return searchRes;
	}
	
	/* PRE: N/A
	POST: REturns a string representation of the tree in order from least
	to greatest.
	 */
	public String toString() {
		String retString = "";
		if (m_nodeRoot == null) {
			retString += "The list is empty\n";
		} else {
			retString += "\nHere is the tree--------------\n";
			retString += m_nodeRoot.toStringInOrder("");  //, true);
			retString += "This is the end of the tree---------\n";
		}
		
		return retString;
	}
	
	/* The SearchRes class is for returning valuable
		information for node deletion.*/
	private enum RES_IS{UNKNOWN, LEFT, RIGHT};
	private class SearchRes{
		private SearchRes(){
			m_Parent=null;
			m_Result=null;
			m_nResIs=RES_IS.UNKNOWN;
		}
		private BSNode m_Parent;
		private BSNode m_Result;
		private RES_IS m_nResIs;
	}
	
	//The BSNode holds whatever object the list stores.
	private class BSNode implements Comparable<BSNode>{
		T m_object;
		BSNode m_nodeLeft;
		BSNode m_nodeRight;
		
		/* PRE: N/A
		POST: Creates a new instance of BSNode
		 */
		public BSNode(){
			m_nodeLeft=null;
			m_nodeRight=null;
			m_object=null;
		}
		
		/* PRE: N/A
		POST: Creates a new instance of BSNode containing the
		the specified object.
		 */
		public BSNode(T object){
			m_nodeLeft=null;
			m_nodeRight=null;
			m_object=object;
		}
		
		/* PRE: n is a BSNode.
		POST: Returns integer value in accordance with compareTo
		specifications.
		 */
		public int compareTo(BSNode n){
			return m_object.compareTo(n.m_object);
		}
		
		/* PRE: N/A
		POST: A string representation of the object is returned.
		 */
		public String toString(){
			return m_object.toString();
		}
		
		/* PRE: s is a string to be appended to.
		POST: Appends this node and child nodes strings together
		and returns the new string.  Tranverses child nodes in-order.
		 */
		public String toStringInOrder(String s) {
			if (m_nodeLeft!=null) {
				s = m_nodeLeft.toStringInOrder(s);
			}
			s += m_object + "\n";
			if (m_nodeRight!=null)
				s = m_nodeRight.toStringInOrder(s);
			return s;
		}
		
	}
	
}
