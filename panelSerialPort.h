#ifndef PANELSERIALPORT_H
#define PANELSERIALPORT_H

#include <QGroupBox>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class PanelSerialPort;
}

class PanelSerialPort : public QGroupBox
{
    Q_OBJECT

public:
    explicit PanelSerialPort(QWidget *parent = nullptr);
    ~PanelSerialPort();

public slots:
    void openSerialPort();
    void closeSerialPort();

private:
    Ui::PanelSerialPort *ui;

    QSerialPort* _serialPort=nullptr;

    void _listSerialPort();
    void _init();

};

#endif // PANELSERIALPORT_H
