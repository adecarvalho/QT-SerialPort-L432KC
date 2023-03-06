#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QToolBar>
#include <QMessageBox>
#include<QThread>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>
//


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showAbout();
    void sendAction();
    //
    void openSerial();
    void closeSerial();
    //
    void terminalClear();
    void terminalCopy();
    //
    void readSerialData();


private:
    Ui::MainWindow *ui;

    QSerialPort * _serialPort=nullptr;

    QToolBar* _toolBar=nullptr;

    QString _buffer;

    void _listSerialPort();

    void _afficheLcd(float val);

    void _writeData(const QByteArray & data);

    void _init();

};
#endif // MAINWINDOW_H
