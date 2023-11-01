#include "plotagemexterna.h"
#include "ui_plotagemexterna.h"
#include <QPixmap>
#include <QPropertyAnimation>

plotagemExterna::plotagemExterna(QString caminho_Imagem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotagemExterna)
{
    ui->setupUi(this);

    janela_plotagem_externa(caminho_Imagem);
}

plotagemExterna::~plotagemExterna()
{
    delete ui;
}

void plotagemExterna::janela_plotagem_externa(QString caminho_Imagem)
{
    QString nome_Imagem = "soppe_image.png";
    QPixmap imagem(caminho_Imagem + "/" + nome_Imagem);
    ui->label_imagem_externa->setPixmap(imagem.scaled(600, 600, Qt::KeepAspectRatio));
    ui->plainTextEdit_mensagem_imagens_externa->setPlainText("A demais imagens geradas podem ser encontradas em " + caminho_Imagem);
}
