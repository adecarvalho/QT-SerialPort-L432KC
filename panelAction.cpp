#include "panelAction.h"
#include "ui_panelAction.h"

PanelAction::PanelAction(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PanelAction)
{
    ui->setupUi(this);
}

PanelAction::~PanelAction()
{
    delete ui;
}
