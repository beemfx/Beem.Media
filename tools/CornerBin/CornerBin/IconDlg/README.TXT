Welcome to CIconDialog, A freeware MFC dialog class to select an icon. This is
based on the dialog that appears when you choose to change the icon for a 
shortcut in the Windows 95 / NT 4 shell. The actual appearance of the dialog is 
based on the new look dialog in IE4 PP2 which uses a larger list box to display
the icons. Have a look on my web site or run the supplied sample to see what it 
looks like.

Included is a simple dialog based application which shows how to use it. The 
class would be used in your application as follows:

  CIconDialog dlg(this);
  dlg.SetIcon(m_sFilename, m_nIconIndex);
  if (dlg.DoModal() == IDOK)
    dlg.GetIcon(m_sFilename, m_nIconIndex);

The variables m_sFilename and m_nIconIndex would be managed by your application.							   


To use CIconDialog in your project simply include icondlg.cpp, the 5 string 
resources and the dialog resource IDD_CHOOSE_ICON from the test application in 
your application. Then just #include "icondlg.h" in which ever class needs to 
use it.


Happy coding.



CONTACTING THE AUTHOR

PJ Naughter
Email: pjna@naughter.com
Web: http://www.naughter.com
12th April 2000


