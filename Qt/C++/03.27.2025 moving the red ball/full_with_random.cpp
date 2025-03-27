#include <iostream>
#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QDateTime>
#include <QMouseEvent>
#include <QRandomGenerator>

using namespace std;

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600
#define SIMULATION_SPEED 300


class Circle{
public:
    Circle(float x, float y, float r, float lineSize, QColor color): 
        m_x(x), m_y(y), m_r(r),
         m_velocity(0), m_acceleration(50),
          m_lineSize(lineSize), m_color(color){}

    QRect getRect() const { return QRect(m_x-m_r, m_y-m_r, 2*m_r - m_lineSize, 2*m_r - m_lineSize); }
    QColor getColor() const { return m_color; }
    int getLineSize() const { return m_lineSize*2; }

    void move(float deltaTime){
        if (!m_isMoving){
            return;
        }

        float newY = m_y + m_velocity*deltaTime + m_acceleration*deltaTime*deltaTime/2;
        float newVelocity = m_velocity + m_acceleration*deltaTime;
        if (newY + m_r > SCREEN_SIZE_Y){
            float len = SCREEN_SIZE_Y - m_y - m_r;
            float deltaTimeDown = (-m_velocity + sqrt(m_velocity*m_velocity + 2*m_acceleration*len)) / m_acceleration;
            float delatTimeUp = deltaTime - deltaTimeDown;

            float bottomVelocity = m_velocity + m_acceleration*deltaTimeDown;
            bottomVelocity = -bottomVelocity;
            //bottomVelocity *= 0.4f;

            newY = float(SCREEN_SIZE_Y - m_r) + bottomVelocity*delatTimeUp + m_acceleration*delatTimeUp*delatTimeUp/2;

            newVelocity = bottomVelocity + m_acceleration*delatTimeUp;
        }

        m_y = newY;
        m_velocity = newVelocity;

        if (m_y != m_y || m_velocity != m_velocity){
            m_isMoving = false;
            m_y = SCREEN_SIZE_Y - m_r;
            m_velocity = 0;
            m_acceleration = 0;
        }
    }

private:
    float m_x, m_y, m_r;
    float m_velocity, m_acceleration;
    bool m_isMoving = true;

    QColor m_color;
    int m_lineSize;
};

class PainterWidget: public QWidget{
public:
    PainterWidget(QWidget* parrent, const vector<Circle>& circles): QWidget(parrent), m_circles(circles){
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.fillRect(this->geometry(), Qt::GlobalColor::white);
        
        for(const Circle& circle: m_circles){
            painter.setPen(QPen(circle.getColor(), circle.getLineSize()));
            painter.drawEllipse(circle.getRect());
        }
        painter.end();
    }

private:
    const vector<Circle> &m_circles;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_circles.clear();
        m_painterWidget = new PainterWidget(this, m_circles);

        this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        this->setCentralWidget(m_painterWidget);
    }

    void run(){
        uint64_t time = QDateTime::currentMSecsSinceEpoch();
        while(m_isRunning){
            m_app->processEvents();
            uint64_t newTime = QDateTime::currentMSecsSinceEpoch();
            float deltaTime = float(newTime - time)/SIMULATION_SPEED;

            for(Circle& circle: m_circles){
                circle.move(deltaTime);
            }
            this->repaint();
            time = newTime;
        }
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        m_isRunning = false;
        QMainWindow::closeEvent(event);
    }

    void mousePressEvent(QMouseEvent* event) override{
        if (event->button() == Qt::LeftButton) {
            QPoint clickPoint = event->pos();
            float radius = QRandomGenerator::global()->generate()%60 + 20;
            float lineSize = QRandomGenerator::global()->generate()%5 + 1;
            QColor color(QRandomGenerator::global()->generate()%256, QRandomGenerator::global()->generate()%256, QRandomGenerator::global()->generate()%256);
            m_circles.emplace_back(clickPoint.x(), clickPoint.y(), radius, lineSize, color);
        }
    }

private:
    QApplication* m_app;
    PainterWidget* m_painterWidget;
    vector<Circle> m_circles;
    bool m_isRunning = true;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}