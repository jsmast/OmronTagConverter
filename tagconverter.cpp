#include "tagconverter.h"

TagConverter::TagConverter()
{
    addrBits["A"]   = "59";
    addrBits["CIO"] = "50";
    addrBits["D"]   = "60";
    addrBits["H"]   = "56";
    addrBits["W"]   = "53";

    addrWords["A"]   = "2";
    addrWords["CIO"] = "35";
    addrWords["D"]   = "0";
    addrWords["H"]   = "3";
    addrWords["W"]   = "1";

    baseTypes["BOOL"] = 0;
    baseTypes["UINT"] = 2;
    baseTypes["UDINT"] = 4;

    QMap<QString,QString> infoStruct;
    infoStruct["COUNT"] = "UDINT";
    infoStruct["TOTAL_COUNT"] = "UDINT";
    infoStruct["SPEED"] = "UDINT";
    plcStruct["INFO_STRUCT"] = infoStruct;

    QMap<QString,QString> statesStruct;
    statesStruct.insert("INIT","BOOL");
    statesStruct.insert("ERROR","BOOL");
    statesStruct.insert("WARNING","BOOL");
    statesStruct.insert("RUN","BOOL");
    statesStruct.insert("STOPPING","BOOL");
    statesStruct.insert("STOP","BOOL");
    plcStruct.insert("STATES",statesStruct);

    QMap<QString,QString> plcSStruct;
    plcSStruct.insert("MODE", "UINT");
    plcSStruct.insert("STATE", "STATES");
    plcSStruct.insert("WARNINGS", "BOOL");
    plcSStruct.insert("ERRORS", "BOOL");
    plcSStruct.insert("CLEAN", "BOOL");
    plcSStruct.insert("START", "BOOL");
    plcSStruct.insert("STOP", "BOOL");
    plcSStruct.insert("RESET", "BOOL");
    plcSStruct.insert("FULL_RESET", "BOOL");
    plcStruct.insert("PLC_STRUCT",plcSStruct);

}

QString TagConverter::convert(QString input)
{
    return tagsToCsv(symbolsToTags(parseInput(input)));
}

// Функция проверки, является ли тип базовым
bool TagConverter::isBase(QString type)
{
    return baseTypes.contains(type);
}

// Функция проверки, является ли тип структурой
bool TagConverter::isStruct(QString type)
{
    return type == QString("STRUCT");
}
QString TagConverter::getStruct(QString name, QString addrArea, QString structName, QList<SymbolStruct>* out)
{
    QRegExp rx("(\[a-zA-Z]+)");
    int pos = rx.indexIn(addrArea);
    QString area = rx.capturedTexts().at(0);
    QString addr = addrArea.mid(area.length());
    int word = addr.toInt();
    int bit = 0;

    qDebug(structName.toStdString().c_str());
    // Если эта структура неизвестная возвращаем false
    if(!plcStruct.contains(structName)) return QString("false");

    QMap<QString,QString> symbols = plcStruct.value(structName);
    QList<QString> keys = symbols.keys();

    for(int i = 0; i < keys.size(); i++){
        QString type = symbols.value(keys.at(i));
        if(isBase(type)){
            switch(baseTypes.value(type))
            {
                case 0: addrArea = QString("%1%2.%3").arg(area).arg(word).arg(bit);
                        bit++;
                        if(bit == 16){
                            bit = 0;
                            word++;
                        }
                break;

                case 2: addrArea = QString("%1%2").arg(area).arg(word);
                word++;
                break;

                case 4: addrArea = QString("%1%2").arg(area).arg(word);
                word += 2;
                break;
            }

            out->append(getBaseSymbol(QString("%1_%2").arg(name,keys.at(i)),type,addrArea));
        } else {
            addrArea = getStruct(QString("%1_%2").arg(name,keys.at(i)),addrArea,type,out);
        }
    }
    return addrArea;
}
SymbolStruct TagConverter::getBaseSymbol(QString name, QString type, QString addrArea)
{
    QRegExp rx("(\[a-zA-Z]+)");
    SymbolStruct symbol;
    symbol.tagName = name;
    symbol.dataType = type;
    symbol.addrArea = addrArea;

    int pos = rx.indexIn(addrArea);
    symbol.area = rx.capturedTexts().at(0);
    symbol.addr = symbol.addrArea.mid(symbol.area.length());

    if(symbol.area.length() == 0) symbol.area = "CIO";

    return symbol;
}

