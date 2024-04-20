from PyQt6.QtWidgets import QMenuBar, QMenu, QWidget
from PyQt6.QtGui import QAction

class TestMenu(QMenuBar):
    def __init__(self, parent: QWidget):
        super().__init__(parent)
        self.setMinimumSize(300, 1)
                
        self.stateMItem = QMenu("State")
        self.editMItem = QMenu("Edit")
        self.fileMItem = QMenu("File")
        self.addMenu(self.stateMItem)
        self.addMenu(self.editMItem)
        self.addMenu(self.fileMItem)

        self.loadMenuAction = QAction("Load")
        self.stateMItem.addAction(self.loadMenuAction)

        self.saveMenuAction = QAction("Save")
        self.stateMItem.addAction(self.saveMenuAction)

        self.dropdownMenu = QMenu("Dropdown")
        self.dropdownMenu.addAction("Option 1")
        self.dropdownMenu.addAction("Option 3")
        self.dropdownMenu.addAction("Option 2")

        self.editMItem.addMenu(self.dropdownMenu)

        self.openFileAction = QAction("Open")
        self.fileMItem.addAction(self.openFileAction)
        
    def addLoadActionHandler(self, handler):
        self.loadMenuAction.triggered.connect(handler)
        
    def addSaveActionHandler(self, handler):
        self.saveMenuAction.triggered.connect(handler)
        
    def addOpenFileActionHandler(self, handler):
        self.openFileAction.triggered.connect(handler)
