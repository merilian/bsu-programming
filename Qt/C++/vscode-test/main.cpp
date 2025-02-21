#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow wnd;
    wnd.setGeometry(300, 300, 900, 600);

    QWidget centralWidget(&wnd);
    QVBoxLayout layout(&centralWidget);
    QLabel label;
    label.setText("Hello there from vs code (:");

    QLineEdit input(&centralWidget);

    QPushButton btn;

    QObject::connect(&btn, &QPushButton::clicked, [&label, &input]() {
        label.setText(input.text());
    });

    layout.addWidget(&input);
    layout.addWidget(&btn);
    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    
    wnd.show();
    return app.exec();
}