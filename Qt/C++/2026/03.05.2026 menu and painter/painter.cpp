#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include <QPixmap>
#include <QPainter>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    QMainWindow wnd;
    wnd.setGeometry(300, 300, 800, 800);

    QWidget centralWidget(&wnd);
    QVBoxLayout layout(&centralWidget);
    QLabel label;

    QPixmap canvas(800, 500);
    canvas.fill(Qt::white);

    QPainter painter(&canvas);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(5);
    bluePen.setStyle(Qt::PenStyle::DotLine);
    painter.setPen(bluePen);

    QBrush pinkBrush(QColor(173, 67, 111));
    // painter.setBrush(pinkBrush);

    painter.drawRect(100, 100, 600, 300);


    painter.drawRect(10, 10, 150, 150);




    label.setPixmap(canvas);
    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    
    wnd.show();
    return app.exec();
}