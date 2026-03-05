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

class MainMenu: public QMenuBar{
private:
    QAction* drawAction;
    QAction* clearAction;

public:
    MainMenu(QWidget *parent = nullptr): QMenuBar(parent){
        drawAction = new QAction("Draw");
        clearAction = new QAction("Clear");
        this->addAction(drawAction);
        this->addAction(clearAction);
    }

    template <typename Func2>
    void setClearAction(const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot){
        QObject::connect(
            clearAction, &QAction::triggered,
            receiver, slot
        );
    }

    template <typename Func2>
    void setDrawAction(const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot){
        QObject::connect(
            drawAction, &QAction::triggered,
            receiver, slot
        );
    }
};


class MainWindow: public QMainWindow{
private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QLabel* label;
    MainMenu* menuBar;

    void clear(){
        QPixmap canvas(800, 500);
        canvas.fill(Qt::white);
        label->setPixmap(canvas);
    }

    void draw(){
        QPixmap canvas(800, 500);
        
        QPainter painter(&canvas);

        for(int i = 0; i < 100000; ++i){
            QPen bluePen(QColor(rand()%255, rand()%255, rand()%255));
            bluePen.setWidth(rand()%10);
            painter.setPen(bluePen);
            painter.drawPoint(rand()%800, rand()%500);
        }

        label->setPixmap(canvas);
    }

public:
    MainWindow(): QMainWindow(){
        this->setGeometry(300, 300, 800, 800);

        centralWidget = new QWidget(this);
        layout = new QVBoxLayout(centralWidget);
        label = new QLabel();

        menuBar = new MainMenu(this);
        menuBar->setClearAction(this, &MainWindow::clear);
        menuBar->setDrawAction(this, &MainWindow::draw);

        layout->addWidget(label);
        centralWidget->setLayout(layout);
        this->setCentralWidget(centralWidget);
        this->setMenuBar(menuBar);
    }

    ~MainWindow(){
        delete menuBar;
        delete label;
        delete layout;
        delete centralWidget;
    }
};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    MainWindow wnd;
    wnd.show();
    return app.exec();
}