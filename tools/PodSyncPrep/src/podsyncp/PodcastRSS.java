/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import com.sun.cnpi.rss.elements.Channel;
import com.sun.cnpi.rss.elements.Enclosure;
import com.sun.cnpi.rss.elements.Item;
import com.sun.cnpi.rss.elements.PubDate;
import com.sun.cnpi.rss.elements.Rss;
import com.sun.cnpi.rss.parser.RssParser;
import com.sun.cnpi.rss.parser.RssParserFactory;
import java.net.URL;
import java.util.Collection;
import java.util.Iterator;

/**
 *
 * @author beemfx
 */
public class PodcastRSS{

	public PodcastRSS(String strURL) {
		m_strFeedURL = strURL;
		m_nItems = 0;
		m_aItems = new RSSItem[MAX_ITEMS];

		for (int i = 0; i < MAX_ITEMS; i++) {
			m_aItems[i] = new RSSItem();
		}

		//The first thing we should do is load the settings file, so we know
		//what the date of the last downloaded feed is.

		ReadFeed();
	}

	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();

		str.append(String.format("Feed %s (%d items):\n", m_strFeedURL, m_nItems));

		for (int i = 0; i < m_nItems; i++) {
			str.append(String.format("%s: %s (%s)\n", m_aItems[i].strTitle, m_aItems[i].strFileURL, m_aItems[i].dtPub.toString()));
		}
		return str.toString();
	}
	private final String m_strFeedURL; //The URL of the feed.
	private static final int MAX_ITEMS = 10; //Maximum number of items that will be downloaded.
	private int m_nItems;
	private final RSSItem[] m_aItems;

	//The RSSItem class is a subclass that defines the important information
	//of one of the RSS items, namely it contains the filename.
	private class RSSItem {

		public String strTitle;
		public String strFileURL; //URL of the file.
		public PubDate dtPub; //Date of publication.
	}

	/*
	 * ReadFeed reads the feed of m_strFeedURL, when the function exists
	 * m_nItems will contain the number of items that were read (this is all
	 * items that were read, not necessarily the ones that have meaning).
	 * And m_aItems will contain the important information about those items,
	 * that is the title, filename, and date.
	 * 
	 */
	private void ReadFeed() {
		try {

			RssParser parser = RssParserFactory.createDefault();
			Rss rss = parser.parse(new URL(m_strFeedURL));

			Channel c = rss.getChannel();
			
			Collection items = c.getItems();

			m_nItems = 0;
			for (Iterator it = items.iterator(); it.hasNext() && m_nItems < MAX_ITEMS;) {

				Item item = (Item) it.next();
				try {
					if (IsPodcast(item)) {
						m_aItems[m_nItems].strTitle = item.getTitle().toString();
						m_aItems[m_nItems].strFileURL = item.getEnclosure().getAttribute("url");
						m_aItems[m_nItems].dtPub = item.getPubDate();
						m_nItems++;
					}
				} catch (Exception e) {
					System.out.println("An item with invalid data was found.\n");
				}
			}
			 

		} catch (Exception e) {
			System.out.println("Error reading feed:" + e.toString() + "\n");
		}
	}

	private static boolean IsPodcast(Item item) {
		//This function returns true if the item is a podcast, and false otherwise
		boolean bPod = false;

		try {
			String url = item.getEnclosure().getAttribute("url");

			//Currently only checking if it is an MP3, should probably check
			//for other podcast types.
			if (url.matches(".*mp3$")) {
				bPod = true;
			}
		} catch (Exception e) {
			System.out.println("No enclosure.\n");
		}

		return bPod;
	}
}
