#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include <QPixmap>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow wnd;
    wnd.setGeometry(300, 300, 600, 600);

    QWidget centralWidget(&wnd);
    QVBoxLayout layout(&centralWidget);
    QLabel label;
    QLineEdit input(&centralWidget);
    input.setText("C:\\Users\\e.derevyago\\Pictures\\Screenshots\\Screenshot 2024-10-04 101950.png");
    QPushButton btn;

    QObject::connect(&btn, &QPushButton::clicked, [&label, &input, &wnd]() {
        // "C:\Users\e.derevyago\Pictures\Screenshots\Screenshot 2024-10-04 101950.png"
        // "C:\Users\e.derevyago\Pictures\Screenshots\Screenshot 2024-01-25 143017.png"

        QFileDialog file(&wnd);
        QString filePath = file.getOpenFileName();

        input.setText(filePath);

        QPixmap picture(filePath);
        picture = picture.scaled(580, 500);
        label.setPixmap(picture);
    });
    
    QPushButton btnColor;
    btnColor.setText("Color");

    QObject::connect(&btnColor, &QPushButton::clicked, [&btnColor, &input, &wnd]() {
        QColorDialog colorDlg(&wnd);
        QColor color = colorDlg.getColor();
        QPalette plt(color);
        btnColor.setPalette(plt);
    });

    QPushButton btnFont;
    btnFont.setText("Font");

    QObject::connect(&btnFont, &QPushButton::clicked, [&btnFont, &input, &wnd]() {
        QFontDialog fontDlg(&wnd);
        QFont font = fontDlg.getFont(0, btnFont.font());
        btnFont.setFont(font);
    });

    QPushButton btnInput;
    btnInput.setText("Input");

    QObject::connect(&btnInput, &QPushButton::clicked, [&btnInput, &input, &wnd]() {
        QInputDialog inputDlg(&wnd);
        QString txt = inputDlg.getMultiLineText(&wnd, "Title", "Label");
        btnInput.setText(txt);
    });

    QPushButton btnMessage;
    btnMessage.setText("Message");

    QObject::connect(&btnMessage, &QPushButton::clicked, [&btnMessage, &input, &wnd]() {
        QMessageBox messageBox(&wnd);
        messageBox.question(&wnd, "Title", "To be or not to be");
    });

    layout.addWidget(&input);
    layout.addWidget(&btn);
    layout.addWidget(&btnColor);
    layout.addWidget(&btnFont);
    layout.addWidget(&btnInput);
    layout.addWidget(&btnMessage);
    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    
    wnd.show();
    return app.exec();
}