#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

using namespace std;

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600

class PaintWidget: public QWidget{
public:
    PaintWidget(QWidget* parent = nullptr):
            QWidget(parent), m_ellipce(60, 60){
                m_up = false;
                m_down = false;
                m_left = false;
                m_right = false;

                m_moveTimer = new QTimer(this);
                connect(m_moveTimer, &QTimer::timeout, this, &PaintWidget::move);
                m_moveTimer->start(20);
                setMouseTracking(true);
            }

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QRect geometry = this->geometry();

        // painter.fillRect(geometry, Qt::GlobalColor::white);

        painter.drawEllipse(m_ellipce, 50, 50);

        painter.end();
    }

    void mousePressEvent(QMouseEvent *event){
        if (event->button() != Qt::LeftButton){
            return;
        }

        m_ellipce = event->position().toPoint();
        this->repaint();
    }

    void mouseMoveEvent(QMouseEvent *event){
        // if (event->button() != Qt::RightButton){
        //     return;
        // }

        m_ellipce = event->position().toPoint();
        this->repaint();
    }

    void keyPressEvent(QKeyEvent *event){
        switch (event->key())
        {
        case Qt::Key_W:
            m_up = true;
            break;
        case Qt::Key_S:
            m_down = true;
            break;
        case Qt::Key_A:
            m_left = true;
            break;
        case Qt::Key_D:
            m_right = true;
            break;
        default:
            break;
        }

        // move();

        // if (!m_moveTimer->isActive()){
        //     m_moveTimer->start(20);
        // }
    }

    void keyReleaseEvent(QKeyEvent *event){
        if (event->isAutoRepeat()){
            return;
        }

        switch (event->key())
        {
        case Qt::Key_W:
            m_up = false;
            break;
        case Qt::Key_S:
            m_down = false;
            break;
        case Qt::Key_A:
            m_left = false;
            break;
        case Qt::Key_D:
            m_right = false;
            break;
        default:
            break;
        }

        // if(!m_up && !m_down && !m_left && !m_right){
        //     m_moveTimer->stop();
        // }
    }

    void move(){
        if (m_up)
            m_ellipce.setY(m_ellipce.y() - 1);

        if (m_down)
            m_ellipce.setY(m_ellipce.y() + 1);
        
        if (m_left)
            m_ellipce.setX(m_ellipce.x() - 1);
        
        if (m_right)        
            m_ellipce.setX(m_ellipce.x() + 1);

        this->repaint();
    }

private:
    QPoint m_ellipce;
    bool m_up, m_down, m_left, m_right;
    QTimer* m_moveTimer;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_centralWidget = new PaintWidget(this);

        this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        this->setCentralWidget(m_centralWidget);

    }

    void keyPressEvent(QKeyEvent *event){
        m_centralWidget->keyPressEvent(event);
    }

    void keyReleaseEvent(QKeyEvent *event){
        std::cout << event->key() << std::endl;
        m_centralWidget->keyReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event){
        m_centralWidget->mouseMoveEvent(event);
    }

private:
    QApplication* m_app;
    PaintWidget* m_centralWidget;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    return app.exec();
}