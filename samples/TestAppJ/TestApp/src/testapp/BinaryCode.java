/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

public class BinaryCode
{

	public static String m_strIn = "";

	public static String[] decode(String strIn)
	{
		//Begin by converting the string into an array of integers.
		final int n = strIn.length();
		int[] anC = new int[n];
		for (int i = 0; i < n; i++)
		{
			anC[i] = strIn.charAt(i) - '0';
		}

		//Create an array for the outputs.
		int[] anD0 = new int[n];
		int[] anD1 = new int[n];

		//Predict the starting value.
		anD0[0] = 0;
		anD1[0] = 1;

		//the second number should be handled manually.
		anD0[1] = anC[0] - anD0[0];
		anD1[1] = anC[0] - anD1[0];

		boolean b0 = (anD0[1] | 1) == 1;
		boolean b1 = (anD1[1] | 1) == 1;

		for (int i = 2; i < n; i++)
		{
			anD0[i] = anC[i - 1] - anD0[i - 2] - anD0[i - 1];
			anD1[i] = anC[i - 1] - anD1[i - 2] - anD1[i - 1];

			b0 = b0 && (anD0[i] | 1) == 1;
			b1 = b1 && (anD1[i] | 1) == 1;

		}

		//We also check the very last number
		if(anC[n-1] != (anD0[n-2] + anD0[n-1]))b0=false;
		if(anC[n-1] != (anD1[n-2] + anD1[n-1]))b1=false;


		//Converte the decoded strings to integers.
		StringBuilder sb0 = new StringBuilder();
		StringBuilder sb1 = new StringBuilder();

		if (b0)
		{
			for (int i = 0; i < n; i++)
			{
				sb0.append(anD0[i]);
			}
		}
		else
		{
			sb0.append("NONE");
		}
		
		
		if (b1)
		{
			for (int i = 0; i < n; i++)
			{
				sb1.append(anD1[i]);
			}
		}
		else
		{
			sb1.append("NONE");
		}


		String strOut[] =
		{
			sb0.toString(), sb1.toString()
		};


		return strOut;
	}
};
