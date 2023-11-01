#include "mainsoppe.h"
#include "plotagem.h"
#include "instrucoesplot.h"
#include "saida.h"
#include "ui_saida.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QThread>
#include <QProcess>
#include <QtDebug>
#include <QFileDialog>

Saida::Saida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Saida)
{
    QThread::sleep(1);
    ui->setupUi(this);
    bool primeiraVez = true;
    if(primeiraVez)
    {
        montar_saida();
        primeiraVez = false;
    }
}

Saida::~Saida()
{
    delete ui;
}

void Saida::on_btn_plotar_imagem_saida_clicked()
{
    instrucoesplot instrucoes;
    QProcess executar;
    QFile::copy(QDir::currentPath() + "/soppe_image.dat", QDir::currentPath() + "/GNUPLOT_SCRIPTS_VISUALIZATION/soppe_image.dat");
    executar.setWorkingDirectory(QDir::currentPath() + "/GNUPLOT_SCRIPTS_VISUALIZATION");
    executar.start("/bin/bash", QStringList() << "-c" << "gnome-terminal -- ./gnuplot_images_SOPPE.gpl soppe_image.dat");
    executar.waitForFinished(-1);
    QThread::sleep(1);

    plotagem plot;
    plot.exec();
}

void Saida::montar_saida()
{
    QString local = QDir::currentPath();
    QString nome_saida_gpu = "/SOPPE_GPU_base_inputs.out";
    QString nome_saida_cpu = "/SOPPE_CPU_base_inputs.out";
    QString nome_arquivo_entradas_base = "/SOPPE_base_inputs.in";

    MainSoppe *mainSoppe = new MainSoppe();
    QString modo = mainSoppe->get_modo_simulacao();

    if(modo == "GPU"){
        QFile arquivo(local + nome_saida_gpu);
        if(!arquivo.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this, "ERRO", "Nao foi possivel abrir o arquivo " + nome_saida_gpu);
        }

        QTextStream saida_gpu(&arquivo);
        QString saida = saida_gpu.readAll();

        ui->plainTextEdit_arquivo_saida->setPlainText(saida);
        ui->listWidget_arquivo_saida_lista->addItem(nome_saida_gpu);
        arquivo.close();
    }
    else if(modo == "CPU"){
        QFile arquivo(local + nome_saida_cpu);
        if(!arquivo.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this, "ERRO", "Nao foi possivel abrir o arquivo " + nome_saida_cpu);
        }

        QTextStream saida_cpu(&arquivo);
        QString saida = saida_cpu.readAll();

        ui->plainTextEdit_arquivo_saida->setPlainText(saida);
        ui->listWidget_arquivo_saida_lista->addItem(nome_saida_cpu);
        arquivo.close();
    }

    QString secao_detector = "SECTION IMAGE DETECTOR v.2009-12-02";
    QString secao_dose = "SECTION DOSE DEPOSITION v.2012-12-12";

    QString linha;
    int linhas_buscadas = 0;
    bool linha_encontrada = false;
    QString parametro_detector = "";
    QString parametro_dose = "";
    bool preencher_detector = true;
    bool preencher_dose = true;

    QFile arquivo_entradas_base(local + nome_arquivo_entradas_base);
    if(!arquivo_entradas_base.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "O arquivo com as entradas iniciais não pode ser aberto!");
    }

    QTextStream entradas_base(&arquivo_entradas_base);

    do{
        linha = entradas_base.readLine();

        //############### DETECTOR DE IMAGEM ##############
        if(linha.contains(secao_detector, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 4 && preencher_detector){
            if(linhas_buscadas == 0){
                parametro_detector = linha.split('#')[0].trimmed();
                QString nomeSaida = parametro_detector.split('/').last();

                ui->listWidget_arquivo_saida_lista->addItem(nomeSaida);
                ui->listWidget_arquivo_saida_lista->addItem(nomeSaida + ".raw");

                linha_encontrada = false;
                preencher_detector = false;
                linhas_buscadas = 0;
            }
            else{
                linhas_buscadas++;
            }

            continue;
        }

        //############### DOSE DEPOSITADA ##############
        if(linha.contains(secao_dose, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 6 && preencher_dose){
            if(linhas_buscadas == 2){
                parametro_dose = linha.split('#')[0].trimmed();
                QString nomeSaida = parametro_dose.split('/').last();

                ui->listWidget_arquivo_saida_lista->addItem(nomeSaida);
                ui->listWidget_arquivo_saida_lista->addItem(nomeSaida + ".raw");
                ui->listWidget_arquivo_saida_lista->addItem(nomeSaida + "_2sigma.raw");

                linha_encontrada = false;
                preencher_dose = false;
                linhas_buscadas = 0;
            }
            else{
                linhas_buscadas++;
            }

            continue;
        }
    }while(!linha.isNull());
}

