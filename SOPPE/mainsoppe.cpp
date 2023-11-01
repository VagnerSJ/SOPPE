#include "mainsoppe.h"
#include "plotagemexterna.h"
#include "qthread.h"
#include "ui_mainsoppe.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtDebug>
#include "avancado.h"
#include "saida.h"

QString modoSimulação;
QStringList materiais_antigos;
QStringList materiais_novos;

MainSoppe::MainSoppe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSoppe)
{
    ui->setupUi(this);
    preencher_parametros();
    //ui->radioButton_modo_gpu->setChecked(true);
}

MainSoppe::~MainSoppe()
{
    delete ui;
}


QString MainSoppe::get_modo_simulacao()
{
    qDebug() << modoSimulação;
    return modoSimulação;
}


void MainSoppe::on_btn_avancado_clicked()
{
    const QString mensagemAlertaOpcoesAvancadas = "Os parâmetros são sensiveis e podem alterar completamente os resultados da simulação. Deseja continuar?";
    QMessageBox::StandardButton respostaBotaoAvancado = QMessageBox::question(this, "Cuidado", mensagemAlertaOpcoesAvancadas, QMessageBox::Yes | QMessageBox::No);

    Avancado opcoesAvancadas;
    if(respostaBotaoAvancado == QMessageBox::Yes){
        this->close();
        opcoesAvancadas.exec();
    }
}


void MainSoppe::on_btn_executar_clicked()
{
    QProcess executar_source;
    executar_source.setWorkingDirectory(QDir::currentPath());
    executar_source.startCommand("source .bashrc");
    executar_source.waitForBytesWritten();
    if(!executar_source.waitForFinished(1000)){
        executar_source.kill();
        executar_source.waitForFinished(1000);
    }

    if(ui->radioButton_modo_gpu->isChecked()){
        on_btn_salvar_clicked();
        modoSimulação = "GPU";
        QProcess executar;
        executar.setWorkingDirectory(QDir::currentPath());
        executar.start("/bin/bash", QStringList() << "-c" << "./SOPPE.x SOPPE_base_inputs.in | tee SOPPE_GPU_base_inputs.out");
        executar.waitForBytesWritten();

        bool acabou = executar.waitForFinished(-1);
        Saida opcaoSaida;

        if(acabou == true){
            opcaoSaida.exec();
        }

        if(!executar.waitForFinished(-1)){
            executar.kill();
            executar.waitForFinished(1000);
        }
    }
    else if(ui->radioButton_modo_cpu->isChecked()){
        on_btn_salvar_clicked();
        modoSimulação = "CPU";
        QProcess executar;
        executar.setWorkingDirectory(QDir::currentPath());
        executar.start("/bin/bash", QStringList() << "-c" << "./SOPPE_CPU.x SOPPE_base_inputs.in | tee SOPPE_CPU_base_inputs.out");
        executar.waitForBytesWritten();

        bool acabou = executar.waitForFinished(-1);
        Saida opcaoSaida;

        if(acabou == true){
            opcaoSaida.exec();
        }

        if(!executar.waitForFinished(1000)){
            executar.kill();
            executar.waitForFinished(1000);
        }
    }
    else{
        const QString mensagemAlertaEscolhaModo = "Por favor, escolha um modo de simulação!";
        QMessageBox::warning(this, "Alerta", mensagemAlertaEscolhaModo);
    }
}

