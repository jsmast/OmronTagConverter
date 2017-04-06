#include "widget.h"
#include "ui_widget.h"
#include "tagconverter.h"
#include <QtEndian>
#include <QSettings>
#include <QTextStream>
#include <QTextCodec>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSettings settings("omron_converter_config.ini", QSettings::IniFormat);
    ui->savePath->setText(settings.value("savePath").toString());

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_proceedButton_clicked()
{
    //Получение данных формы
    QString input = ui->inputTextEdit->toPlainText();

    // Конвертер
    TagConverter output;

    // Вывод
    ui->outputTextEdit->setPlainText(output.convert(input));
}

void Widget::on_saveButton_clicked()
{
    // Читаем имя файла для экспорта
    QString savePath = ui->savePath->text();

    // Сохраняем имя файла
    saveSettings(savePath);

    // Создаем файловый декриптор
    QFile file(savePath);

    // Читаем сформированный csv
    QString csv = ui->outputTextEdit->toPlainText();

    // Открываем файл на запись
    file.open(QFile::WriteOnly);

    // Создаем поток
    QTextStream out(&file);

    // Преобразовываем в кодировку USC2(UTF-16) LittleEndian
    out.setCodec("UTF-16LE");

    // Добавляем BOM (Byte Order Mark)
    out.setGenerateByteOrderMark(true);

    // Пишем в файл
    out << csv;

    // Закрываем файл
    file.close();
}
void Widget::saveSettings(QString savePath)
{
    // Сохраняем путь и имя файла для экспорта
    QSettings settings("omron_converter_config.ini", QSettings::IniFormat);
    settings.setValue("savePath", savePath);

}
