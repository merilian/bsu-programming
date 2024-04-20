from TestWindow import TestWindow

from PyQt6.QtWidgets import QApplication

import sys

app = QApplication(sys.argv)
wnd = TestWindow()
wnd.show()

sys.exit(app.exec())