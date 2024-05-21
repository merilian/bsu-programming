from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QFileDialog, QLabel
from PyQt6.QtGui import QMouseEvent, QPixmap, QFont, QColor, QPainter, QPen, QBrush, QResizeEvent
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QVBoxLayout, QLineEdit

import sys

width = 1000
height = 500

app = QApplication(sys.argv)
# wnd = QMainWindow()



class Canvas(QWidget):
    def __init__(self, width, height, parent):
        super().__init__(parent)

        self.canvas = QPixmap(width, height)
        self.canvas.fill(Qt.GlobalColor.white)
        self.label = QLabel(self)
        self.label.setPixmap(self.canvas)

        self.customLayout = QVBoxLayout(self)
        self.customLayout.addWidget(self.label) 
        self.setLayout(self.customLayout)
    
    def mouseMoveEvent(self, event):
        paint = QPainter(self.canvas)
        # paint = QPainter(self.label.pixmap())
        
        bluePen = QPen(Qt.GlobalColor.blue)
        bluePen.setWidth(5)
        paint.setPen(bluePen)

        positionL = self.label.pos()
        click = event.position()
        
        paint.drawPoint(int(click.x() - positionL.x()), int(click.y() - positionL.y()))
        paint.end()

        # self.update()
        
        self.label.setPixmap(self.canvas)





class CanvasLabel(QLabel):
    def __init__(self, width, height, parent):
        super().__init__(parent)

        self.bluePen = QPen(Qt.GlobalColor.blue)
        self.bluePen.setWidth(5)

        self.points = []

        self.resize(width, height)
    
    def mouseMoveEvent(self, event):
        paint = QPainter(self.canvas)
        # paint = QPainter(self.pixmap())
        paint.setPen(self.bluePen)

        click = event.position()
        
        self.points.append(click)

        paint.drawPoint(click)
        paint.end()

        # self.update()
        
        self.setPixmap(self.canvas)

    def resize(self, width, height):
        self.canvas = QPixmap(width, height)
        self.canvas.fill(Qt.GlobalColor.white)

        paint = QPainter(self.canvas)
        paint.setPen(self.bluePen)
        for point in self.points:
            paint.drawPoint(point)
        paint.end()

        self.setPixmap(self.canvas)



class MainWnd(QMainWindow):
    def __init__(self):
        super().__init__()

        self.width = 1000
        self.height = 500
        self.setGeometry(200, 200, self.width, self.height)
        self.setMinimumSize(100, 100)

        self.canvas = CanvasLabel(self.width, self.height, self)
        self.setCentralWidget(self.canvas)

    def resizeEvent(self, event: QResizeEvent | None):
        size = event.size()
        # print(size.width(), size.height())
        self.canvas.resize(size.width(), size.height())
        return super().resizeEvent(event)

#canvas = CanvasLabel(width, height, wnd)
#wnd.setCentralWidget(canvas)

wnd = MainWnd()

#wnd.setGeometry(200, 200, width, height)
wnd.show()
sys.exit(app.exec())