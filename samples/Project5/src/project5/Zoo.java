/* Blaine Myers
   CS 2420-002
 
   Zoo - class for managing zoo and operating on it.
 */
package project5;

import java.io.*;
import java.util.*;
import bcol.*;

public class Zoo {
   private BGraph<ZVector> m_grphZoo;
   
	/* PRE: strFilename must point to a validly formatted
	 zoo graph filename.
		POST: The zoo is setup and ready for processing.
	 */
   public Zoo(String strFilename){
      try{
	 
	 //BufferedReader fin = new BufferedReader(new File(szFilename));
	 Scanner fin = new Scanner(new File(strFilename), "UTF-8");
	 //The first thing we read is the number of vectors in the zoo,
	 //we can then proceed to create the graph based
	 //on the upcoming information.
	 int nCount = fin.nextInt();
	 //System.out.println("The count: " + nCount);
	 
	 //Read the data and create the graph appropriately.
	 m_grphZoo=new BGraph<ZVector>(nCount);
	 for(int i=0; i<nCount; i++){
	    m_grphZoo.setData(i, new ZVector(fin.next()));
	    for(int j=0; j<nCount; j++){
	       int n = fin.nextInt();
	       if(n!=0)
		  m_grphZoo.addEdge(i, j, n);
	    }
	 }
	 
	 //Test stuff...
	 //System.out.println(m_grphZoo);
	 /*
	 //Prints out all the neighbors...
	 for(int i=0; i<m_grphZoo.size(); i++){
		 ZVector v = m_grphZoo.getData(i);
		 int[] neig = m_grphZoo.neighbors(i);
		 String strNeig = v + ": ";
	  
		 for(int n: neig){
		 strNeig+=m_grphZoo.getData(n) + " ";
		 }
	  
		 System.out.println(strNeig);
	 }
	  */
      }catch (FileNotFoundException e){
	 System.out.println("Could not find " + strFilename);
      }catch (BColException e){
	 System.out.println("A data formating error ocurred " + e);
      }
      
   }
   
	/* PRE: N/A
	POST: Prompts user for two zoo locations and finds the shortest path.
	 */
   public void shortestPath(){
      
      String strPath="";
      try{
	 String strStart, strEnd;
	 int nStart=-1, nEnd=-1;
	 System.out.println("Where do you want to start from?");
	 strStart=KBInput.readLine();
	 System.out.println("Where do you want to end from?");
	 strEnd=KBInput.readLine();
	 
	 //Now that we have the desired infor find the references for those.
	 for(int i=0; (i<m_grphZoo.size()); i++){
	    ZVector v = m_grphZoo.getData(i);
	    if(v.m_strAnimal.compareToIgnoreCase(strStart)==0){
	       nStart=i;
	    }
	    if(v.m_strAnimal.compareToIgnoreCase(strEnd)==0){
	       nEnd=i;
	    }
	 }
	 
	 if(nEnd==-1 || nStart==-1){
	    System.out.println("Invalid animals specified, no path defined.");
	 }else{
	    int[] path = m_grphZoo.shortestPath(nStart);
	    
	    boolean bDone=false;
	    
	    int nDistance=0;
	    while(!bDone){
	       int nDist=m_grphZoo.distance(path[nEnd], nEnd);
	       strPath = String.format(
		  "%s ==> %s %d\n",
		  m_grphZoo.getData(path[nEnd]).m_strAnimal,
		  m_grphZoo.getData(nEnd).m_strAnimal,
		  nDist) + strPath;
	       nDistance+=nDist;
	       if(path[nEnd]==nStart) {
		  bDone=true;
	       }else {
		  nEnd=path[nEnd];
	       }
	    }
	    System.out.println("Results: ");
	    System.out.println(strPath + "\nTotal Distance: " + nDistance);
	    
	 }
	 
      } catch(BColException e){
	 System.out.println("Internal Logic Error:" + e + "\n" + strPath);
      }
   }
   
	/* PRE: N/A
		POST: Returns a string rep of all the animals in the zoo,
	 the graph is traversed in order to show the animals.
	 */
   public String toString(){
      return m_grphZoo.toString();
   }
   
   private class ZVector{
      private String m_strAnimal;
      
      //PRE: strAnimal is the name of the animal.
      //POST: ZVector is created and the name of the animal is et.
      public ZVector(String strAnimal){
	 m_strAnimal = strAnimal;
      }
      
		/* PRE: N/A
	 POST: Returns a string rep of the zoo vector (the animal's name).
		 */
      public String toString(){
	 return m_strAnimal;
      }
   }
}
