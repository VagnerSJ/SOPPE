#include "instrucoesplot.h"
#include "ui_instrucoesplot.h"

instrucoesplot::instrucoesplot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instrucoesplot)
{
    ui->setupUi(this);
}

instrucoesplot::~instrucoesplot()
{
    delete ui;
}
