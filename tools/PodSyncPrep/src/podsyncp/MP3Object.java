/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import java.io.File;
import org.farng.mp3.MP3File;
import org.farng.mp3.TagConstant;
import org.farng.mp3.id3.AbstractID3v2;
import org.farng.mp3.id3.ID3v1;
import org.farng.mp3.id3.ID3v2_2;
import org.farng.mp3.lyrics3.Lyrics3v1;

/**
 *
 * @author beemfx
 */
class MP3Object {

	private String m_strArtist;
	private String m_strTitle;
	private String m_strListName;
	private MP3File m_mp3File;
	private File m_file;
	private int m_nUID;
	private SyncManager.Location m_loc;
	private SyncManager m_mgr;

	public MP3Object(File file, int nUID, SyncManager mgr) {
		super();
		m_mgr = mgr;
		m_nUID = nUID;

		m_file = file;

		m_loc = SyncManager.Location.UNASSIGNED;

		try {
			m_mp3File = new MP3File(file);

			ID3v1 tag1 = m_mp3File.getID3v1Tag();
			AbstractID3v2 tag2 = m_mp3File.getID3v2Tag();


			if (tag2.getSongTitle().length() > 0) {
				m_strTitle = tag2.getSongTitle();
			} else if (tag1.getSongTitle().length() > 0) {
				m_strTitle = tag1.getSongTitle();
			} else {
				m_strTitle = file.getName();
			}


			if (tag2.getLeadArtist().length() > 0) {
				m_strArtist = tag2.getLeadArtist();
			} else {
				m_strArtist = "Unknown";
			}
			/*
			else if(tag1.getAuthorComposer().length()>0)
			m_strArtist = tag1.getAuthorComposer();
			else
			m_strArtist = "Unkown";
			 */




		} catch (Exception e) {
			m_strArtist = "Unknown";
			m_strTitle = "Unknown";
		}

		m_strListName = String.format("%d: %s - %s (%s)", m_nUID, m_strArtist, m_strTitle, file.getName());
	}

	void setLocation(SyncManager.Location loc) {
		m_loc = loc;
	}

	public SyncManager.Location getLocation() {
		return m_loc;
	}

	public int getUID() {
		return m_nUID;
	}

	public void processFile(String strFilename) {
		removeTagInfo();

		File fileNew = new File(strFilename);
		if (fileNew.exists()) {
			fileNew.delete();
			m_mgr.printWarning("Overwriting " + fileNew.getName() + "...");
		}

		m_file.renameTo(fileNew);

		m_strListName = "Processed - " + fileNew.getName();

	}

	private void removeTagInfo() {
		ID3v1 tag1 = new ID3v1();
		ID3v2_2 tag2 = new ID3v2_2();
		Lyrics3v1 lyric = new Lyrics3v1();

		m_mp3File.setID3v1Tag(tag1);
		m_mp3File.setID3v2Tag(tag2);
		m_mp3File.setLyrics3Tag(lyric);

		try {
			m_mp3File.save();
		} catch (Exception e) {
			m_mgr.printWarning("Couldn't write to MP3.");
		}
	}

	@Override
	public String toString() {
		return m_strListName;
	}
}
