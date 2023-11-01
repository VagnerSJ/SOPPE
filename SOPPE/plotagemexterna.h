#ifndef PLOTAGEMEXTERNA_H
#define PLOTAGEMEXTERNA_H

#include <QDialog>

namespace Ui {
class plotagemExterna;
}

class plotagemExterna : public QDialog
{
    Q_OBJECT

public:
    explicit plotagemExterna(QString caminho_Imagem = "", QWidget *parent = nullptr);
    ~plotagemExterna();
    void janela_plotagem_externa(QString caminho_Imagem);

private:
    Ui::plotagemExterna *ui;


};

#endif // PLOTAGEMEXTERNA_H
