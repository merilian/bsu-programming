#include <iostream>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

using namespace std;

class JsonSave{
public:
    QString Name;
    JsonSave(): Name("custom name"), coordinate(2.2736587), m_count(5){}

    QJsonObject toJson(){
        QJsonObject json;
        json["name"] = Name;
        json["coordinate"] = coordinate;
        json["m_count"] = m_count;
        return json;
    }

    void fromJson(QJsonObject json){
        const QJsonValue v = json["name"];
        if (v.isString())
            Name = v.toString();

        const QJsonValue v1 = json["coordinate"];
        if (v1.isDouble())
            coordinate = v1.toDouble();

        const QJsonValue v2 = json["m_count"];
        if (v2.isDouble())
            m_count = v2.toInt();
    }
protected:
    double coordinate;
private:
    int m_count;
};

int main(int argc, char *argv[])
{
    JsonSave js;
    QJsonObject json = js.toJson();

    QFile loadFile("save.json");

    // write
    if (!loadFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    loadFile.write(QJsonDocument(json).toJson());
    loadFile.close();
    

    // read
    // if (!loadFile.open(QIODevice::ReadOnly)) {
    //     qWarning("Couldn't open save file.");
    //     return false;
    // }
    // QByteArray saveData = loadFile.readAll();
    // QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    // js.fromJson(loadDoc.object());

    // qDebug() << js.Name;
}