// Разбор данных на массив символов
QList<SymbolStruct> TagConverter::parseInput(QString input)
{
    // Разбор данных на строки
    QStringList inputStrings = input.split("\n");

    // Определение символов
    QList<SymbolStruct> symbols;

    // Разбор строки на элементы структуры symbols
    // Проходим по каждой строке, кроме последней пустой
    for(int i = 0; i < inputStrings.size() - 1; i++){

        // Разбиваем строку на массив полей
        QStringList tempCols = inputStrings.at(i).split("\t");

        // Если поле адреса пустое (автоматически генерируемое) пропускаем символ
        if(!tempCols.at(2).length()) continue;

        if(isStruct(tempCols.at(1))){
            //qDebug("Is Struct");
            //qDebug("Struct name: %s",tempCols.at(5).toStdString().c_str());
            //qDebug("Recurcive: %s",getStruct(tempCols.at(0),tempCols.at(2),tempCols.at(5)).toStdString().c_str());
            //qDebug("%s",getStruct(tempCols.at(0),tempCols.at(2),tempCols.at(5),"").toStdString().c_str());
            //getStruct(tempCols.at(0),tempCols.at(2),tempCols.at(5),&symbols);
        }

        // Если тип данных не соответсвует базовому пропускаем этот символ
        //if(!baseTypes.contains(tempCols.at(1))) continue;
        if(!isBase(tempCols.at(1))) continue;

        symbols.append(getBaseSymbol(tempCols.at(0),tempCols.at(1),tempCols.at(2)));
    }
    return symbols;
}

// Конвертирование символов в csv формат
QList<TagStruct> TagConverter::symbolsToTags(QList<SymbolStruct> symbols)
{
    // Массив тегов
    QList<TagStruct> tags;

    // Проходим по списку символов
    for(int i = 0; i < symbols.size(); i++){

        // Формируем тег
        TagStruct tag;
        tag.AddrTagName = symbols.at(i).tagName;

        // Если тип данных BOOL
        if(symbols.at(i).dataType == "BOOL"){
            // Если адресная зона не известна, пропускаем символ
            if(!addrBits.contains(symbols.at(i).area)) continue;

            // Тип данных бит
            tag.DataType = "0";

            // Тип адреса
            tag.AddrType = addrBits[symbols.at(i).area];

        } else { // Если тип данных WORD
            // Если адресная зона не известна, пропускаем символ
            if(!addrWords.contains(symbols.at(i).area)) continue;

            // Тип данных слово
            tag.DataType = "2";

            // Тип адреса
            tag.AddrType = addrWords[symbols.at(i).area];
        }
        // Заполняем адрес
        tag.Addr = symbols.at(i).addr;

        // Добавляем тег в список
        tags.append(tag);
    }
    return tags;
}

QString TagConverter::tagsToCsv(QList<TagStruct> tags)
{
    QString csv = "\"AddrTag Lib\"\t\"V100\"\n";
    csv.append("\"AddrTagName\"\t\"AddrHMIID\"\t\"AddrPLCID\"\t\"DataType\"\t\"AddrType\"\t\"Addr\"\t\"AddrCodeType\"\n");
    for(int i = 0; i < tags.size(); i++){
        csv.append(
                    QString("\"%1\"\t\"%2\"\t\"%3\"\t\"%4\"\t\"%5\"\t\"%6\"\t\"%7\"\n")
                    .arg(tags.at(i).AddrTagName)
                    .arg(tags.at(i).AddrHMIID)
                    .arg(tags.at(i).AddrPLCID)
                    .arg(tags.at(i).DataType)
                    .arg(tags.at(i).AddrType)
                    .arg(tags.at(i).Addr)
                    .arg(tags.at(i).AddrCodeType)
                    );
    }
    return csv;
}
