#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //
    setWindowTitle("L432KC SAE");
    resize(565,450);
    //
    _serialPort= new QSerialPort(this);

    //btn clear Terminal
    connect(ui->pushButtonClearTerminal,SIGNAL(clicked(bool)),this,SLOT(clearTerminal()));

    //btn send commande Led ON or OFF
    _setBtnCommandState(false);
    connect(ui->pushButtonLedOn,SIGNAL(clicked(bool)),this,SLOT(sendCommande()));
    connect(ui->pushButtonLedOff,SIGNAL(clicked(bool)),this,SLOT(sendCommande()));

    //
    _listSerialPort();
    //
    ui->pushButtonOpen->setEnabled(true);
    connect(ui->pushButtonOpen,SIGNAL(clicked(bool)),this,SLOT(openSerialPort()));

    ui->pushButtonClose->setEnabled(false);
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(closeSerialPort()));

    ui->lineEditSerialStatus->setText("Pas de port série choisi");

}
//***************
Widget::~Widget()
{
    closeSerialPort();
    delete ui;
}
//***************************
void Widget::openSerialPort()
{
    _serialPort->setPortName(ui->comboBoxName->currentText());
    _serialPort->setBaudRate(ui->comboBoxBaudRate->currentText().toInt());
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setFlowControl(QSerialPort::NoFlowControl);

    _serialPort->open(QIODevice::ReadWrite);
    _serialPort->readAll();

    connect(_serialPort,SIGNAL(readyRead()),this,SLOT(readData()));

    if(_serialPort->isOpen())
    {
        ui->lineEditSerialStatus->setText("Serial Port ready");
        ui->pushButtonOpen->setEnabled(false);
        ui->pushButtonClose->setEnabled(true);
        _setBtnCommandState(true);
    }
    else
    {
        ui->lineEditSerialStatus->setText("Serial Port Error");
        _setBtnCommandState(false);
        QMessageBox::critical(this, tr("Error"), _serialPort->errorString());

    }
}
//****************************
void Widget::closeSerialPort()
{
    if(_serialPort->isOpen())
    {
      _serialPort->close();
      ui->pushButtonClose->setEnabled(false);
      ui->pushButtonOpen->setEnabled(true);
      _setBtnCommandState(false);

      ui->lineEditSerialStatus->setText("Serial Port Close");
    }
}
//*******************************************
void Widget::_writeData(const QByteArray &data)
{
    if(_serialPort->isOpen())
    {
        _serialPort->write(data);
        QThread::msleep(100);
    }
}
//******************************************
void Widget::_setBtnCommandState(bool state)
{
    ui->pushButtonLedOn->setEnabled(state);
    ui->pushButtonLedOff->setEnabled(state);
}
//*********************************
void Widget::_afficheLcd(float val)
{
    ui->lcdNumber->display(val);
}
//*********************
void Widget::readData()
{
    QByteArray dataBA = _serialPort->readAll();
    QString data(dataBA);

    //
    _buffer.append(data);

    int index_T = _buffer.indexOf('T');
    int index_D=-1;

    if(index_T != -1){
        QString message = _buffer.mid(0,index_T);

        //qDebug()<<message;

        ui->console->appendPlainText(message+'T');
        _buffer.remove(0,index_T+1);
        //
        index_D=message.indexOf('D');
        //
        if(index_D != -1)
        {
            QString tmp=message.mid(index_D+1,message.size());
            float val=tmp.toFloat();

            _afficheLcd(val/10.0);
            //qDebug()<<tmp;
        }
    }
}
//**************************
void Widget::clearTerminal()
{
    ui->console->clear();
}
//************************
void Widget::sendCommande()
{
    const QObject *item=sender();
    //qDebug()<<item->objectName();

    if(_serialPort->isOpen())
    {
        if(item->objectName()=="pushButtonLedOn")
        {
            ui->pushButtonLedOn->setEnabled(false);
            ui->pushButtonLedOff->setEnabled(true);
            const QByteArray val("l");
            _writeData(val);
        }
        //
        if(item->objectName()=="pushButtonLedOff")
        {
            ui->pushButtonLedOn->setEnabled(true);
            ui->pushButtonLedOff->setEnabled(false);
            const QByteArray val("k");
            _writeData(val);
        }
    }
}
//****************************
void Widget::_listSerialPort()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    QList<QString> stringPorts;

    //the ports name
    for(int i = 0 ; i < ports.size() ; i++)
    {
        stringPorts.append(ports.at(i).portName());
        //qDebug()<<ports.at(i).portName();
    }
    //
    ui->comboBoxName->addItems(stringPorts);

    //the ports baud rate
    QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();

    QList<QString> stringBaudRates;
    //
    for(int i = 0 ; i < baudRates.size() ; i++)
    {
        stringBaudRates.append(QString::number(baudRates.at(i)));
        //qDebug()<<baudRates.at(i);
    }
    //
    ui->comboBoxBaudRate->addItems(stringBaudRates);
    ui->comboBoxBaudRate->setCurrentIndex(baudRates.size()-3);
}










