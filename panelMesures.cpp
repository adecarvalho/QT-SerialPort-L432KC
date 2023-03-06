#include "panelMesures.h"
#include "ui_panelMesures.h"

PanelMesures::PanelMesures(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PanelMesures)
{
    ui->setupUi(this);
}

PanelMesures::~PanelMesures()
{
    delete ui;
}
