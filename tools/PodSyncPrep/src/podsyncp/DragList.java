/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package podsyncp;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DragGestureEvent;
import java.awt.dnd.DragGestureListener;
import java.awt.dnd.DragGestureRecognizer;
import java.awt.dnd.DragSource;
import java.awt.dnd.DragSourceDragEvent;
import java.awt.dnd.DragSourceDropEvent;
import java.awt.dnd.DragSourceEvent;
import java.awt.dnd.DragSourceListener;
import javax.swing.DropMode;
import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.TransferHandler;

/**
 *
 * @author beemfx
 */
public class DragList extends JList {

	private final SyncManager.Location m_loc;
	private final SyncManager m_mgr;

	public DragList(SyncManager mgr, SyncManager.Location loc) {
		super();

		m_mgr = mgr;
		m_loc = loc;

		setDragEnabled(true);
		setDropMode(DropMode.INSERT);
		setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		setTransferHandler(new MyListDropHandler(this));

		new MyDragListener(this);

		updateListData();

	}

	public void updateListData() {
		this.setListData(m_mgr.getList(m_loc));
	}

	class MyDragListener implements DragSourceListener, DragGestureListener {

		DragList list;
		DragSource ds = new DragSource();

		public MyDragListener(DragList list) {
			this.list = list;
			DragGestureRecognizer dgr = ds.createDefaultDragGestureRecognizer(list,
					  DnDConstants.ACTION_MOVE, this);

		}

		public void dragGestureRecognized(DragGestureEvent dge) {
			MP3Object m = (MP3Object) list.getSelectedValue();

			StringSelection str = new StringSelection(Integer.toString(m.getUID()));

			if (m == null) {
				return;
			}
			//System.out.println("dragGestureRecognized: " + m);
			//StringSelection transferable = new StringSelection(Integer.toString(list.getSelectedIndex()));
			ds.startDrag(dge, DragSource.DefaultMoveDrop, str, this);
		}

		public void dragEnter(DragSourceDragEvent dsde) {
		}

		public void dragExit(DragSourceEvent dse) {
		}

		public void dragOver(DragSourceDragEvent dsde) {
		}

		public void dragDropEnd(DragSourceDropEvent dsde) {
			if (dsde.getDropSuccess()) {
				//System.out.println("Succeeded");
			} else {
				//System.out.println("Failed");
			}

			list.updateListData();
		}

		public void dropActionChanged(DragSourceDragEvent dsde) {
		}
	}

	class MyListDropHandler extends TransferHandler {

		DragList list;

		public MyListDropHandler(DragList list) {
			this.list = list;
		}

		@Override
		public boolean canImport(TransferHandler.TransferSupport support) {
			if (!support.isDataFlavorSupported(DataFlavor.stringFlavor)) {
				return false;
			}
			JList.DropLocation dl = (JList.DropLocation) support.getDropLocation();
			if (dl.getIndex() == -1) {
				return false;
			} else {
				return true;
			}
		}

		@Override
		public boolean importData(TransferHandler.TransferSupport support) {
			if (!canImport(support)) {
				return false;
			}

			Transferable transferable = support.getTransferable();
			String indexString;
			try {
				indexString = (String) transferable.getTransferData(DataFlavor.stringFlavor);
			} catch (Exception e) {
				return false;
			}

			JList.DropLocation dl = (JList.DropLocation) support.getDropLocation();

			int nUID = Integer.parseInt(indexString);
			SyncManager.Location locDest = ((DragList) support.getComponent()).m_loc;
			int nPos = dl.getIndex();

			m_mgr.moveItem(nUID, locDest, nPos);
			//System.out.printf("Moving %d to %s @ %d\n", nUID, locDest, nPos);
			list.updateListData();

			return true;
		}
	}
}
