#include "panelSerialPort.h"
#include "ui_panelSerialPort.h"

PanelSerialPort::PanelSerialPort(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PanelSerialPort)
{
    ui->setupUi(this);
    resize(200,300);

    _init();
}
//********************************
PanelSerialPort::~PanelSerialPort()
{
    delete ui;
    if(_serialPort!= nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }
}
//***********************************
 void PanelSerialPort::_init()
 {
    _serialPort= new QSerialPort(this);
    _listSerialPort();
 }
//************************************
void PanelSerialPort::openSerialPort()
{

}
//************************************
void PanelSerialPort::closeSerialPort()
{

}
//*************************************
void PanelSerialPort::_listSerialPort()
{
    QList<QSerialPortInfo> ports=QSerialPortInfo::availablePorts();
    QList<QString> stringPorts;

    //port name
    for(int i=0;i<ports.size();i++)
    {
        stringPorts.append(ports.at(i).portName());
    }
    //
    ui->comboBoxSerialName->addItems(stringPorts);

    //port baud
    QList<qint32> baudRates=QSerialPortInfo::standardBaudRates();
    QList<QString> stringBaudRates;

    for(int i=0; i<baudRates.size();i++)
    {
        stringBaudRates.append(QString::number(baudRates.at(i)));
        qDebug()<<baudRates.at(i);
    }
    ui->comboBoxSerialBaud->addItems(stringBaudRates);
}









