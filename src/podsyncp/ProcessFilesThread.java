/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

public class ProcessFilesThread extends Thread {

	private final SyncManager m_mgr;
	private final IProgressObject m_progress;

	public ProcessFilesThread(SyncManager mgr, IProgressObject progress) {
		super();
		m_mgr = mgr;
		m_progress = progress;
	}

	@Override
	public void run() {

		m_progress.startProgress();
		m_mgr.processFiles(m_progress);
		m_progress.endProgress();
	}
}
