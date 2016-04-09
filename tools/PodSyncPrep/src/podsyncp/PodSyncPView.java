/*
 * PodSyncPView.java
 */
package podsyncp;

import org.jdesktop.application.Action;
import org.jdesktop.application.ResourceMap;
import org.jdesktop.application.SingleFrameApplication;
import org.jdesktop.application.FrameView;
import org.jdesktop.application.TaskMonitor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 * The application's main frame.
 */
public class PodSyncPView extends FrameView implements ActionListener, WarningI {

    public PodSyncPView(SingleFrameApplication app) {
        super(app);

        m_strWarning = "";

        initComponents();
        //this.setComponent(mainPanel);

        // status bar initialization - message timeout, idle icon and busy animation, etc
        ResourceMap resourceMap = getResourceMap();
        int messageTimeout = resourceMap.getInteger("StatusBar.messageTimeout");
        messageTimer = new Timer(messageTimeout, new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                statusMessageLabel.setText("");
            }
        });
        messageTimer.setRepeats(false);
        int busyAnimationRate = resourceMap.getInteger("StatusBar.busyAnimationRate");
        for (int i = 0; i < busyIcons.length; i++) {
            busyIcons[i] = resourceMap.getIcon("StatusBar.busyIcons[" + i + "]");
        }
        busyIconTimer = new Timer(busyAnimationRate, new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                busyIconIndex = (busyIconIndex + 1) % busyIcons.length;
                statusAnimationLabel.setIcon(busyIcons[busyIconIndex]);
            }
        });
        idleIcon = resourceMap.getIcon("StatusBar.idleIcon");
        statusAnimationLabel.setIcon(idleIcon);
        progressBar.setVisible(false);

        // connecting action tasks to status bar via TaskMonitor
        TaskMonitor taskMonitor = new TaskMonitor(getApplication().getContext());
        taskMonitor.addPropertyChangeListener(new java.beans.PropertyChangeListener() {

            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                String propertyName = evt.getPropertyName();
                if ("started".equals(propertyName)) {
                    if (!busyIconTimer.isRunning()) {
                        statusAnimationLabel.setIcon(busyIcons[0]);
                        busyIconIndex = 0;
                        busyIconTimer.start();
                    }
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(true);
                } else if ("done".equals(propertyName)) {
                    busyIconTimer.stop();
                    statusAnimationLabel.setIcon(idleIcon);
                    progressBar.setVisible(false);
                    progressBar.setValue(0);
                } else if ("message".equals(propertyName)) {
                    String text = (String) (evt.getNewValue());
                    statusMessageLabel.setText((text == null) ? "" : text);
                    messageTimer.restart();
                } else if ("progress".equals(propertyName)) {
                    int value = (Integer) (evt.getNewValue());
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(false);
                    progressBar.setValue(value);
                }
            }
        });

        m_settings = new Settings(this);
        m_mgr = new SyncManager(this, m_settings);

        m_listA = new DragList(m_mgr, SyncManager.Location.ASSIGNED);
        m_listU = new DragList(m_mgr, SyncManager.Location.UNASSIGNED);

        m_scrollA = new JScrollPane(m_listA);
        m_scrollU = new JScrollPane(m_listU);

        m_panelButtons = new JPanel();

        m_btnDoIt = new JButton("Process Files");
        //m_panelButtons.add(new JButton("^"));
        //m_panelButtons.add(new JButton("V"));
        m_panelButtons.add(m_btnDoIt);
        m_btnDoIt.addActionListener(this);

        m_txtWarning = new JTextArea();
        m_txtWarning.setColumns(60);
        m_txtWarning.setRows(5);
        m_txtWarning.setLineWrap(false);
        m_txtWarning.setEditable(false);


        m_scrollWarning = new JScrollPane(m_txtWarning);
        m_panelButtons.add(m_scrollWarning);

        
		  tabPrep.add(m_scrollA);
		  tabPrep.add(m_panelButtons);
        tabPrep.add(m_scrollU);
		  
		  tabWindow.setTitleAt(0, "Download");
		  tabWindow.setTitleAt(1, "Prep");
		  
		  DLPanel p = new DLPanel();
		  tabDownload.add(p); 
		  /*
        mainPanel.add(m_scrollA);
        mainPanel.add(m_panelButtons);
        mainPanel.add(m_scrollU);
		*/

        m_mgr.printWarning("Initialized.");
    }

    @Action
    public void showAboutBox() {
        if (aboutBox == null) {
            JFrame mainFrame = PodSyncPApp.getApplication().getMainFrame();
            aboutBox = new PodSyncPAboutBox(mainFrame);
            aboutBox.setLocationRelativeTo(mainFrame);
        }
        PodSyncPApp.getApplication().show(aboutBox);
    }

    @Action
    public void showSettingsBox()
    {
        JFrame mainFrame = PodSyncPApp.getApplication().getMainFrame();
        SettingsBox setBox = new SettingsBox(mainFrame, true, m_settings);
        setBox.setLocationRelativeTo(mainFrame);
        PodSyncPApp.getApplication().show(setBox);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
   // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
   private void initComponents() {

      menuBar = new javax.swing.JMenuBar();
      javax.swing.JMenu fileMenu = new javax.swing.JMenu();
      javax.swing.JMenuItem exitMenuItem = new javax.swing.JMenuItem();
      settingsMenu = new javax.swing.JMenu();
      editMenuItem = new javax.swing.JMenuItem();
      javax.swing.JMenu helpMenu = new javax.swing.JMenu();
      javax.swing.JMenuItem aboutMenuItem = new javax.swing.JMenuItem();
      statusPanel = new javax.swing.JPanel();
      javax.swing.JSeparator statusPanelSeparator = new javax.swing.JSeparator();
      statusMessageLabel = new javax.swing.JLabel();
      statusAnimationLabel = new javax.swing.JLabel();
      progressBar = new javax.swing.JProgressBar();
      mainPanel = new javax.swing.JPanel();
      tabWindow = new javax.swing.JTabbedPane();
      tabDownload = new javax.swing.JPanel();
      tabPrep = new javax.swing.JPanel();

      menuBar.setName("menuBar"); // NOI18N

      org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(podsyncp.PodSyncPApp.class).getContext().getResourceMap(PodSyncPView.class);
      fileMenu.setText(resourceMap.getString("fileMenu.text")); // NOI18N
      fileMenu.setName("fileMenu"); // NOI18N

      javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(podsyncp.PodSyncPApp.class).getContext().getActionMap(PodSyncPView.class, this);
      exitMenuItem.setAction(actionMap.get("quit")); // NOI18N
      exitMenuItem.setName("exitMenuItem"); // NOI18N
      fileMenu.add(exitMenuItem);

      menuBar.add(fileMenu);

      settingsMenu.setText(resourceMap.getString("settingsMenu.text")); // NOI18N
      settingsMenu.setName("settingsMenu"); // NOI18N

      editMenuItem.setAction(actionMap.get("showSettingsBox")); // NOI18N
      editMenuItem.setText(resourceMap.getString("editMenuItem.text")); // NOI18N
      editMenuItem.setName("editMenuItem"); // NOI18N
      settingsMenu.add(editMenuItem);

      menuBar.add(settingsMenu);

      helpMenu.setText(resourceMap.getString("helpMenu.text")); // NOI18N
      helpMenu.setName("helpMenu"); // NOI18N

      aboutMenuItem.setAction(actionMap.get("showAboutBox")); // NOI18N
      aboutMenuItem.setName("aboutMenuItem"); // NOI18N
      helpMenu.add(aboutMenuItem);

      menuBar.add(helpMenu);

      statusPanel.setName("statusPanel"); // NOI18N

      statusPanelSeparator.setName("statusPanelSeparator"); // NOI18N

      statusMessageLabel.setName("statusMessageLabel"); // NOI18N

      statusAnimationLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
      statusAnimationLabel.setName("statusAnimationLabel"); // NOI18N

      progressBar.setName("progressBar"); // NOI18N

      javax.swing.GroupLayout statusPanelLayout = new javax.swing.GroupLayout(statusPanel);
      statusPanel.setLayout(statusPanelLayout);
      statusPanelLayout.setHorizontalGroup(
         statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
         .addComponent(statusPanelSeparator, javax.swing.GroupLayout.DEFAULT_SIZE, 604, Short.MAX_VALUE)
         .addGroup(statusPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(statusMessageLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 434, Short.MAX_VALUE)
            .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(statusAnimationLabel)
            .addContainerGap())
      );
      statusPanelLayout.setVerticalGroup(
         statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
         .addGroup(statusPanelLayout.createSequentialGroup()
            .addComponent(statusPanelSeparator, javax.swing.GroupLayout.PREFERRED_SIZE, 2, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
               .addComponent(statusMessageLabel)
               .addComponent(statusAnimationLabel)
               .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
            .addGap(3, 3, 3))
      );

      mainPanel.setAutoscrolls(true);
      mainPanel.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
      mainPanel.setName("mainPanel"); // NOI18N
      mainPanel.setLayout(new java.awt.GridLayout(1, 1));

      tabWindow.setName("tabWindow"); // NOI18N

      tabDownload.setName("tabDownload"); // NOI18N
      tabWindow.addTab(resourceMap.getString("tabDownload.TabConstraints.tabTitle"), tabDownload); // NOI18N

      tabPrep.setName("tabPrep"); // NOI18N
      tabPrep.setLayout(new java.awt.GridLayout(3, 1));
      tabWindow.addTab(resourceMap.getString("tabPrep.TabConstraints.tabTitle"), tabPrep); // NOI18N

      mainPanel.add(tabWindow);

      setComponent(mainPanel);
      setMenuBar(menuBar);
      setStatusBar(statusPanel);
   }// </editor-fold>//GEN-END:initComponents
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JMenuItem editMenuItem;
   private javax.swing.JPanel mainPanel;
   private javax.swing.JMenuBar menuBar;
   private javax.swing.JProgressBar progressBar;
   private javax.swing.JMenu settingsMenu;
   private javax.swing.JLabel statusAnimationLabel;
   private javax.swing.JLabel statusMessageLabel;
   private javax.swing.JPanel statusPanel;
   private javax.swing.JPanel tabDownload;
   private javax.swing.JPanel tabPrep;
   private javax.swing.JTabbedPane tabWindow;
   // End of variables declaration//GEN-END:variables
    private final Timer messageTimer;
    private final Timer busyIconTimer;
    private final Icon idleIcon;
    private final Icon[] busyIcons = new Icon[15];
    private int busyIconIndex = 0;
    private JDialog aboutBox;
    private SyncManager m_mgr;
    private DragList m_listU;
    private DragList m_listA;
    private JScrollPane m_scrollU;
    private JScrollPane m_scrollA;
    private JPanel m_panelButtons;
    private JButton m_btnDoIt;
    private JScrollPane m_scrollWarning;
    private JTextArea m_txtWarning;
    private Settings m_settings;
    private String m_strWarning;

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == m_btnDoIt) {
            JFrame mainFrame = PodSyncPApp.getApplication().getMainFrame();
            WaitWindow wnd = new WaitWindow(mainFrame, m_mgr);


            m_listA.updateListData();
            m_listU.updateListData();
        }
    }

    public void setWarning(String str) {
        m_strWarning = str;
        //JOptionPane.showMessageDialog(null, str, null, JOptionPane.WARNING_MESSAGE);
        if (m_txtWarning != null) {
            m_txtWarning.setText(m_strWarning);
        }

    }

    public void appendWarning(String str) {
        m_strWarning += str;
        setWarning(m_strWarning);
    }
}
