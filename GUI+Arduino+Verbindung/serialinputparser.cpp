#include <QDebug>

#include "serialinputparser.h"

SerialInputParser::SerialInputParser() {

}

// Interpretiert einen vollständigen Input Block vom arduino.
SerialInput SerialInputParser::parseInputBlock(QString inputBlock) {
    QStringList values = inputBlock.split(',');

    // the block should contain exactly two values, light and temp
    if (values.length() != 2) {
        qDebug() << "invalid input block detected: " << inputBlock << endl;
        return SerialInput(0, 0);
    }

    return SerialInput(values.at(0), values.at(1));
}

// Nimmt neuen arduino-input und sucht nach vollständigen Blöcken.
bool SerialInputParser::addInputString(QString input) {
    bool newBlock = false;

    // add new input to the buffer
    this->buffer += input;

    // check, whether there is a complete block
    while(this->buffer.indexOf('|') != -1) {
        newBlock = true;

        // extract block
        int pos = this->buffer.indexOf('|');
        QString block = this->buffer.left(pos);
        this->buffer.remove(0, pos + 1);

        // parse block and add to list
        SerialInput parsedBlock = this->parseInputBlock(block);
        this->data.append(parsedBlock);
    }

    return newBlock;
}

void SerialInputParser::clearData() {
    this->data.clear();
}
