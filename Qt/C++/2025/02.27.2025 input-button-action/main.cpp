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

    QObject::connect(&input, &QLineEdit::returnPressed, [&label, &input](){
        label.setText(input.text());
    });

    QPushButton clear(&centralWidget);
    clear.setText("Clear");

    QObject::connect(&clear, &QPushButton::pressed, [&label, &input](){
        input.clear();
        label.setText("");
    });


    layout.addWidget(&label);
    layout.addWidget(&input);
    layout.addWidget(&clear);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    
    wnd.show();
    return app.exec();
}