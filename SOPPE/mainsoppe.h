#ifndef MAINSOPPE_H
#define MAINSOPPE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainSoppe; }
QT_END_NAMESPACE

class MainSoppe : public QMainWindow
{
    Q_OBJECT

public:
    MainSoppe(QWidget *parent = nullptr);
    ~MainSoppe();

    QString get_modo_simulacao();

    void preencher_parametros();

private slots:
    void on_pushButton_material_basico_clicked();

    void on_btn_avancado_clicked();

    void on_btn_executar_clicked();

    void on_btn_salvar_clicked();

    QString copiar_arquivo_para_pasta_base();

    void on_pushButton_fonteEnergia_basico_clicked();

    void on_pushButton_geometria_basico_clicked();

    void on_pushButton_remover_material_clicked();

    void on_btn_plot_externo_clicked();

private:
    Ui::MainSoppe *ui;
};
#endif // MAINSOPPE_H
