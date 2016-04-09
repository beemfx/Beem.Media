/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import javax.swing.JTextArea;


/**
 *
 * @author beemfx
 */
public class DLPanel extends javax.swing.JPanel {

	public DLPanel() {
		String strFeed = "http://www.keithandthegirl.com/rss/";
		//strFeed = "http://www.pcgamer.com/feed/";
		
		boolean bTest = false;
		
		if(bTest)
		{
			PodcastRSS rss = new PodcastRSS(strFeed);


			JTextArea t = new JTextArea(rss.toString());//ReadFeed(strFeed));
			this.add(t);
		}
	}
}
