#ifndef PANELACTION_H
#define PANELACTION_H

#include <QGroupBox>

namespace Ui {
class PanelAction;
}

class PanelAction : public QGroupBox
{
    Q_OBJECT

public:
    explicit PanelAction(QWidget *parent = nullptr);
    ~PanelAction();

private:
    Ui::PanelAction *ui;
};

#endif // PANELACTION_H
