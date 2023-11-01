#include "plotagem.h"
#include "ui_plotagem.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QFileDialog>

plotagem::plotagem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotagem)
{
    ui->setupUi(this);

    plotagem::janela_plotagem();
}

plotagem::~plotagem()
{
    delete ui;
}

void plotagem::janela_plotagem()
{
    QString nome_Imagem = "soppe_image.png";
    QString caminho_Imagem = QDir::currentPath() + "/GNUPLOT_SCRIPTS_VISUALIZATION";
    QPixmap imagem(caminho_Imagem + "/" + nome_Imagem);
    ui->label_imagem->setPixmap(imagem.scaled(600, 600, Qt::KeepAspectRatio));
    ui->plainTextEdit_mensagem_imagens->setPlainText("A demais imagens geradas podem ser encontradas em " + caminho_Imagem);
}
