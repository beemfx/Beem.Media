/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package testapp;

import java.util.Arrays;
import java.util.Comparator;

/**
 *
 * @author beemfx
 */
public class Bonuses
{
	public static int[] getDivision(int[] points)
	{
		int n = points.length;
		int[] anOut = new int[n];

		Emp[] elist = new Emp[n];

		for(int i=0; i<n; i++)
		{
			elist[i] = new Emp();
			elist[i].nID = i;
			elist[i].nPoints = points[i];
		}

		//Sort by the most points:
		Arrays.sort(elist, elist[0]);


		int nTotalPoints = 0;

		for(int i=0; i<n; i++)
			nTotalPoints += elist[i].nPoints;

		//Percentage for each person;
		int nTotalPerc = 0;
		for(int i=0; i<n; i++)
		{
			elist[i].nPerc = (100*elist[i].nPoints)/(nTotalPoints);

			System.out.println(elist[i] );
			nTotalPerc += elist[i].nPerc;
		}

		//Calculate the number of points left over:
		nTotalPerc = 100 - nTotalPerc;

		for(int i=0; i<nTotalPerc; i++)
		{
			elist[i].nPerc++;
		}

		for(int i=0; i<n; i++)
		{
			anOut[elist[i].nID] = elist[i].nPerc;
		}

		return anOut;
	}

	static class Emp implements Comparator
	{
		int nID;
		int nPoints;
		int nPerc;


		public int compare(Object o1, Object o2)
		{
			if(((Emp)o1).nPoints < ((Emp)o2).nPoints)
				return 1;
			else
				return -1;
		}

		public String toString()
		{
			return "EmpID " + nID + " (" + nPerc + ") (" + nPerc + "%)";
		}
	}
}