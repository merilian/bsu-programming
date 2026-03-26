#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QDateTime>

using namespace std;

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600

class PaintWidget: public QWidget{
public:
    PaintWidget(QWidget* parent = nullptr):
            QWidget(parent){}

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QRect geometry = this->geometry();

        painter.fillRect(geometry, Qt::GlobalColor::white);

        painter.setPen(QPen(Qt::GlobalColor::red, 2));
        painter.drawEllipse(m_x, m_y, m_r*2, m_r*2);

        painter.end();
    }

    void move(uint64_t delta_time){
        m_x = m_x + delta_time*m_V;

        if (m_V > 0 && m_x + m_r > SCREEN_SIZE_X){
            m_x = 0;
        }

        if (m_V < 0 && m_x + m_r < 0){
            m_x = SCREEN_SIZE_X;
        }
    }

    void keyPressEvent(QKeyEvent *event){
        switch (event->key())
        {
        case Qt::Key_Left:
            m_V -= 0.01;
            break;
        case Qt::Key_Right:
            m_V += 0.01;
            break;
        default:
            break;
        }
    }

private:
    double m_V = 0.02;
    double m_x = 0, m_y = 250, m_r = 60;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_centralWidget = new PaintWidget(this);

        this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        this->setCentralWidget(m_centralWidget);

    }

    void run(){
        uint64_t time = QDateTime::currentMSecsSinceEpoch();
        while(m_is_runnig){
            // handle events
            m_app->processEvents();

            // do the math
            uint64_t new_time = QDateTime::currentMSecsSinceEpoch();
            uint64_t delta = new_time - time;
            // std::cout << delta << std::endl;
            m_centralWidget->move(delta);

            // render
            m_centralWidget->repaint();
            time = new_time;
        }
    }

    void keyPressEvent(QKeyEvent *event){
        m_centralWidget->keyPressEvent(event);
    }

    void closeEvent(QCloseEvent *event){
        m_is_runnig = false;
        QMainWindow::closeEvent(event);
    }

private:
    QApplication* m_app;
    PaintWidget* m_centralWidget;
    bool m_is_runnig = true;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}