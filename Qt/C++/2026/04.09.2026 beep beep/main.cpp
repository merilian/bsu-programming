#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QDateTime>

#include <QMediaPlayer>
#include <QAudioOutput>

using namespace std;

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600

class PaintWidget: public QWidget{
public:
    PaintWidget(QWidget* parent = nullptr):
            QWidget(parent){
                m_text = new QString("0");
                m_textColor = new QColor(0, 0, 0);
                m_hits = 0;

                m_player = new QMediaPlayer();
                m_output = new QAudioOutput();

                m_player->setAudioOutput(m_output);
                m_player->setSource(QUrl::fromLocalFile("/home/merilian/Downloads/song.mp3"));
                m_player->play();
            }

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QRect geometry = this->geometry();

        painter.fillRect(geometry, Qt::GlobalColor::white);
        painter.setPen(QPen(*m_textColor, 20));

        QFont font = painter.font();
        font.setPixelSize(250);
        painter.setFont(font);

        painter.drawText(100, 300, *m_text);

        painter.end();
    }

    void keyPressEvent(QKeyEvent *event){
        qint64 pos = m_player->position();

        qint64 step = 476;
        qint64 start_dif = 325;

        qint64 dif = (pos - start_dif) % step;
        bool hit = min(dif, step-dif) < 60;

        cout << dif << "  " << step-dif << "  " << pos << endl;

        if (hit){
            m_hits++;
            m_textColor = new QColor(0, 255, 0);
        }
        else{
            m_hits--;
            m_textColor = new QColor(255, 0, 0);
        }

        m_text = new QString(QString::number(m_hits));
    }

private:
    QString* m_text;
    QColor* m_textColor;
    QMediaPlayer* m_player;
    QAudioOutput* m_output;
    int m_hits;
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



    // QApplication app(argc, argv);
    // QMainWindow wnd;
    // wnd.setGeometry(300, 300, 500, 500);

    // QMediaPlayer player;
    // QAudioOutput output;

    // player.setAudioOutput(&output);
    // player.setSource(QUrl::fromLocalFile("/home/merilian/Downloads/song.mp3"));
    // player.play();

    // wnd.show();
    // return app.exec();

}