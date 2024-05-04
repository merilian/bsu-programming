from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QLabel
from PyQt6.QtGui import QColor
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QVBoxLayout, QDialog, QInputDialog, QColorDialog 

import sys


def dialogFinished(result):
    if type(result) is QColor:
        color = QColor(result)
        label.setText(str(color.red()) + ', ' + 
                      str(color.green()) + ', ' + 
                      str(color.blue()))
    else:
        label.setText(str(result))

def openDialog():
    dialog = QDialog(wnd)
    dialog.open()
    dialog.finished.connect(dialogFinished)

def openInputDialog():
    dialog = QInputDialog(wnd)
    dialog.open()
    dialog.textValueSelected.connect(dialogFinished)

def openColorDialog():
    dialog = QColorDialog(wnd)
    dialog.open()
    dialog.currentColorChanged.connect(dialogFinished)





app = QApplication(sys.argv)
wnd = QMainWindow()

centralWidget = QWidget(wnd)

wnd.setCentralWidget(centralWidget)
layout = QVBoxLayout(centralWidget)
centralWidget.setLayout(layout)


button = QPushButton("Open")
layout.addWidget(button)
#button.clicked.connect(openDialog)
#button.clicked.connect(openInputDialog)
button.clicked.connect(openColorDialog)

label = QLabel()
layout.addWidget(label)








wnd.setGeometry(200, 200, 600, 600)

wnd.show()

sys.exit(app.exec())