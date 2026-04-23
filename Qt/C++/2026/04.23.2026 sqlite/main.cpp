#include <iostream>

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

using namespace std;

int main(int argc, char *argv[])
{
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lect_2.db");
    cout << db.open() << endl;

    // QSqlError err = db.lastError();
    // qDebug() << err;

    // err = db.lastError();
    // qDebug() << err;

    QSqlQuery selectPeopleQuery("select * from people order by id desc");
    selectPeopleQuery.exec();

    while(selectPeopleQuery.next()){
        cout << selectPeopleQuery.value(0).toInt()
             << "  "
             << selectPeopleQuery.value(1).toString().toStdString()
             << endl;
    }




    db.close();
}