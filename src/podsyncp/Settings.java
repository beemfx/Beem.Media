/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author beemfx
 */
public class Settings {

    public Settings(WarningI warn) {
        m_warn = warn;
        m_strCWD = "./";
        m_bDateInFile = true;
        open();
    }

    public String getCWD()
    {
        return m_strCWD;
    }

    public void setCWD(String strCWD)
    {
        m_strCWD = strCWD;
        m_bDateInFile = true;
    }

    public boolean getDateInFile()
    {
        return m_bDateInFile;
    }

    public void setDateInFile(boolean b)
    {
        m_bDateInFile = b;
    }

    private void open()
    {
        openSettings();
    }
    public void save() {
        File fileSettings = openSettingsFile();
        try {
            PrintWriter writeFile = new PrintWriter(new FileWriter(fileSettings));

            writeFile.printf("dir = \"%s\"\n", m_strCWD);
            writeFile.printf("dateinfile = \"%s\"\n", m_bDateInFile?"true":"false");

            writeFile.close();

        } catch (Exception e) {
        }
    }
    private WarningI m_warn;
    private String m_strCWD;
    private boolean m_bDateInFile;

    private void openSettings() {
        File fileSettings = openSettingsFile();
        try {
            if (fileSettings == null) {
                throw new IllegalStateException("Didn't open file.");
            }

            Scanner scanFile = new Scanner(fileSettings);
            Pattern p = Pattern.compile("(\\w*)\\s*=\\s\"(.*)\"");

            while (scanFile.hasNextLine()) {
                String strLine = scanFile.nextLine();
                //printWarning("The line is: " + strLine);
                Matcher match = p.matcher(strLine);
                if (match.matches()) {
                    String strProp = match.group(1);
                    String strValue = match.group(2);
                    //printWarning(String.format("%s is %s", strProp, strValue));
                    if (0 == "dir".compareToIgnoreCase(strProp)) {
                        m_strCWD = strValue;
                    }else if(0 == "dateinfile".compareToIgnoreCase(strProp))
                        m_bDateInFile = (0=="true".compareToIgnoreCase(strValue));
                } else {
                    printWarning(strLine + " is invalid.");
                }

            }
            scanFile.close();

        } catch (Exception e) {
            printWarning("Failed to load settings: " + e.toString());

            m_strCWD = "./";
        }

    }

    private File openSettingsFile() {
        String strUserDir = System.getProperty("user.home");
        if (strUserDir == null) {
            throw new IllegalStateException("Couldn't find user.home.");

        }

        //printWarning("The user dir is " + strUserDir);
        File fileHome = new File(strUserDir);
        File fileSettingsDir = new File(fileHome, ".podsyncp");
        if (!fileSettingsDir.exists()) {
            printWarning("Creating application settigns directory...");
            if (!fileSettingsDir.mkdir()) {
                printWarning("Couldn't create settings directory.");
                throw new IllegalStateException(fileSettingsDir.toString());
            }

        }

        //We now have the file: Let's open the settings file
        File fileSettings = new File(fileSettingsDir, "settings.cfg");

        if (!fileSettings.exists()) {
            printWarning("Creating the settings file...");
            try {
                fileSettings.createNewFile();
            } catch (Exception e) {
                printWarning("Coul not create settings file.");
                return null;
            }

        }

        return fileSettings;
    }


	public void printWarning(String str) {
                m_warn.appendWarning(str + "\n");
	}
}
