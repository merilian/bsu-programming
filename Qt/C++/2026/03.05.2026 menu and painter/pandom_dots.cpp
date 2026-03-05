#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include <QPixmap>
#include <QPainter>

#include <QMenuBar>
#include <QMenu>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    QMainWindow wnd;
    wnd.setGeometry(300, 300, 800, 800);

    QWidget centralWidget(&wnd);
    QVBoxLayout layout(&centralWidget);
    QLabel label;

    QMenuBar menuBar(&wnd);

    QAction draw("Draw");
    QAction clear("Clear");
    menuBar.addAction(&draw);
    menuBar.addAction(&clear);


    QObject::connect(&clear, &QAction::triggered, [&label](){
        QPixmap canvas(800, 500);
        canvas.fill(Qt::white);
        label.setPixmap(canvas);
    }); 

    QObject::connect(&draw, &QAction::triggered, [&label](){
        QPixmap canvas(800, 500);
        
        QPainter painter(&canvas);

        for(int i = 0; i < 100000; ++i){
            QPen bluePen(QColor(rand()%255, rand()%255, rand()%255));
            bluePen.setWidth(rand()%10);
            painter.setPen(bluePen);
            painter.drawPoint(rand()%800, rand()%500);
        }

        label.setPixmap(canvas);
    }); 


    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    wnd.setMenuBar(&menuBar);
    
    wnd.show();
    return app.exec();
}