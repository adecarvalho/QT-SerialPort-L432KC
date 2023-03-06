#ifndef PANELTERMINAL_H
#define PANELTERMINAL_H

#include <QGroupBox>

namespace Ui {
class PanelTerminal;
}

class PanelTerminal : public QGroupBox
{
    Q_OBJECT

public:
    explicit PanelTerminal(QWidget *parent = nullptr);
    ~PanelTerminal();

private:
    Ui::PanelTerminal *ui;
};

#endif // PANELTERMINAL_H
