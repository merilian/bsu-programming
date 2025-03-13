#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include <QPixmap>
#include <QPainter>
#include <QPen>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow wnd;
    wnd.setGeometry(100, 100, 600, 600);

    QWidget centralWidget(&wnd);
    QVBoxLayout layout(&centralWidget);
    QLabel label;


    int width = 1500, height = 1000;


    QPixmap pict(width, height);
    pict.fill(QColorConstants::White);

    QPainter paint(&pict);
    QPen pen(QColorConstants::Blue);
    pen.setWidth(5);
    paint.setPen(pen);

    paint.drawLine(width/3, 0, width/3, height);
    paint.drawLine(2*width/3, 0, 2*width/3, height);
    paint.drawLine(0, height/3, width, height/3);
    paint.drawLine(0, 2*height/3, width, 2*height/3);

    for (int i = 0; i < 100000; ++i){
        QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
        QPen randomColorPen(randomColor);
        randomColorPen.setWidth(10);

        paint.setPen(randomColorPen);
        //paint.drawPoint(rand()%width, rand()%height);        
    }

    // QPicture img;
    // img.load("C:\\Users\\e.derevyago\\Pictures\\Screenshots\\Screenshot 2024-10-04 101950.png");
    // paint.drawPicture(10, 10, img);

    QPixmap img2("C:\\Users\\e.derevyago\\Pictures\\Screenshots\\Screenshot 2024-10-04 101950.png");
    paint.drawPixmap(50, 50, img2);
    

    paint.end();

    
    label.setPixmap(pict);

    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    
    wnd.show();
    return app.exec();
}