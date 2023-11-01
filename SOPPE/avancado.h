#ifndef AVANCADO_H
#define AVANCADO_H

#include <QDialog>

namespace Ui {
class Avancado;
}

class Avancado : public QDialog
{
    Q_OBJECT

public:
    explicit Avancado(QWidget *parent = nullptr);
    ~Avancado();

private slots:
    void on_btn_salvar_avancado_clicked();

    void preencher_parametros_avancado();

    void on_pushButton_material_clicked();

    QString copiar_arquivo_para_pasta_base();

    void on_pushButton_fonte_energia_clicked();

    void on_pushButton_geometria_clicked();

    void on_pushButton_material_remover_clicked();

private:
    Ui::Avancado *ui;
};

#endif // AVANCADO_H
