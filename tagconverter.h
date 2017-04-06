#ifndef TAGCONVERTER_H
#define TAGCONVERTER_H

#include <QString>
#include <QMap>
#include <QRegExp>

struct SymbolStruct{
    QString tagName;
    QString dataType;
    QString addrArea;
    QString area;
    QString addr;
};

struct TagStruct{
    QString AddrTagName;
    QString AddrHMIID = "0";
    QString AddrPLCID = "0";
    QString DataType;
    QString AddrType;
    QString Addr;
    QString AddrCodeType = "0";

};

class TagConverter
{
public:
    TagConverter();
    QString convert(QString input);
    bool isBase(QString type);
    bool isStruct(QString type);
private:
    QMap<QString, QString> addrBits;
    QMap<QString, QString> addrWords;
    QMap<QString, int> baseTypes;
    QMap<QString, QMap<QString,QString>> plcStruct;

    QList<SymbolStruct> parseInput(QString input);
    QList<TagStruct> symbolsToTags(QList<SymbolStruct> symbols);
    QString tagsToCsv(QList<TagStruct> tags);
    QString getStruct(QString name, QString addrArea, QString structName, QList<SymbolStruct>* out);
    SymbolStruct getBaseSymbol(QString name, QString type, QString addrArea);


};

#endif // TAGCONVERTER_H
