"""
PyQt GUI to call from browse.py (optionally)
based on PyQt 4.2 QAbstractTableModel/QTableView Example from
http://www.saltycrane.com/blog/2007/06/pyqt-42-qabstracttablemodelqtableview/
on cosmetics, also
http://www.saltycrane.com/blog/2007/12/pyqt-43-qtableview-qabstracttable-model/
"""

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import sys

# this was main(), now it is the function called by browse.py
# action is one of 'Restore', 'Delete', 'Print', 'SetDefault', 'remDefault'
# my_array is a list of tuples, setting file info from browse.py
def choose(action, my_array):
    app = QApplication(sys.argv)
    w = MyWindow(action, my_array)
    w.show()
    return app.exec_() # sys.exit(app.exec_()) - NOT!  # exec_() returns fline

action_text = { 'Restore'    : 'Restore saved setting', 
                'Delete'     : 'Delete saved setting', 
                'Print'      : 'Print saved setting', 
                'SetDefault' : 'Add setting to default list',
                'remDefault' : 'Remove setting from default list' }

class MyWindow(QWidget):
    def __init__(self, action, my_array, *args):
        QWidget.__init__(self, *args)

        # x, y, w, h. from OpsMain.edl, Embedded Window for utilities.edl etc.
        self.setGeometry(250, 15, 1075, 885) # same size as in utilities.edl 

        caption = QLabel(QString(action_text[action]))
        font = caption.font()
        font.setPointSize(12)
        caption.setFont(font)
        caption.setAlignment(Qt.AlignHCenter)

        tablemodel = MyTableModel(my_array, self)
        self.tableview = QTableView()  # we need to refer to this view later
        self.tableview.setModel(tablemodel)
        self.tableview.resizeColumnsToContents()

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.ok)
        buttons.rejected.connect(self.cancel)

        layout = QVBoxLayout(self)
        layout.addWidget(caption)
        layout.addWidget(self.tableview)
        layout.addWidget(buttons)
        self.setLayout(layout)

    def ok(self):
        fline = self.tableview.currentIndex().row() + 1
        # print " OK pressed, returning fline %d" % fline # DEBUG
        QCoreApplication.exit(fline) 

    def cancel(self):
        # print " Cancel pressed, returning fline 0" # DEBUG
        QCoreApplication.exit(0) # fline == 0 indicates no selection
        
# all this code has to be here
class MyTableModel(QAbstractTableModel):
    def __init__(self, datain, parent=None, *args):
        QAbstractTableModel.__init__(self, parent, *args)
        self.arraydata = datain
        self.headerdata = ['Setting','Description','Operator','Date']

    def rowCount(self, parent):
        return len(self.arraydata)

    def columnCount(self, parent):
        return len(self.arraydata[0]) if len(self.arraydata) else 0

    # some qt ritual -- ??
    def data(self, index, role):
        if not index.isValid():
            return QVariant()
        elif role != Qt.DisplayRole:
            return QVariant()
        return QVariant(self.arraydata[index.row()][index.column()])

    def headerData(self, i, orientation, role):  # i is row or column
        if orientation == Qt.Horizontal and role == Qt.DisplayRole:
            return QVariant(self.headerdata[i])
        if orientation == Qt.Vertical and role == Qt.DisplayRole:
            return QVariant(i+1)
        return QVariant()

# no call to main
