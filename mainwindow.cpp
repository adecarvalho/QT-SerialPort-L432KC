#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    _init();
}
//***********************
MainWindow::~MainWindow()
{

    if(_serialPort!= nullptr)
    {
        if(_serialPort->isOpen())
        {
            _serialPort->close();
            delete _serialPort;
        }
    }
    //
    delete ui;
}
//**************************
void MainWindow::showAbout()
{
    QMessageBox::about(this,"About","SAé Graphic Interface\n A.DeCarvalho");
}
//***************************
void MainWindow::sendAction()
{
    const QObject* item=sender();

    if(_serialPort!= nullptr)
    {
        if(_serialPort->isOpen())
        {
            if(item->objectName()=="pushButtonActionLedOn")
            {
                ui->pushButtonActionLedOn->setEnabled(false);
                ui->pushButtonActionLedOff->setEnabled(true);
                const QByteArray val="l";
                _writeData(val);
            }
            //
            if(item->objectName()=="pushButtonActionLedOff")
            {
                ui->pushButtonActionLedOn->setEnabled(true);
                ui->pushButtonActionLedOff->setEnabled(false);
                const QByteArray val="k";
                _writeData(val);
            }
        }
    }
}
//****************************
void MainWindow::openSerial()
{
    if(_serialPort!= nullptr)
    {
        _serialPort->setPortName(ui->comboBoxSerialName->currentText());
        _serialPort->setBaudRate(ui->comboBoxSerialBaud->currentText().toInt());
        _serialPort->setParity(QSerialPort::NoParity);
        _serialPort->setDataBits(QSerialPort::Data8);
        _serialPort->setFlowControl(QSerialPort::NoFlowControl);

        _serialPort->open(QIODevice::ReadWrite);
        connect(_serialPort,SIGNAL(readyRead()),this,SLOT(readSerialData()));

        //
        if(_serialPort->isOpen())
        {
            this->statusBar()->showMessage("SerialPort is ready");
            ui->pushButtonSerialOpen->setEnabled(false);
            ui->pushButtonSerialClose->setEnabled(true);
        }
        else
        {
            this->statusBar()->showMessage("Error SerialPort");
            QMessageBox::critical(this,tr("Error"),_serialPort->errorString());
        }
    }

}
//***************************
void MainWindow::closeSerial()
{
    if(_serialPort!= nullptr)
    {
        _serialPort->close();
        ui->pushButtonSerialClose->setEnabled(false);
        ui->pushButtonSerialOpen->setEnabled(true);
        this->statusBar()->showMessage("SerialPort is close");
    }
}
//*****************************
void MainWindow::terminalClear()
{
    ui->plainTextEditTerminal->clear();
}
//****************************
void MainWindow::terminalCopy()
{
    ui->plainTextEditTerminal->selectAll();
    ui->plainTextEditTerminal->copy();
}
//******************************
void MainWindow::readSerialData()
{
    if(_serialPort!= nullptr)
    {
        QByteArray dataBA=_serialPort->readAll();
        QString data(dataBA);

        ui->plainTextEditTerminal->appendPlainText(data);
        //
        _buffer.append(data);
        int index_T=_buffer.indexOf('T');
        int index_D=-1;

        if(index_T!=-1)
        {
            QString message=_buffer.mid(0,index_T);
            _buffer.remove(0,index_T+1);
            //
            index_D=message.indexOf('D');
            if(index_D !=-1)
            {
                QString tmp=message.mid(index_D+1, message.size());
                float val=tmp.toFloat();

                _afficheLcd(val/10.0);
                //qDebug()<<tmp;
            }
        }
    }
}
//********************************
void MainWindow::_listSerialPort()
{
    //name
    QList<QSerialPortInfo> ports=QSerialPortInfo::availablePorts();
    QList<QString> stringPorts;

    for(int i=0; i< ports.size();i++)
    {
        stringPorts.append(ports.at(i).portName());
    }
    //
    ui->comboBoxSerialName->addItems(stringPorts);
    //
    //baudRate
    QList<qint32> baudRates=QSerialPortInfo::standardBaudRates();
    QList<QString> stringBaudRates;
    int index=0;

    for(int i=0;i<baudRates.size();i++)
    {
        int val=baudRates.at(i);
        if(val==115200)
        {
            index=i;
        }
        stringBaudRates.append(QString::number(val));
    }
    //
    ui->comboBoxSerialBaud->addItems(stringBaudRates);
    ui->comboBoxSerialBaud->setCurrentIndex(index);
}
//************************************
void MainWindow::_afficheLcd(float val)
{
    ui->lcdNumber->display(val);
}
//************************************************
void MainWindow::_writeData(const QByteArray &data)
{
    if(_serialPort!= nullptr)
    {
        if(_serialPort->isOpen())
        {
            _serialPort->write(data);
            QThread::msleep(100);
        }
    }
}
//**********************
void MainWindow::_init()
{
    //
    _serialPort=new QSerialPort(this);
    _listSerialPort();
    _buffer.clear();
    //
    connect(ui->actionExit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    //
    //btn action
    connect(ui->pushButtonActionLedOn,SIGNAL(clicked(bool)),this,SLOT(sendAction()));
    connect(ui->pushButtonActionLedOff,SIGNAL(clicked(bool)),this,SLOT(sendAction()));

    //btn serial
    connect(ui->pushButtonSerialOpen,SIGNAL(clicked(bool)),this,SLOT(openSerial()));
    connect(ui->pushButtonSerialClose,SIGNAL(clicked(bool)),this,SLOT(closeSerial()));
    ui->pushButtonSerialClose->setEnabled(false);
    ui->pushButtonSerialOpen->setEnabled(true);

    //btn terminal
    connect(ui->pushButtonTerminalClear,SIGNAL(clicked(bool)),this,SLOT(terminalClear()));
    connect(ui->pushButtonTerminalCopy,SIGNAL(clicked(bool)),this,SLOT(terminalCopy()));


    //
    _toolBar=this->addToolBar("Fichier");
    _toolBar->setMovable(false);
    _toolBar->setFloatable(false);
    _toolBar->addAction(ui->actionExit);
    _toolBar->addAction(ui->actionAbout);
    //
    this->statusBar()->showMessage("Connect serial port");
    //
}

