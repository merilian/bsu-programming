from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt6.QtCore import Qt

from PyQt6.QtWidgets import QMenuBar, QMenu
from PyQt6.QtGui import QAction

import sys

app = QApplication(sys.argv)
wnd = QMainWindow()
wnd.setGeometry(200, 200, 450, 450)

centralWidget = QLabel("Default text")
centralWidget.setAlignment(
    Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignVCenter)
wnd.setCentralWidget(centralWidget)

menuBar = QMenuBar(wnd)
stateMItem = QMenu("State")
editMItem = QMenu("Edit")
menuBar.addMenu(stateMItem)
menuBar.addMenu(editMItem)

loadMenuAction = QAction("Load")
stateMItem.addAction(loadMenuAction)

def loadActionHandler():
    import json
    data = json.load(open('json/out.json'))
    centralWidget.setText(data['text'])

loadMenuAction.triggered.connect(loadActionHandler)


saveMenuAction = QAction("Save")
stateMItem.addAction(saveMenuAction)

def saveActionHandler():
    import json
    toSave = {
        'text': "Saved to file text"
    }
    json.dump(toSave, open('json/out.json', 'w'), indent=2)

saveMenuAction.triggered.connect(saveActionHandler)




dropdownMenu = QMenu("Dropdown")
dropdownMenu.addAction("Option 1")
dropdownMenu.addAction("Option 3")
dropdownMenu.addAction("Option 2")

editMItem.addMenu(dropdownMenu)




wnd.show()

sys.exit(app.exec())