#ifndef SAIDA_H
#define SAIDA_H

#include <QDialog>

namespace Ui {
class Saida;
}

class Saida : public QDialog
{
    Q_OBJECT

public:
    explicit Saida(QWidget *parent = nullptr);
    ~Saida();

private slots:
    void on_btn_plotar_imagem_saida_clicked();

    void montar_saida();

private:
    Ui::Saida *ui;
};

#endif // SAIDA_H
