#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void saveSettings(QString savePath = "");

private slots:
    void on_proceedButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
