/*
   Blaine Myers
   CS 2420-002
 
   Generic Input Class For Re-Use
 */
package bcol;

import java.io.*;

/* KeyboardInput is a strictly static class so that it's methods
will be available to any classes that need to get input from the
keyboard without explicitely declaring a new KeybaordInput class
for every class that needs it.
 */
public class KBInput {
   //s_KB is a keyboard input class (see declaration)
   //it is used whenever necessary
   //to get input.
   private static final BufferedReader s_KB = new BufferedReader(
	 new InputStreamReader(System.in));
   
   /* PRE: s_KB!=NULL
   POST: One character, as read from the keybarod is returned,
   note that a whole line may be typed in but only the first
   character is returned.
    */
   public static char readChar() {
      char cChar;
      try{
	 String szTemp=s_KB.readLine();
	 cChar=szTemp.charAt(0);
      }catch(IOException e) {
	 System.out.println(
	       "ERROR: Keyboard input error: " + e.toString());
	 cChar=' ';
      }
      return cChar;
   }
   
   /* PRE: s_KB != null)
   POST: Returns the string as inputed by the user, if
   an error occurs the returned return string is set
   to empty ("") and an error message is printed to the screen.
    */
   public static String readLine() {
      String strLine;
      
      boolean bError=false;
      
      if(s_KB==null) {
	 System.out.println(
	       "ERROR: Keyboard was not initialized!");
	 bError=true;
      }
      
      //Attempt to read a line,
      //if the line is successfully read, then that line will
      //be returned.  If an error occured, the user will be
      //shown the error and the return string will be set to
      //("") empty.
      try{
	 if(!bError) {
	    strLine=s_KB.readLine();
	 } else {
	    strLine="";
	 }
      }catch(IOException e){
	 //If the program gets to this point then the
	 //computer is probably
	 //having some serious issues, and the program
	 //may need to be
	 //terminated by the OS.
	 System.out.println(
	       "ERROR: Keyboard input error: " + e.toString());
	 strLine="";
      }
      
      
      return strLine;
   }
   
   /*PRE: s_KB != null
   POST: Returns the double entered by the user.  If the user
   enters an invalid number, the user is prompted to enter
   another number.  The user will continue to be prompted til
   a valid number is entered.
    */
   public static double readDouble() {
      boolean bGotNumber=false;
      double  fNumber=0.0;
      
      do
      {
	 
	 try{
	    
	    fNumber=Double.parseDouble(
		  KBInput.readLine());
	    bGotNumber=true;
	    
	 }catch(NumberFormatException e){
	    System.out.println(
		  "You have entered an invalid number. Try again.");
	 }
	 
      }while(!bGotNumber);
      
      return fNumber;
   }
   
   /*PRE: s_KB!=null, min and max represent the mininum and maximum
   number that will be gotten.
   POST: A  number within the range (inclusive) is returned.
    */
   public static int readNumberRange(int min, int max) {
      boolean bGotNumber=false;
      int nNumber=0;
      
      do
      {
	 try{
	    
	    nNumber=Integer.parseInt(
		  KBInput.readLine(), 10);
	    
	    
	    if( (nNumber>=min) && (nNumber<=max) ) {
	       bGotNumber=true;
	    } else {
	       System.out.println(
		     "Enter a value between " + min + " and " +  max +
		     ". Try again.");
	    }
	    
	    
	 }catch(NumberFormatException e){
	    System.out.println(
		  "You have entered an invalid number.  Try again.");
	    nNumber=0;
	 }
	 
	 
      }while(!bGotNumber);
      
      return nNumber;
   }
}
