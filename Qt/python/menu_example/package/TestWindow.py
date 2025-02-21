from menu import TestMenu

from PyQt6.QtWidgets import QMainWindow, QLabel
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QFileDialog

class TestWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(200, 200, 450, 450)
        self.createCentralWidget()
        self.menuBar = TestMenu(self)
        self.menuBar.addLoadActionHandler(self.setLoadText)
        self.menuBar.addSaveActionHandler(self.setSaveText)
        self.menuBar.addOpenFileActionHandler(self.openFile)

    def createCentralWidget(self):
        self.centralWidget = QLabel("Default text")
        self.centralWidget.setAlignment(
            Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignVCenter)
        self.setCentralWidget(self.centralWidget)

    def setLoadText(self):
        self.centralWidget.setText("Clicked on State->Load menu item")

    def setSaveText(self):
        self.centralWidget.setText("Clicked on State->Save menu item")

    def openFile(self):
        file = QFileDialog(self)
        fileName = file.getOpenFileName()
        text = ""
        for line in open(fileName[0]):
            text += line

        self.centralWidget.setText(text)
