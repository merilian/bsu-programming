#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include <QPixmap>
#include <QFileDialog>

using namespace std;

class CustomInput: public QWidget{
public:
    CustomInput(QWidget* parent): QWidget(parent){
        layout = new QVBoxLayout(this);
        input = new QLineEdit(this);
        btn = new QPushButton();

        //QObject::connect(btn, &QPushButton::clicked,
        //    this, &CustomInput::openFile);
        
        layout->addWidget(input);
        layout->addWidget(btn);
        this->setLayout(layout);
    }

    void setText(QString text){
        input->setText(text);
    }

    template <typename TCallback>
    void addBtnClickCallback(const typename QtPrivate::ContextTypeForFunctor<TCallback>::ContextType *actor, TCallback &&callback){
        QObject::connect(btn, &QPushButton::clicked, actor, callback);
    }

    ~CustomInput(){
        delete layout;
        delete input;
        delete btn;
    }

private:
    QVBoxLayout* layout;
    QLineEdit* input;
    QPushButton* btn;

    void openFile(){
        QFileDialog file(this);
        QString filePath = file.getOpenFileName();
        input->setText(filePath);
    }
};

class MainWindow: public QMainWindow{
public:
    MainWindow():QMainWindow(){
        this->setGeometry(300, 300, 600, 600);

        centralWidget = new QWidget(this);
        layout = new QVBoxLayout(centralWidget);
        input = new CustomInput(centralWidget);
        input2 = new CustomInput(centralWidget);

        input->addBtnClickCallback(this, &MainWindow::openFileMain);

        layout->addWidget(input);
        layout->addWidget(input2);
        centralWidget->setLayout(layout);
        this->setCentralWidget(centralWidget);
    }

    ~MainWindow(){
        if (centralWidget != nullptr)
            delete centralWidget;

        delete layout;
        delete input;
        delete input2;
    }

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    CustomInput* input;
    CustomInput* input2;

    void openFileMain(){
        QFileDialog file(this);
        QString filePath = file.getOpenFileName();
        input2->setText(filePath);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd;
    wnd.show();
    return app.exec();
}