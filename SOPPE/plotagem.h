#ifndef PLOTAGEM_H
#define PLOTAGEM_H

#include <QDialog>

namespace Ui {
class plotagem;
}

class plotagem : public QDialog
{
    Q_OBJECT

public:
    explicit plotagem(QWidget *parent = nullptr);
    ~plotagem();

private:
    Ui::plotagem *ui;

    void janela_plotagem();
};

#endif // PLOTAGEM_H
