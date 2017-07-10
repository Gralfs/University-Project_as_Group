#ifndef SERIALINPUTPARSER_H
#define SERIALINPUTPARSER_H

#include <QString>
#include <QList>


struct SerialInput {
    QString licht;
    QString temp;

    SerialInput(QString licht, QString temp) {
        this->licht = licht;
        this->temp = temp;
    }

    SerialInput(int licht, int temp) {
        this->licht = licht;
        this->temp = temp;
    }
};

class SerialInputParser {

private:
    QString buffer;
    QList<SerialInput> data;

    SerialInput parseInputBlock(QString inputBlock);

public:
    SerialInputParser();

    void clearData();
    bool addInputString(QString input);
    QList<SerialInput>* getData() { return &(this->data); }
};

#endif // SERIALINPUTPARSER_H
