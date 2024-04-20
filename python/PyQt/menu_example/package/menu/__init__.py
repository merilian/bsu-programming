from .TestMenu import TestMenu

from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt6.QtCore import Qt

import sys

if __name__ == "__main__":
    app = QApplication(sys.argv)
    wnd = QMainWindow()
    wnd.setGeometry(200, 200, 450, 450)

    centralWidget = QLabel("Default text")
    centralWidget.setAlignment(
        Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignVCenter)
    wnd.setCentralWidget(centralWidget)
    menu = TestMenu(wnd)

    def click():
        centralWidget.setText("Clicked")
    
    menu.addLoadActionHandler(click)


    wnd.show()

    sys.exit(app.exec())