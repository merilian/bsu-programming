#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include <QPixmap>

#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>

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
    QLineEdit input(&centralWidget);

    QMenuBar menuBar(&wnd);

    QMenu actionsMenu("Actions");
    QAction fileAction("File");

    // Actions menu
    QAction colorAction("Color");

    QMenu warningsMenu("Allerts");
    QAction warningAction("Warning");
    QAction criticalAction("Critical");
    warningsMenu.addAction(&warningAction);
    warningsMenu.addAction(&criticalAction);

    actionsMenu.addAction(&colorAction);
    actionsMenu.addMenu(&warningsMenu);

    


    menuBar.addMenu(&actionsMenu);
    menuBar.addAction(&fileAction);

    
    QPushButton fontBtn;
    fontBtn.setText("Font");

    QPushButton inputBtn;
    inputBtn.setText("Input");

    QPushButton messageBtn;
    messageBtn.setText("Message");



    // Color
    QObject::connect(&colorAction, &QAction::triggered, [&label](){
        QColorDialog colorDlg;

        QPixmap pict(780, 500);
        pict.fill(colorDlg.getColor());

        label.setPixmap(pict);
    }); 

    // File
     QObject::connect(&fileAction, &QAction::triggered, [&label](){
        QFileDialog fileDlg;
        QString fileName = fileDlg.getOpenFileName();

        QPixmap pict(fileName);
        pict.scaledToHeight(700);
        label.setPixmap(fileName);
    }); 

    // Font
     QObject::connect(&fontBtn, &QPushButton::clicked, [&label](){
        QFontDialog fontDlg;
        bool ok;
        QFont font = fontDlg.getFont(&ok);

        label.setFont(font);
        label.setText("     Pu-pu");
    }); 

    // Input
     QObject::connect(&inputBtn, &QPushButton::clicked, [&label, &centralWidget](){
        QInputDialog inputDlg;
        bool ok;
        QString text = inputDlg.getMultiLineText(&centralWidget, "Title", "Label");

        label.setText(text);
    }); 

    // Message
     QObject::connect(&warningAction, &QAction::triggered, [&label, &centralWidget](){
        QMessageBox messageDlg;

        messageDlg.warning(&centralWidget, "Title", "ALLERT 2", QMessageBox::Abort, QMessageBox::No);
    }); 
    QObject::connect(&criticalAction, &QAction::triggered, [&label, &centralWidget](){
        QMessageBox messageDlg;

        messageDlg.critical(&centralWidget, "Title", "ALLERT 5000", QMessageBox::Abort, QMessageBox::No);
    }); 


    layout.addWidget(&input);
    layout.addWidget(&fontBtn);
    layout.addWidget(&inputBtn);
    layout.addWidget(&messageBtn);
    layout.addWidget(&label);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    wnd.setMenuBar(&menuBar);
    
    wnd.show();
    return app.exec();
}