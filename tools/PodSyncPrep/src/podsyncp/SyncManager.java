/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import java.io.File;
import java.io.FilenameFilter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;
import java.util.regex.Pattern;

/**
 *
 * @author beemfx
 */
public class SyncManager {

    private static int s_nNextID = 1;
    private Vector<MP3Object> m_listUnassigned;
    private Vector<MP3Object> m_listAssigned;
    private WarningI m_warn;
    private Settings m_settings;

    public SyncManager(WarningI warn, Settings settings) {
        m_warn = warn;

        printWarning("Starting...");

        //Open up the settings file:
        m_settings = settings;

        printWarning("The directory is: " + m_settings.getCWD());

        m_listUnassigned = new Vector<MP3Object>();
        m_listAssigned = new Vector<MP3Object>();


        File fileDir = new File(m_settings.getCWD());

        File[] fileMP3s = fileDir.listFiles(new MP3Filter());



        if (fileMP3s == null) {
            printWarning("An error occured.");
        } else {

            for (int i = 0; i < fileMP3s.length; i++) {
                m_listUnassigned.add(new MP3Object(fileMP3s[i], s_nNextID, this));
                s_nNextID++;
            }
        }
    }

    public void processFiles(IProgressObject progress) {
        //Technically need to make sure no duplicate names exist for the
        //renaming process:

        Vector<MP3Object> l = m_listAssigned;

        //Find the increment for the progress bar:
        int nInc = l.size() > 0 ? 100 / l.size() : 0;
        int nProg = 0;

        //Create a date in case we want to put the date in the file.
        SimpleDateFormat dateFormat = new SimpleDateFormat(" - yy-MM-dd");
        String strDate = dateFormat.format(new Date());


		for (int i = 0; i
                < l.size(); i++) {
            MP3Object m = l.elementAt(i);

            String strNewName = String.format("%s/%03d%s.mp3", m_settings.getCWD(), i + 1, m_settings.getDateInFile()?strDate:"");
            printWarning(m + " => " + strNewName);

            m.processFile(strNewName);

            nProg +=
                    nInc;
            progress.setProgress(nProg);
        }

//Now, strangly the MP3 save things sometimes makes original copies,
//in this case we delete them.
        File fileDir = new File(m_settings.getCWD());
        File[] fileMP3s = fileDir.listFiles(new MP3OriginalFilter());

        for (int i = 0; i
                < fileMP3s.length; i++) {
            fileMP3s[i].delete();
        }





    }

    public enum Location {

        UNASSIGNED, ASSIGNED
    };

    /* moveItem: Moves an item from one list to the other:
     * nUID indicates the unique id of the item to be moved.
     * locFrom is the list in which the item is to be moved from.
     * locTo is the list that the item is to be moved to.
     * nPos is the position in the list where the item should be moved to, note
     * that 0 indicates the first position, and every other number inserts the
     * item after the specified number. nPos does not have anything to do with
     * unique ids, it is the position in the list.
     *
     * Returns true if the operation succeeded false otherwise, also
     * if the item cannot be inserted to the specifed position (ie the position
     * is after the end of the list) then the item is appended to the end.
     */
    public boolean moveItem(int nUID, Location locTo, int nPos) {
        //The first thing to do is find the item we want, we have to search both
        //lists for it.
        MP3Object m = null;

        //First check for the object in the unassigned list.
        for (int i = 0; i
                < m_listUnassigned.size() && m == null; i++) {
            if (m_listUnassigned.elementAt(i).getUID() == nUID) {
                m = m_listUnassigned.elementAt(i);
                m_listUnassigned.removeElementAt(i);
            }

        }

        //Now we check for the object in the assigned list, note that we
        //don't need to do any extra check because the m==null statement
        //will keep us going.
        //First check for the object in the unassigned list.
        for (int i = 0; i
                < m_listAssigned.size() && m == null; i++) {
            if (m_listAssigned.elementAt(i).getUID() == nUID) {
                m = m_listAssigned.elementAt(i);
                m_listAssigned.removeElementAt(i);

            }

        }

        //Now check to see that we actually have the item, fail if not.
        if (m == null) {
            return false;
        }

        m.setLocation(locTo);

        //Now insert to the specified list:
        Vector<MP3Object> list = (locTo == Location.ASSIGNED) ? m_listAssigned : m_listUnassigned;

        //Clamp the position, so it is within range.
        nPos =
                Math.max(0, nPos);
        nPos =
                Math.min(list.size(), nPos);
        list.add(nPos, m);


        return true;
    }

    public Vector<MP3Object> getList(Location loc) {
        return loc == Location.ASSIGNED ? m_listAssigned : m_listUnassigned;
    }

    public void printWarning(String str) {
        m_warn.appendWarning(str + "\n");
    }

//This class just filters MP3 files only.
    private class MP3Filter implements FilenameFilter {

        public boolean accept(File dir, String name) {
            if (Pattern.matches("^(.*[/\\\\])?[0-9]{3}.*\\.mp3$", name)) {
                printWarning("The file " + name + " exists, this file may be overwritten.");
                return false;
            }

            return name.endsWith(".mp3");
        }
    }

//This class just filters MP3 files only.
    private class MP3OriginalFilter implements FilenameFilter {

        public boolean accept(File dir, String name) {

            return name.endsWith(".original.mp3");
        }
    }
}
