/*
	SceneLight.java - Light Management code.
	Blaine Myers
	Project 3
	CS 1400-002
	Copyright (c) 2006, Blaine Myers
 */

package project3;

import java.awt.*;
import javax.swing.*;

public class SceneLight extends JComponent
{
	
	private int m_nR, m_nG, m_nB;
	
	public SceneLight(int nRGBColor, int x, int y) 
	{
		super();
		setBounds(0, 0, 10, 10);
		setLocation(x, y);
		
		
		m_nR=((nRGBColor&0x00FF0000)>>16);
		m_nG=((nRGBColor&0x0000FF00)>>8);
		m_nB=((nRGBColor&0x000000FF));
		
		setIntensity(1.0f);
	}
	
	public void paint(Graphics g)
	{
		g.setColor(getBackground());
		g.fillOval(0, 0, getWidth()-1, getHeight()-1);
		paintChildren(g);
	}
	
	public void setIntensity(float fIntensity)
	{
		//Clamp to between 0.0f and 1.0f.
		fIntensity=fIntensity<0.0f?0.0f:fIntensity>1.0f?1.0f:fIntensity;
		
		int r, g, b;
		
		r=(int)((float)m_nR*fIntensity);
		g=(int)((float)m_nG*fIntensity);
		b=(int)((float)m_nB*fIntensity);
		setBackground(new Color(r, g, b));
	}
	
}
