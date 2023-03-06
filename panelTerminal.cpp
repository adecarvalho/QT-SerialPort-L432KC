#include "panelTerminal.h"
#include "ui_panelTerminal.h"

PanelTerminal::PanelTerminal(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PanelTerminal)
{
    ui->setupUi(this);
    resize(300,300);
}

PanelTerminal::~PanelTerminal()
{
    delete ui;
}
