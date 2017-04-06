/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox;
    QPlainTextEdit *inputTextEdit;
    QPushButton *proceedButton;
    QGroupBox *groupBox_2;
    QPlainTextEdit *outputTextEdit;
    QPushButton *saveButton;
    QLineEdit *savePath;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(666, 592);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/dev-32/dev-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 651, 261));
        inputTextEdit = new QPlainTextEdit(groupBox);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));
        inputTextEdit->setGeometry(QRect(10, 20, 631, 201));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputTextEdit->sizePolicy().hasHeightForWidth());
        inputTextEdit->setSizePolicy(sizePolicy);
        proceedButton = new QPushButton(groupBox);
        proceedButton->setObjectName(QStringLiteral("proceedButton"));
        proceedButton->setGeometry(QRect(540, 222, 101, 31));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 280, 651, 301));
        outputTextEdit = new QPlainTextEdit(groupBox_2);
        outputTextEdit->setObjectName(QStringLiteral("outputTextEdit"));
        outputTextEdit->setGeometry(QRect(10, 20, 631, 241));
        saveButton = new QPushButton(groupBox_2);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(550, 260, 91, 31));
        savePath = new QLineEdit(groupBox_2);
        savePath->setObjectName(QStringLiteral("savePath"));
        savePath->setGeometry(QRect(262, 269, 271, 21));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 270, 31, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Omron Tag Converter", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Widget", "Input", Q_NULLPTR));
        proceedButton->setText(QApplication::translate("Widget", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Widget", "Output", Q_NULLPTR));
        saveButton->setText(QApplication::translate("Widget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\320\244\320\260\320\271\320\273:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
