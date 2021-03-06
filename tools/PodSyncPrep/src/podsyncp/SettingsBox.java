/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * SettingsBox.java
 *
 * Created on Nov 24, 2010, 1:27:22 PM
 */
package podsyncp;

import java.io.File;
import javax.swing.JFileChooser;
import org.jdesktop.application.Action;

/**
 *
 * @author beemfx
 */
public class SettingsBox extends javax.swing.JDialog {

    /** Creates new form SettingsBox */
    public SettingsBox(java.awt.Frame parent, boolean modal, Settings settings) {
        super(parent, modal);
        m_settings = settings;
        initComponents();


        this.m_txtWorkingDir.setText(m_settings.getCWD());
        this.m_cboxDate.setSelected(m_settings.getDateInFile());


    }
    private Settings m_settings;

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        m_btnOkay = new javax.swing.JButton();
        m_txtWorkingDir = new javax.swing.JTextField();
        jLabel1 = new javax.swing.JLabel();
        m_cboxDate = new javax.swing.JCheckBox();
        m_btnBrowse = new javax.swing.JButton();
        m_btnCancel = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(podsyncp.PodSyncPApp.class).getContext().getResourceMap(SettingsBox.class);
        setTitle(resourceMap.getString("Form.title")); // NOI18N
        setModal(true);
        setName("Form"); // NOI18N
        setResizable(false);

        javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(podsyncp.PodSyncPApp.class).getContext().getActionMap(SettingsBox.class, this);
        m_btnOkay.setAction(actionMap.get("onBtnOkay")); // NOI18N
        m_btnOkay.setText(resourceMap.getString("m_btnOkay.text")); // NOI18N
        m_btnOkay.setName("m_btnOkay"); // NOI18N

        m_txtWorkingDir.setText(resourceMap.getString("m_txtWorkingDir.text")); // NOI18N
        m_txtWorkingDir.setName("m_txtWorkingDir"); // NOI18N

        jLabel1.setText(resourceMap.getString("jLabel1.text")); // NOI18N
        jLabel1.setName("jLabel1"); // NOI18N

        m_cboxDate.setText(resourceMap.getString("m_cboxDate.text")); // NOI18N
        m_cboxDate.setName("m_cboxDate"); // NOI18N

        m_btnBrowse.setAction(actionMap.get("onBtnBrowse")); // NOI18N
        m_btnBrowse.setText(resourceMap.getString("m_btnBrowse.text")); // NOI18N
        m_btnBrowse.setName("m_btnBrowse"); // NOI18N

        m_btnCancel.setAction(actionMap.get("onBtnCancel")); // NOI18N
        m_btnCancel.setText(resourceMap.getString("m_btnCancel.text")); // NOI18N
        m_btnCancel.setName("m_btnCancel"); // NOI18N

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(m_txtWorkingDir, javax.swing.GroupLayout.PREFERRED_SIZE, 228, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(10, 10, 10)
                        .addComponent(m_btnBrowse))
                    .addComponent(m_cboxDate))
                .addContainerGap())
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(287, Short.MAX_VALUE)
                .addComponent(m_btnCancel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(m_btnOkay)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(m_txtWorkingDir, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(m_btnBrowse))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(m_cboxDate)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 30, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(m_btnOkay)
                    .addComponent(m_btnCancel))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    @Action
    public void onBtnOkay() {
        m_settings.setCWD(this.m_txtWorkingDir.getText());
        m_settings.setDateInFile(this.m_cboxDate.isSelected());
        m_settings.save();
        this.dispose();
    }

    @Action
    public void onBtnBrowse() {
        JFileChooser chooser = new JFileChooser();
        chooser.setCurrentDirectory(new java.io.File("."));
        chooser.setDialogTitle("Sync Directory");
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        chooser.setCurrentDirectory(new File(m_settings.getCWD()));
        //
        // disable the "All files" option.
        //
        chooser.setAcceptAllFileFilterUsed(false);
        //
        if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            this.m_txtWorkingDir.setText(chooser.getSelectedFile().getPath());
        } else {
            
        }
    }

    @Action
    public void onBtnCancel() {
        this.dispose();
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel1;
    private javax.swing.JButton m_btnBrowse;
    private javax.swing.JButton m_btnCancel;
    private javax.swing.JButton m_btnOkay;
    private javax.swing.JCheckBox m_cboxDate;
    private javax.swing.JTextField m_txtWorkingDir;
    // End of variables declaration//GEN-END:variables
}
