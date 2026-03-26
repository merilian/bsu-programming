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

class Circle{
public:
    void move(uint64_t delta_time){
        m_x = m_x + delta_time*m_V;

        if (m_V > 0 && m_x + m_r > SCREEN_SIZE_X){
            m_x = 0;
        }

        if (m_V < 0 && m_x + m_r < 0){
            m_x = SCREEN_SIZE_X;
        }
    }

    void incSpeed(){
        m_V += 0.01;
    }

    void decSpeed(){
        m_V -= 0.01;
    }

    QRect getRect(){
        return QRect(m_x, m_y, m_r*2, m_r*2);
    }
private:
    double m_V = 0.02;
    double m_x = 0, m_y = 250, m_r = 60;
};

class CircleState{
public:
    CircleState(){
        m_circle = new Circle();
    }

    void tick(uint64_t delta_time){
        m_circle->move(delta_time);
    }

    QRect getCircle(){
        return m_circle->getRect();
    }

    void keyPressed(int key){
        switch (key)
        {
        case Qt::Key_Left:
            m_circle->decSpeed();
            break;
        case Qt::Key_Right:
            m_circle->incSpeed();
            break;
        default:
            break;
        }
    }
private:
    Circle* m_circle;
};

class PaintWidget: public QWidget{
public:
    PaintWidget(CircleState* state, QWidget* parent = nullptr)
        :QWidget(parent){
        m_state = state;
    }

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QRect geometry = this->geometry();

        painter.fillRect(geometry, Qt::GlobalColor::white);

        painter.setPen(QPen(Qt::GlobalColor::red, 2));
        painter.drawEllipse(m_state->getCircle());

        painter.end();
    }

private:
    CircleState* m_state;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_state = new CircleState();
        m_centralWidget = new PaintWidget(m_state, this);

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
            m_state->tick(delta);

            // render
            m_centralWidget->repaint();
            time = new_time;
        }
    }

    void keyPressEvent(QKeyEvent *event) override {
        m_state->keyPressed(event->key());
    }

    void closeEvent(QCloseEvent *event) override {
        m_is_runnig = false;
        QMainWindow::closeEvent(event);
    }

private:
    QApplication* m_app;
    PaintWidget* m_centralWidget;
    CircleState* m_state;
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