void MainSoppe::preencher_parametros()
{
    QString local_arquivo_entradas_base = QDir::currentPath();
    QString nome_arquivo_entradas_base = "/SOPPE_base_inputs.in";

    QString secao_simulacao = "SECTION SIMULATION CONFIG v.2009-05-12";
    QString secao_fonte = "SECTION SOURCE v.2011-07-12";
    QString secao_geometria = "SECTION VOXELIZED GEOMETRY FILE v.2009-11-30";
    QString secao_materiais = "SECTION MATERIAL FILE LIST v.2009-11-30";

    QFile arquivo_entradas_base(local_arquivo_entradas_base + nome_arquivo_entradas_base);
    if(!arquivo_entradas_base.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "O arquivo com as entradas iniciais não pode ser aberto!");
    }

    QTextStream entradas_base(&arquivo_entradas_base);

    QString linha;
    bool linha_encontrada = false;
    QString num_historias = "";
    QString fonte = "";
    QString geometria = "";
    QStringList materiais;
    bool sem_materiais = false;

    do{
        linha = entradas_base.readLine();

        //Historias
        if(linha.contains(secao_simulacao, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && num_historias == ""){
            num_historias = linha.split('#')[0].trimmed();
            ui->textEdit_num_historia_basico->clear();
            ui->textEdit_num_historia_basico->setPlainText(num_historias);
            linha_encontrada = false;
            continue;
        }

        //Fonte
        if(linha.contains(secao_fonte, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && fonte == ""){
            fonte = linha.split('#')[0].trimmed();
            ui->field_fonteEnergia_basico->setText(fonte);
            ui->field_fonteEnergia_basico->repaint();
            linha_encontrada = false;
            continue;
        }

        //Geometria
        if(linha.contains(secao_geometria, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && geometria == ""){
            geometria = linha.split('#')[0].trimmed();
            ui->field_geometria_basico->setText(geometria);
            ui->field_geometria_basico->repaint();
            linha_encontrada = false;
            continue;
        }

        //Materiais
        if(linha.contains(secao_materiais, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && sem_materiais == false){
            QString material = linha.split('#')[0].trimmed();
            if(material != ""){
                materiais.append(linha.split('#')[0].trimmed());
                materiais_antigos.append(linha.split('#')[0].trimmed());
                materiais_novos.append(linha.split('#')[0].trimmed());
                ui->listWidget_material_lista_basico->addItem(material);
                continue;
            }
            else{
                ui->listWidget_material_lista_basico->repaint();
                break;
            }
        }
    }while(!linha.isNull());

    arquivo_entradas_base.close();



    //ui->textEdit_num_historia_basico->setPlainText(num_historias);
    //ui->field_fonteEnergia_basico->setText(fonte);
    //ui->field_geometria_basico->setText(geometria);
    //foreach(QString material, materiais){
    //   ui->listWidget_material_lista_basico->addItem(material);
    //}
    //ui->field_material_basico->setText(materiais);

    //QString num_historias = entradas_base.getLine
}

void MainSoppe::on_btn_salvar_clicked()
{
    QString local_arquivo_entradas_base = QDir::currentPath();
    QString nome_arquivo_entradas_base = "/SOPPE_base_inputs.in";

    QString secao_simulacao = "SECTION SIMULATION CONFIG v.2009-05-12";
    QString secao_fonte = "SECTION SOURCE v.2011-07-12";
    //QString secao_detector = "SECTION IMAGE DETECTOR v.2009-12-02";
    //QString secao_ct = "SECTION CT SCAN TRAJECTORY v.2011-10-25";
    //QString secao_dose = "SECTION DOSE DEPOSITION v.2012-12-12";
    QString secao_geometria = "SECTION VOXELIZED GEOMETRY FILE v.2009-11-30";
    QString secao_materiais = "SECTION MATERIAL FILE LIST v.2009-11-30";

    QFile arquivo_entradas_base(local_arquivo_entradas_base + nome_arquivo_entradas_base);
    if(!arquivo_entradas_base.open(QFile::ReadWrite|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "O arquivo com as entradas iniciais não pode ser aberto!");
    }

    QTextStream entradas_base(&arquivo_entradas_base);

    QString linha;
    //int linhas_buscadas = 0;
    bool linha_encontrada = false;
    QString num_historias = "";
    QString fonte = "";
    QString geometria = "";
    //QStringList materiais;
    bool sem_materiais = false;
    QString texto_entrada_modificada = "";
    int index_material = 0;

    do{
        linha = entradas_base.readLine();

        //Historias
        if(linha.contains(secao_simulacao, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && num_historias == ""){
            num_historias = linha.split('#')[0].trimmed();
            //ui->textEdit_num_historia_basico->setPlainText(num_historias);
            linha_encontrada = false;
            texto_entrada_modificada += linha.replace(num_historias, ui->textEdit_num_historia_basico->toPlainText()) + '\n';
            continue;
        }

        //Fonte
        if(linha.contains(secao_fonte, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && fonte == ""){
            fonte = linha.split('#')[0].trimmed();
            //ui->field_fonteEnergia_basico->setText(fonte);
            linha_encontrada = false;
            texto_entrada_modificada += linha.replace(fonte, ui->field_fonteEnergia_basico->text()) + '\n';
            continue;
        }

        //Geometria
        if(linha.contains(secao_geometria, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && geometria == ""){
            geometria = linha.split('#')[0].trimmed();
            //ui->field_geometria_basico->setText(geometria);
            linha_encontrada = false;
            qDebug() << geometria;
            qDebug() << ui->field_geometria_basico->text();
            texto_entrada_modificada += linha.replace(geometria, ui->field_geometria_basico->text()) + '\n';
            continue;
        }

        //Materiais
        if(linha.contains(secao_materiais, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';

            materiais_novos.clear();

            for (int x = 0; x < ui->listWidget_material_lista_basico->count(); x++)
            {
                materiais_novos.append(ui->listWidget_material_lista_basico->item(x)->text());
            }

            continue;
        }
        else if(linha_encontrada == true && sem_materiais == false){
            QString material = linha.split('#')[0].trimmed();

            if(index_material < materiais_novos.count() && material != ""){
                texto_entrada_modificada += linha.replace(material, materiais_novos[index_material]) + '\n';
                index_material++;
                continue;
            }
            else if(index_material < materiais_novos.count() && material == ""){
                texto_entrada_modificada += materiais_novos[index_material] + "                #  " + linha.split('#')[1].trimmed() + '\n';
                index_material++;
                continue;
            }
            else if(index_material >= materiais_novos.count() && material != ""){
                texto_entrada_modificada += "                                                           #  " + linha.split('#')[1].trimmed() + '\n';
                index_material++;
                continue;
            }
            else{
                sem_materiais = true;
                linha_encontrada = false;
                texto_entrada_modificada += linha + '\n';
                continue;
            }
        }

        if(linha == "# >>>> END INPUT FILE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"){
            texto_entrada_modificada += linha;
            break;
        }
        else{
            texto_entrada_modificada += linha + '\n';
        }

    }while(!linha.isNull());

    index_material = 0;
    materiais_novos.clear();

    foreach (QString mat, materiais_novos) {
        qDebug() << mat;
    }

    arquivo_entradas_base.resize(0);
    entradas_base << texto_entrada_modificada;
    arquivo_entradas_base.flush();
    arquivo_entradas_base.close();

    //ui->textEdit_num_historia_basico->setPlainText(num_historias);
    //ui->field_fonteEnergia_basico->setText(fonte);
    //ui->field_geometria_basico->setText(geometria);
    //foreach(QString material, materiais){
    //   ui->listWidget_material_lista_basico->addItem(material);
    //}
    //ui->field_material_basico->setText(materiais);

    //QString num_historias = entradas_base.getLine
}

QString MainSoppe::copiar_arquivo_para_pasta_base()
{
    QString filtro = "Todos os Arquivos (*.*) ;; Arquivo de texto (*.txt)";
    QString local_documentos = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString local_arquivo_entradas_base = QDir::currentPath() + "/";
    QString abrir_arquivo = QFileDialog::getOpenFileName(this, "Abrir", local_documentos, filtro);
    QFileInfo arquivo_info(abrir_arquivo);

    QString nome_arquivo_copia = arquivo_info.fileName();
    QString caminho_arquivo_copia = arquivo_info.absoluteFilePath();

    if (QFile::exists(local_arquivo_entradas_base + nome_arquivo_copia))
    {
        QFile::remove(local_arquivo_entradas_base + nome_arquivo_copia);
    }

    QFile::copy(caminho_arquivo_copia, local_arquivo_entradas_base + nome_arquivo_copia);

    return local_arquivo_entradas_base + nome_arquivo_copia;
}

void MainSoppe::on_pushButton_fonteEnergia_basico_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    ui->field_fonteEnergia_basico->setText(arquivo_copiado);
}


void MainSoppe::on_pushButton_geometria_basico_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    ui->field_geometria_basico->setText(arquivo_copiado);
}


void MainSoppe::on_pushButton_material_basico_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    //ui->listWidget_material_lista_basico->addItem(ui->field_material_basico->text());
    ui->listWidget_material_lista_basico->addItem(arquivo_copiado);
    materiais_novos.append(arquivo_copiado);
    ui->field_material_basico->clear();
}




void MainSoppe::on_pushButton_remover_material_clicked()
{
    const QString mensagem = "O material selecionado será removido da listagem. Deseja continuar?";
        QMessageBox::StandardButton resposta = QMessageBox::question(this, "Cuidado", mensagem, QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes){
        QListWidgetItem *material_selecionado = ui->listWidget_material_lista_basico->currentItem();
        materiais_novos.removeOne(material_selecionado->text());

        delete material_selecionado;

        ui->listWidget_material_lista_basico->setCurrentRow(-1);

        qDebug() << "lista nova de materiais";
        foreach (QString mat, materiais_novos) {
            qDebug() << mat;
        }
    }
}


void MainSoppe::on_btn_plot_externo_clicked()
{
    QString filtro = "Todos os Arquivos (*.*) ;; Arquivo de texto (*.txt)";
    QString local_documentos = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString local_arquivo_arquivos_externos = QDir::currentPath() + "/Arquivos_Externos";
    QString abrir_arquivo = QFileDialog::getOpenFileName(this, "Abrir", local_documentos, filtro);
    QFileInfo arquivo_info(abrir_arquivo);

    QString nome_arquivo_copia = arquivo_info.fileName();
    QString caminho_arquivo_copia = arquivo_info.absoluteFilePath();

    QDir pasta_arquivos_externos(local_arquivo_arquivos_externos);
    if(!pasta_arquivos_externos.exists()){
        pasta_arquivos_externos.mkpath(".");
    }

    QDir pasta_arquivo_externo(local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0]);
    if(!pasta_arquivo_externo.exists()){
        pasta_arquivo_externo.mkpath(".");
    }
    else{
        pasta_arquivo_externo.removeRecursively();
        pasta_arquivo_externo.mkpath(".");
    }

    QFile::copy(caminho_arquivo_copia, local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0] + "/" + nome_arquivo_copia);
    QFile::copy(caminho_arquivo_copia, local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0] + "/soppe_image.dat");

    QProcess executar;
    QFile::copy(QDir::currentPath() + "/GNUPLOT_SCRIPTS_VISUALIZATION/gnuplot_images_SOPPE.gpl", local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0] + "/gnuplot_images_SOPPE.gpl");
    QThread::sleep(1);
    executar.setWorkingDirectory(local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0]);
    executar.start("/bin/bash", QStringList() << "-c" << "gnome-terminal -- ./gnuplot_images_SOPPE.gpl " + nome_arquivo_copia);
    executar.waitForFinished(-1);
    QThread::sleep(1);
    QFile::remove(local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0] + "/gnuplot_images_SOPPE.gpl");
    QFile::remove(local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0] + "/soppe_image.dat");
    QThread::sleep(1);

    plotagemExterna *plot = new plotagemExterna(local_arquivo_arquivos_externos + "/" + nome_arquivo_copia.split(".")[0]);
    plot->exec();
}

