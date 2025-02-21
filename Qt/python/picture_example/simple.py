from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QFileDialog, QLabel
from PyQt6.QtGui import QPixmap, QFont

from PyQt6.QtWidgets import QVBoxLayout, QLineEdit

import sys


def showImage():
    file = QFileDialog(wnd)
    fileName = file.getOpenFileName()[0]
    pixmap = QPixmap(fileName)
    pixmap = pixmap.scaled(580, 500)
    picture.setPixmap(pixmap)


def openImage():
    pixmap = QPixmap(input.displayText())
    pixmap = pixmap.scaled(580, 500)
    picture.setPixmap(pixmap)


app = QApplication(sys.argv)
wnd = QMainWindow()

centralWidget = QWidget(wnd)

#centralWidget.setFixedSize(200, 200)
wnd.setCentralWidget(centralWidget)
layout = QVBoxLayout(centralWidget)
centralWidget.setLayout(layout)


button = QPushButton("Open")
layout.addWidget(button)
button.clicked.connect(showImage)

picture = QLabel()
layout.addWidget(picture)


input = QLineEdit()
input.setFont(QFont("Arial",20))
layout.addWidget(input)


input.editingFinished.connect(openImage)

# C:\Users\Merilian\Desktop\Attempt1.jpg

wnd.setGeometry(200, 200, 600, 600)

wnd.show()

sys.exit(app.exec())