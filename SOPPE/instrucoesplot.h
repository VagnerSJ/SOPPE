#ifndef INSTRUCOESPLOT_H
#define INSTRUCOESPLOT_H

#include <QDialog>

namespace Ui {
class instrucoesplot;
}

class instrucoesplot : public QDialog
{
    Q_OBJECT

public:
    explicit instrucoesplot(QWidget *parent = nullptr);
    ~instrucoesplot();

private:
    Ui::instrucoesplot *ui;
};

#endif // INSTRUCOESPLOT_H
