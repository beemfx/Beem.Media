/* Blaine Myers
   CS 2420-002
 
   Project 5 - Zoo Graph Demmo
 
   Main - Entry Point and Program Logic
 */

package project5;

import java.io.*;

public class Main {
   private static Zoo s_zoo;
   
   /* PRE: s_zoo initialized.
      POST: Performs menu program logic, and allows exploration of the zoo.
    */
   private static void menuMain(){
      boolean bContinue=true;
      while(bContinue){
	 System.out.println("Options:");
	 System.out.println("1) Show animals");
	 System.out.println("2) Find path");
	 System.out.println("3) Quit");
	 
	 int nChoice = bcol.KBInput.readNumberRange(1, 3);
	 switch(nChoice){
	    case 1:
	       System.out.println(s_zoo);
	       break;
	    case 2:
	       s_zoo.shortestPath();
	       break;
	    case 3:
	       bContinue=false;
	       break;
	 }
      }
   }
   
   /* PRE: Entry
      POST: Exit, all program logic called.
    */
   public static void main(String[] args) throws bcol.BColException{
      s_zoo = new Zoo("zoo_graph.txt");
      menuMain();
   }
   
}
