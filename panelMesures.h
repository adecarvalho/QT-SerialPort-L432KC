#ifndef PANELMESURES_H
#define PANELMESURES_H

#include <QGroupBox>

namespace Ui {
class PanelMesures;
}

class PanelMesures : public QGroupBox
{
    Q_OBJECT

public:
    explicit PanelMesures(QWidget *parent = nullptr);
    ~PanelMesures();

private:
    Ui::PanelMesures *ui;
};

#endif // PANELMESURES_H
