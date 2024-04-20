from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QMenuBar, QMenu
from PyQt6.QtGui import QAction

import sys


class TestWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(200, 200, 450, 450)
        self.createCentralWidget()
        self.menuBar = TestMenu(self)
        self.menuBar.addLoadActionHandler(self.setLoadText)
        self.menuBar.addSaveActionHandler(self.setSaveText)

    def createCentralWidget(self):
        self.centralWidget = QLabel("Default text")
        self.centralWidget.setAlignment(
            Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignVCenter)
        self.setCentralWidget(self.centralWidget)

    def setLoadText(self):
        self.centralWidget.setText("Clicked on State->Load menu item")

    def setSaveText(self):
        self.centralWidget.setText("Clicked on State->Save menu item")



class TestMenu(QMenuBar):
    def __init__(self, parent: QMainWindow):
        super().__init__(parent)
                
        self.stateMItem = QMenu("State")
        self.editMItem = QMenu("Edit")
        self.addMenu(self.stateMItem)
        self.addMenu(self.editMItem)

        self.loadMenuAction = QAction("Load")
        self.stateMItem.addAction(self.loadMenuAction)

        self.saveMenuAction = QAction("Save")
        self.stateMItem.addAction(self.saveMenuAction)

        self.dropdownMenu = QMenu("Dropdown")
        self.dropdownMenu.addAction("Option 1")
        self.dropdownMenu.addAction("Option 3")
        self.dropdownMenu.addAction("Option 2")

        self.editMItem.addMenu(self.dropdownMenu)
        
    def addLoadActionHandler(self, handler):
        self.loadMenuAction.triggered.connect(handler)
        
    def addSaveActionHandler(self, handler):
        self.saveMenuAction.triggered.connect(handler)



if __name__ == "__main__":
    app = QApplication(sys.argv)
    wnd = TestWindow()
    wnd.show()

    sys.exit(app.exec())