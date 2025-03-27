#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>

using namespace std;

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600


class PainterWidget: public QWidget{
public:
    PainterWidget(QWidget* parrent): QWidget(parrent){
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.fillRect(this->geometry(), Qt::GlobalColor::white);
        
        painter.setPen(QPen(Qt::GlobalColor::red, 2));
        painter.drawEllipse(300, 300, 20, 20);
        painter.end();
    }

private:
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_painterWidget = new PainterWidget(this);

        this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        this->setCentralWidget(m_painterWidget);
    }

private:
    QApplication* m_app;
    PainterWidget* m_painterWidget;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    return app.exec();
}