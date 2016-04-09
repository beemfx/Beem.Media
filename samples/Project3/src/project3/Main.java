/*
	Main.java - Entry point and windows management for Project3.
	Blaine Myers
	Project 3
	CS 1400-002
	Copyright (c) 2006, Blaine Myers
 */

package project3;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class Main extends JFrame implements ActionListener
{ 
	private static String m_szAppName="Winter Wonderland";
	
	private JButton m_btnPower1;
	private JButton m_btnPower2;
	private JButton m_btnCycleLights;
	private ImageIcon m_imgBG;
	private JLabel m_lblImg;
	
	private javax.swing.Timer m_time;
	private int m_nRefreshRate=250;
	
	private SceneLight m_pStrand1[];
	private boolean m_bStrand1On=true;
	private int m_nStrand1LightCount=0;
	private int m_nStrand1Pattern=0;
	private int m_nStrand1Extra=0;
	
	private SceneLight m_pStrand2[];
	private boolean m_bStrand2On=true;
	private int m_nStrand2LightCount=0;

	
	private boolean m_bReady=false; //Ready value means we are ready to update.
	
	private Random m_rnd=new Random();
	
	
	public Main()
	{
		//Setup the window. 
		super(m_szAppName);
		setBounds(20, 20, 640, 480);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		setResizable(false);
		//Create the buttons.
		//FlowLayout flow=new FlowLayout();
		setLayout(null);
		//flow.setAlignment(FlowLayout.LEFT);
		
		m_btnPower1=new JButton("Power 1");
		m_btnPower2=new JButton("Power 2");
		m_btnCycleLights=new JButton("Cycle Lights");
		
		
		m_btnPower1.addActionListener(this);
		m_btnPower2.addActionListener(this);
		m_btnCycleLights.addActionListener(this);
		
		m_btnPower1.setBounds(0, 0, 110, 30);
		m_btnPower2.setBounds(0, 0, 110, 30);
		m_btnCycleLights.setBounds(0, 0, 110, 30);
		
		m_btnPower1.setLocation(10, 10);
		m_btnPower2.setLocation(10, 45);
		m_btnCycleLights.setLocation(125, 10);
		
		
		
		//Create the background
		//Toolkit kit = Toolkit.getDefaultToolkit();
		//m_imgBG=kit.getImage("background.jpg");
		m_imgBG=new ImageIcon("background.jpg");
		m_lblImg=new JLabel(m_imgBG);
		m_lblImg.setBounds(0, 0, m_imgBG.getIconWidth(), m_imgBG.getIconHeight());
		
		setupLights();
		
		add(m_btnPower1);
		add(m_btnPower2);
		add(m_btnCycleLights);
		
		add(m_lblImg);
		
		
		//Create the timer.
		m_time=new javax.swing.Timer(m_nRefreshRate, this);
		m_time.setInitialDelay(m_nRefreshRate);
		m_time.start();
		
		
		
		validate();
		m_bReady=true;
	}
	
	private int lightColor(int n)
	{
		switch(n%4)
			{
				default:
				case 0:return 0xFF0000;
				case 1:return 0x00FF00;
				case 2:return 0x0000FF;
				case 3:return 0xFFFF00;
			}
	}
	
	private void setupLights()
	{
		int i=0, j=0, n=0;
		//int nColor=0;
		
		//Create the standard lights.
		m_pStrand1=new SceneLight[32];
		
		//Base of the roof.
		for(i=0, n=0; i<16; i++,n++)
		{
			
			m_pStrand1[n]=new SceneLight(lightColor(n), 34*i+66, 155);
			add(m_pStrand1[n]);
		}
		
		//Right side.
		for(i=0; i<3; i++, n++)
		{
			m_pStrand1[n]=new SceneLight(lightColor(n), 560-i*23, 125-i*28);
			add(m_pStrand1[n]);
		}
		
		//Top.
		for(i=0; i<11; i++, n++)
		{
			m_pStrand1[n]=new SceneLight(lightColor(n), 482-i*35, 69);
			add(m_pStrand1[n]);
		}
		
		//Left side.
		for(i=0; i<2; i++, n++)
		{
			m_pStrand1[n]=new SceneLight(lightColor(n), 108-i*23, 95+i*30);
			add(m_pStrand1[n]);
		}
		
		
		m_nStrand1LightCount=n;
		
		
		//Add the icicle lights (strand 2).
		m_pStrand2=new SceneLight[38];
		for(i=0, n=0; i<15; i++)
		{
			for(j=0; j<3-i%2; j++, n++)
			{
				m_pStrand2[n]=new SceneLight(0xFFFFFF, 37*i+63, 160+j*20);
				add(m_pStrand2[n]);
			}
		}
		
		m_nStrand2LightCount=n;
	}
	
	private void messageBox(String szMessage)
	{
		JOptionPane.showMessageDialog(this, szMessage);	
	}
	
	private void power1()
	{
		m_bStrand1On=!m_bStrand1On;
		float fNewIntensity=m_bStrand1On?1.0f:0.25f;
		
		for(int i=0; i<m_nStrand1LightCount; i++)
		{
			m_pStrand1[i].setIntensity(fNewIntensity);
		}
	}
	
	private void power2()
	{
		m_bStrand2On=!m_bStrand2On;
		float fNewIntensity=m_bStrand2On?1.0f:0.25f;
		
		for(int i=0; i<m_nStrand2LightCount; i++)
		{
			m_pStrand2[i].setIntensity(fNewIntensity);
		}
	}
	
	private void changeLightCycle()
	{
		m_nStrand1Pattern++;
		if(m_nStrand1Pattern>1)
			m_nStrand1Pattern=0;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(!m_bReady)
			return;
		Object src=e.getSource();
		if(src==m_btnPower1)
		{
			power1();
		}
		else if(src==m_btnPower2)
		{
			power2();
		}
		else if(src==m_btnCycleLights)
		{
			m_nStrand1Extra=0;
			changeLightCycle();
		}
		else if(src==m_time)
		{
			//Call timed refresh on the time
			//and return so we don't call it twice.
			timedRefresh();
			return;
		}
		
		timedRefresh();
	}
	
	private void processLightPattern1()
	{
		float fNewIntensity=1.0f;
		if(m_nStrand1Extra>20)
			m_nStrand1Extra=0;
		
		if(m_nStrand1Extra<10)
			fNewIntensity=1.0f-(float)m_nStrand1Extra*0.07f;
		else
			fNewIntensity=1.0f-(float)(20-m_nStrand1Extra)*0.07f;
		
		m_nStrand1Extra++;
		
		for(int i=0; i<m_nStrand1LightCount; i++)
		{
			m_pStrand1[i].setIntensity(fNewIntensity);
		}
	}
	
	private void processLightPattern2()
	{
		if(m_nStrand1Extra>3)
			m_nStrand1Extra=0;
		
		for(int i=0; i<m_nStrand1LightCount; i++)
		{

			if((i%4)==m_nStrand1Extra)
			{
				m_pStrand1[i].setIntensity(1.0f);
			}
			else
			{
				m_pStrand1[i].setIntensity(0.25f);
			}
		}
		
		m_nStrand1Extra++;
	}
	
	private void timedRefresh()
	{
		//Process strand 1.
		if(m_bStrand1On)
		{
			switch(m_nStrand1Pattern)
			{
				default:
				case 0:
					processLightPattern1();
					break;
				case 1:
					processLightPattern2();
					break;
			}
		}
		
		//Make strand 2 twinkle a little bit
		if(m_bStrand2On)
		{
			for(int i=0; i<m_nStrand2LightCount; i++)
			{
				float fNewIntensity=(float)(100-m_rnd.nextInt(30))/100.0f;
				m_pStrand2[i].setIntensity(fNewIntensity);
			}
		}
		
		validate();
	}
	

	//Entry point for Project3
	public static void main(String[] args) 
	{
		Main win=new Main();
	}
    
}
