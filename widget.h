#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include<QMessageBox>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void openSerialPort();
    void closeSerialPort();

    void readData();
    void clearTerminal();
    void sendCommande();

private:
    Ui::Widget *ui;
    QSerialPort * _serialPort=nullptr;
    QSerialPortInfo* _serialPortInfo=nullptr;
    QString _buffer;

    void _listSerialPort();
    void _writeData(const QByteArray & data);
    void _setBtnCommandState(bool state);
    void _afficheLcd(float val);
};
#endif // WIDGET_H
