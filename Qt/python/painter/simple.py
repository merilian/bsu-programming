from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QFileDialog, QLabel
from PyQt6.QtGui import QPixmap, QFont, QColor, QPainter, QPen, QBrush
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QVBoxLayout, QLineEdit

import sys

app = QApplication(sys.argv)
wnd = QMainWindow()


label = QLabel(wnd)

width = 1000
height = 500


canvas = QPixmap(width, height)
#canvas.fill(QColor(255, 0, 0, 255))
canvas.fill(Qt.GlobalColor.white)

paint = QPainter(canvas)
bluePen = QPen(Qt.GlobalColor.blue)
bluePen.setWidth(5)
paint.setPen(bluePen)

yellowBrush = QBrush(Qt.GlobalColor.yellow)
paint.setBrush(yellowBrush)

#paint.drawLine(0, 0, 200, 200)
#paint.drawPoint(100, 200)


#paint.drawEllipse(50, 50, 450, 450)

paint.drawLine(width // 3, 0, width // 3, height)
paint.drawLine(2 * width // 3, 0, 2 * width // 3, height)
paint.drawLine(0, height // 3, width, height // 3)
paint.drawLine(0, 2 * height // 3, width, 2 * height // 3)



'''
from random import randint
pen = QPen()
pen.setWidth(10)
paint.setPen(pen)

for n in range(100000):
    pen.setColor(QColor(randint(0, 255), randint(0, 255), randint(0, 255), 255))
    paint.setPen(pen)
    paint.drawPoint(
        300+randint(-300, 300),  # x
        300+randint(-300, 300)   # y
        )

'''
#paint.end()


label.setPixmap(canvas)
#centralWidget.setFixedSize(200, 200)
wnd.setCentralWidget(label)


wnd.setGeometry(200, 200, width, height)
wnd.show()
sys.exit(app.exec())