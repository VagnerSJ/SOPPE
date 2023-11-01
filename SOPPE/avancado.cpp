#include "mainsoppe.h"
#include "avancado.h"
#include "ui_avancado.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtDebug>

QStringList materiais_antigos_avancado;
QStringList materiais_novos_avancado;

Avancado::Avancado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Avancado)
{
    ui->setupUi(this);
    preencher_parametros_avancado();
}

Avancado::~Avancado()
{
    delete ui;
}

void Avancado::preencher_parametros_avancado()
{
    QString local_arquivo_entradas_base = QDir::currentPath();
    QString nome_arquivo_entradas_base = "/SOPPE_base_inputs.in";

    QString secao_simulacao = "SECTION SIMULATION CONFIG v.2009-05-12";
    QString secao_fonte = "SECTION SOURCE v.2011-07-12";
    QString secao_detector = "SECTION IMAGE DETECTOR v.2009-12-02";
    QString secao_ct = "SECTION CT SCAN TRAJECTORY v.2011-10-25";
    QString secao_dose = "SECTION DOSE DEPOSITION v.2012-12-12";
    QString secao_geometria = "SECTION VOXELIZED GEOMETRY FILE v.2009-11-30";
    QString secao_materiais = "SECTION MATERIAL FILE LIST v.2009-11-30";

    QFile arquivo_entradas_base(local_arquivo_entradas_base + nome_arquivo_entradas_base);
    if(!arquivo_entradas_base.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "O arquivo com as entradas iniciais não pode ser aberto!");
    }

    QTextStream entradas_base(&arquivo_entradas_base);

    QString linha;
    int linhas_buscadas = 0;
    bool linha_encontrada = false;
    QString parametro_simulacao = "";
    QString parametro_fonte = "";
    QString parametro_detector = "";
    QString parametro_ct = "";
    QString parametro_dose = "";
    QString parametro_geometria = "";
    //QStringList parametro_materiais;
    bool sem_materiais = false;
    bool preencher_simulacao = true;
    bool preencher_fonte = true;
    bool preencher_detector = true;
    bool preencher_ct = true;
    bool preencher_dose = true;
    bool preencher_geometria = true;

    do{
        linha = entradas_base.readLine();

        //############### SIMULACAO ##############
        if(linha.contains(secao_simulacao, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 5 && preencher_simulacao){
            parametro_simulacao = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                ui->field_num_historia->setPlainText(parametro_simulacao);
            }
            else if(linhas_buscadas == 1){
                ui->field_semente->setPlainText(parametro_simulacao);
            }
            else if(linhas_buscadas == 2){
                ui->field_num_gpu_mpi->setPlainText(parametro_simulacao);
            }
            else if(linhas_buscadas == 3){
                ui->field_num_thread_bloco->setPlainText(parametro_simulacao);
            }
            else if(linhas_buscadas == 4){
                ui->field_num_historia_thread->setPlainText(parametro_simulacao);
            }

            linhas_buscadas++;

            if(linhas_buscadas == 5){
                linha_encontrada = false;
                preencher_simulacao = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou simulacao";
            continue;
        }

        //############### FONTE ##############
        if(linha.contains(secao_fonte, Qt::CaseInsensitive)){
            linha_encontrada = true;
            qDebug() << linha_encontrada;
            qDebug() << linhas_buscadas;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 4 && preencher_fonte){
            parametro_fonte = linha.split('#')[0].trimmed();
            qDebug() << linhas_buscadas;
            if(linhas_buscadas == 0){
                ui->field_fonte_energia->setText(parametro_fonte);
            }
            else if(linhas_buscadas == 1){
                QStringList parametro_fonte_aux = parametro_fonte.split(' ');
                parametro_fonte_aux.removeAll("");
                ui->field_posicao_fonte_x->setPlainText(parametro_fonte_aux[0].trimmed());
                ui->field_posicao_fonte_y->setPlainText(parametro_fonte_aux[1].trimmed());
                ui->field_posicao_fonte_z->setPlainText(parametro_fonte_aux[2].trimmed());
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_fonte_aux = parametro_fonte.split(' ');
                parametro_fonte_aux.removeAll("");
                ui->field_coseno_fonte_u->setPlainText(parametro_fonte_aux[0].trimmed());
                ui->field_coseno_fonte_v->setPlainText(parametro_fonte_aux[1].trimmed());
                ui->field_coseno_fonte_w->setPlainText(parametro_fonte_aux[2].trimmed());
            }
            else if(linhas_buscadas == 3){
                QStringList parametro_fonte_aux = parametro_fonte.split(' ');
                parametro_fonte_aux.removeAll("");
                ui->field_abertura_polar->setPlainText(parametro_fonte_aux[0].trimmed());
                ui->field_abertura_azimutal->setPlainText(parametro_fonte_aux[1].trimmed());
            }

            linhas_buscadas++;

            if(linhas_buscadas == 4){
                linha_encontrada = false;
                preencher_fonte = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou fonte";
            continue;
        }

        //############### DETECTOR DE IMAGEM ##############
        if(linha.contains(secao_detector, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 4 && preencher_detector){
            parametro_detector = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                QStringList parametro_detector_aux = parametro_detector.split('/');
                parametro_detector_aux.removeAll("");
                ui->lineEdit_nome_arquivo_saida_imagem->setText(parametro_detector_aux.last());
            }
            else if(linhas_buscadas == 1){
                QStringList parametro_detector_aux = parametro_detector.split(' ');
                parametro_detector_aux.removeAll("");
                ui->field_num_pixel_imagem_x->setPlainText(parametro_detector_aux[0].trimmed());
                ui->field_num_pixel_imagem_z->setPlainText(parametro_detector_aux[1].trimmed());
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_detector_aux = parametro_detector.split(' ');
                parametro_detector_aux.removeAll("");
                ui->field_num_dimensao_imagem_x->setPlainText(parametro_detector_aux[0].trimmed());
                ui->field_num_dimensao_imagem_z->setPlainText(parametro_detector_aux[1].trimmed());
            }
            else if(linhas_buscadas == 3){
                ui->field_distancia_fonte_detector->setPlainText(parametro_detector);
            }

            linhas_buscadas++;

            if(linhas_buscadas == 4){
                linha_encontrada = false;
                preencher_detector = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou detector";
            continue;
        }

        //############### CT ##############
        if(linha.contains(secao_ct, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 5 && preencher_ct){
            parametro_ct = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                ui->field_num_projecao->setText(parametro_ct);
            }
            else if(linhas_buscadas == 1){
                ui->field_angulo_projecao->setPlainText(parametro_ct);
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_ct_aux = parametro_ct.split(' ');
                parametro_ct_aux.removeAll("");
                ui->field_angulo_interesse_inicial->setPlainText(parametro_ct_aux[0].trimmed());
                ui->field_angulo_interesse_final->setPlainText(parametro_ct_aux[1].trimmed());
            }
            else if(linhas_buscadas == 3){
                ui->field_distancia_fonte_rotacao->setPlainText(parametro_ct);
            }
            else if(linhas_buscadas == 4){
                ui->field_translacao_projecao->setPlainText(parametro_ct);
            }

            linhas_buscadas++;

            if(linhas_buscadas == 5){
                linha_encontrada = false;
                preencher_ct = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou ct";
            continue;
        }

        //############### DOSE DEPOSITADA ##############
        if(linha.contains(secao_dose, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 6 && preencher_dose){
            parametro_dose = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                if(parametro_dose == "YES"){
                    ui->radioButton_contagem_dose_material_sim->setChecked(true);
                }
                else if(parametro_dose == "NO"){
                    ui->radioButton_contagem_dose_material_nao->setChecked(true);
                }
            }
            else if(linhas_buscadas == 1){
                if(parametro_dose == "YES"){
                    ui->radioButton_contagem_dose_voxel_sim->setChecked(true);
                }
                else if(parametro_dose == "NO"){
                    ui->radioButton_contagem_dose_voxel_nao->setChecked(true);
                }
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_dose_aux = parametro_dose.split('/');
                parametro_dose_aux.removeAll("");
                ui->lineEdit_nome_arquivo_saida_dose->setText(parametro_dose_aux.last());
            }
            else if(linhas_buscadas == 3){
                QStringList parametro_dose_aux = parametro_dose.split(' ');
                parametro_dose_aux.removeAll("");
                ui->field_dose_roi_x_min->setPlainText(parametro_dose_aux[0].trimmed());
                ui->field_dose_roi_x_max->setPlainText(parametro_dose_aux[1].trimmed());
            }
            else if(linhas_buscadas == 4){
                QStringList parametro_dose_aux = parametro_dose.split(' ');
                parametro_dose_aux.removeAll("");
                ui->field_dose_roi_y_min->setPlainText(parametro_dose_aux[0].trimmed());
                ui->field_dose_roi_y_max->setPlainText(parametro_dose_aux[1].trimmed());
            }
            else if(linhas_buscadas == 5){
                QStringList parametro_dose_aux = parametro_dose.split(' ');
                parametro_dose_aux.removeAll("");
                ui->field_dose_roi_z_min->setPlainText(parametro_dose_aux[0].trimmed());
                ui->field_dose_roi_z_max->setPlainText(parametro_dose_aux[1].trimmed());
            }

            linhas_buscadas++;

            if(linhas_buscadas == 6){
                linha_encontrada = false;
                preencher_dose = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou dose";
            continue;
        }

        //############### GEOMETRIA ##############
        if(linha.contains(secao_geometria, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 1 && preencher_geometria){
            parametro_geometria = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                ui->field_geometria->setText(parametro_geometria);
            }

            linhas_buscadas++;

            if(linhas_buscadas == 1){
                linha_encontrada = false;
                preencher_geometria = false;
                linhas_buscadas = 0;
            }
qDebug() << "passou geometria";
            continue;
        }

        //############### LISTA DE MATERIAIS ##############
        if(linha.contains(secao_materiais, Qt::CaseInsensitive)){
            linha_encontrada = true;
            continue;
        }
        else if(linha_encontrada == true && sem_materiais == false){
            QString material = linha.split('#')[0].trimmed();
            if(material != ""){
                ui->listWidget_material_lista->addItem(material);
                materiais_antigos_avancado.append(linha.split('#')[0].trimmed());
                materiais_novos_avancado.append(linha.split('#')[0].trimmed());
                continue;
            }
            else{
                break;
            }
           qDebug() << "passou materiais";
        }

    }while(!linha.isNull());

    foreach (QString mat, materiais_novos_avancado) {
        qDebug() << mat;
    }

    arquivo_entradas_base.close();
}

void Avancado::on_btn_salvar_avancado_clicked()
{
    QString local_arquivo_entradas_base = QDir::currentPath();
    QString nome_arquivo_entradas_base = "/SOPPE_base_inputs.in";

    QString secao_simulacao = "SECTION SIMULATION CONFIG v.2009-05-12";
    QString secao_fonte = "SECTION SOURCE v.2011-07-12";
    QString secao_detector = "SECTION IMAGE DETECTOR v.2009-12-02";
    QString secao_ct = "SECTION CT SCAN TRAJECTORY v.2011-10-25";
    QString secao_dose = "SECTION DOSE DEPOSITION v.2012-12-12";
    QString secao_geometria = "SECTION VOXELIZED GEOMETRY FILE v.2009-11-30";
    QString secao_materiais = "SECTION MATERIAL FILE LIST v.2009-11-30";

    QFile arquivo_entradas_base(local_arquivo_entradas_base + nome_arquivo_entradas_base);
    if(!arquivo_entradas_base.open(QFile::ReadWrite|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "O arquivo com as entradas iniciais não pode ser aberto!");
    }

    QTextStream entradas_base(&arquivo_entradas_base);

    QString linha;
    int linhas_buscadas = 0;
    bool linha_encontrada = false;
    QString parametro_simulacao = "";
    QString parametro_fonte = "";
    QString parametro_detector = "";
    QString parametro_ct = "";
    QString parametro_dose = "";
    QString parametro_geometria = "";
    //QStringList parametro_materiais;
    bool sem_materiais = false;
    bool preencher_simulacao = true;
    bool preencher_fonte = true;
    bool preencher_detector = true;
    bool preencher_ct = true;
    bool preencher_dose = true;
    bool preencher_geometria = true;
    QString texto_entrada_modificada = "";
    int index_material = 0;

    do{
        linha = entradas_base.readLine();

        //############### SIMULACAO ##############
        if(linha.contains(secao_simulacao, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 5 && preencher_simulacao){
            parametro_simulacao = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                texto_entrada_modificada += linha.replace(parametro_simulacao, ui->field_num_historia->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 1){
                texto_entrada_modificada += linha.replace(parametro_simulacao, ui->field_semente->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 2){
                texto_entrada_modificada += linha.replace(parametro_simulacao, ui->field_num_gpu_mpi->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 3){
                texto_entrada_modificada += linha.replace(parametro_simulacao, ui->field_num_thread_bloco->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 4){
                texto_entrada_modificada += linha.replace(parametro_simulacao, ui->field_num_historia_thread->toPlainText()) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 5){
                linha_encontrada = false;
                preencher_simulacao = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### FONTE ##############
        if(linha.contains(secao_fonte, Qt::CaseInsensitive)){
            linha_encontrada = true;
            qDebug() << linha_encontrada;
            qDebug() << linhas_buscadas;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 4 && preencher_fonte){
            parametro_fonte = linha.split('#')[0].trimmed();
            qDebug() << linhas_buscadas;
            if(linhas_buscadas == 0){
                texto_entrada_modificada += linha.replace(parametro_fonte, ui->field_fonte_energia->text()) + '\n';
            }
            else if(linhas_buscadas == 1){
                QStringList parametro_fonte_aux;
                parametro_fonte_aux << ui->field_posicao_fonte_x->toPlainText() << ui->field_posicao_fonte_y->toPlainText() << ui->field_posicao_fonte_z->toPlainText();
                parametro_fonte_aux.removeAll("");
                QString param = parametro_fonte_aux[0].trimmed() + "   " + parametro_fonte_aux[1].trimmed() + "   " + parametro_fonte_aux[2].trimmed();
                texto_entrada_modificada += linha.replace(parametro_fonte, param) + '\n';
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_fonte_aux;
                parametro_fonte_aux << ui->field_coseno_fonte_u->toPlainText() << ui->field_coseno_fonte_v->toPlainText() << ui->field_coseno_fonte_w->toPlainText();
                parametro_fonte_aux.removeAll("");
                QString param = parametro_fonte_aux[0].trimmed() + "   " + parametro_fonte_aux[1].trimmed() + "   " + parametro_fonte_aux[2].trimmed();
                texto_entrada_modificada += linha.replace(parametro_fonte, param) + '\n';
            }
            else if(linhas_buscadas == 3){
                QStringList parametro_fonte_aux;
                parametro_fonte_aux << ui->field_abertura_polar->toPlainText() << ui->field_abertura_azimutal->toPlainText();
                parametro_fonte_aux.removeAll("");
                QString param = parametro_fonte_aux[0].trimmed() + "  " + parametro_fonte_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_fonte, param) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 4){
                linha_encontrada = false;
                preencher_fonte = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### DETECTOR DE IMAGEM ##############
        if(linha.contains(secao_detector, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 4 && preencher_detector){
            parametro_detector = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                texto_entrada_modificada += linha.replace(parametro_detector, ui->lineEdit_nome_arquivo_saida_imagem->text()) + '\n';
            }
            else if(linhas_buscadas == 1){
                QStringList parametro_detector_aux;
                parametro_detector_aux << ui->field_num_pixel_imagem_x->toPlainText() << ui->field_num_pixel_imagem_z->toPlainText();
                parametro_detector_aux.removeAll("");
                QString param = parametro_detector_aux[0].trimmed() + "  " + parametro_detector_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_detector, param) + '\n';
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_detector_aux;
                parametro_detector_aux << ui->field_num_dimensao_imagem_x->toPlainText() << ui->field_num_dimensao_imagem_z->toPlainText();
                parametro_detector_aux.removeAll("");
                QString param = parametro_detector_aux[0].trimmed() + "  " + parametro_detector_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_detector, param) + '\n';
            }
            else if(linhas_buscadas == 3){
                texto_entrada_modificada += linha.replace(parametro_detector, ui->field_distancia_fonte_detector->toPlainText()) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 4){
                linha_encontrada = false;
                preencher_detector = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### CT ##############
        if(linha.contains(secao_ct, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 5 && preencher_ct){
            parametro_ct = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                texto_entrada_modificada += linha.replace(parametro_ct, ui->field_num_projecao->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 1){
                texto_entrada_modificada += linha.replace(parametro_ct, ui->field_angulo_projecao->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 2){
                QStringList parametro_ct_aux;
                parametro_ct_aux << ui->field_angulo_interesse_inicial->toPlainText() << ui->field_angulo_interesse_final->toPlainText();
                parametro_ct_aux.removeAll("");
                QString param = parametro_ct_aux[0].trimmed() + "  " + parametro_ct_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_ct, param) + '\n';
            }
            else if(linhas_buscadas == 3){
                texto_entrada_modificada += linha.replace(parametro_ct, ui->field_distancia_fonte_rotacao->toPlainText()) + '\n';
            }
            else if(linhas_buscadas == 4){
                texto_entrada_modificada += linha.replace(parametro_ct, ui->field_translacao_projecao->toPlainText()) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 5){
                linha_encontrada = false;
                preencher_ct = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### DOSE DEPOSITADA ##############
        if(linha.contains(secao_dose, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 6 && preencher_dose){
            parametro_dose = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                if(ui->radioButton_contagem_dose_material_sim->isChecked()){
                    texto_entrada_modificada += linha.replace(parametro_dose, "YES") + '\n';
                }
                else if(ui->radioButton_contagem_dose_material_nao->isChecked()){
                    texto_entrada_modificada += linha.replace(parametro_dose, "NO") + '\n';
                }
            }
            else if(linhas_buscadas == 1){
                if(ui->radioButton_contagem_dose_voxel_sim->isChecked()){
                    texto_entrada_modificada += linha.replace(parametro_dose, "YES") + '\n';
                }
                else if(ui->radioButton_contagem_dose_voxel_nao->isChecked()){
                    texto_entrada_modificada += linha.replace(parametro_dose, "NO") + '\n';
                }
            }
            else if(linhas_buscadas == 2){
                texto_entrada_modificada += linha.replace(parametro_dose, ui->lineEdit_nome_arquivo_saida_dose->text()) + '\n';
            }
            else if(linhas_buscadas == 3){
                QStringList parametro_dose_aux;
                parametro_dose_aux << ui->field_dose_roi_x_min->toPlainText() << ui->field_dose_roi_x_max->toPlainText();
                parametro_dose_aux.removeAll("");
                QString param = parametro_dose_aux[0].trimmed() + "  " + parametro_dose_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_ct, param) + '\n';
            }
            else if(linhas_buscadas == 4){
                QStringList parametro_dose_aux;
                parametro_dose_aux << ui->field_dose_roi_y_min->toPlainText() << ui->field_dose_roi_y_max->toPlainText();
                parametro_dose_aux.removeAll("");
                QString param = parametro_dose_aux[0].trimmed() + "  " + parametro_dose_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_ct, param) + '\n';
            }
            else if(linhas_buscadas == 5){
                QStringList parametro_dose_aux;
                parametro_dose_aux << ui->field_dose_roi_z_min->toPlainText() << ui->field_dose_roi_z_max->toPlainText();
                parametro_dose_aux.removeAll("");
                QString param = parametro_dose_aux[0].trimmed() + "  " + parametro_dose_aux[1].trimmed();
                texto_entrada_modificada += linha.replace(parametro_ct, param) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 6){
                linha_encontrada = false;
                preencher_dose = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### GEOMETRIA ##############
        if(linha.contains(secao_geometria, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';
            continue;
        }
        else if(linha_encontrada == true && linhas_buscadas < 1 && preencher_geometria){
            parametro_geometria = linha.split('#')[0].trimmed();

            if(linhas_buscadas == 0){
                texto_entrada_modificada += linha.replace(parametro_geometria, ui->field_geometria->text()) + '\n';
            }

            linhas_buscadas++;

            if(linhas_buscadas == 1){
                linha_encontrada = false;
                preencher_geometria = false;
                linhas_buscadas = 0;
            }

            continue;
        }

        //############### LISTA DE MATERIAIS ##############
        if(linha.contains(secao_materiais, Qt::CaseInsensitive)){
            linha_encontrada = true;
            texto_entrada_modificada += linha + '\n';

            materiais_novos_avancado.clear();

            for (int x = 0; x < ui->listWidget_material_lista->count(); x++)
            {
                materiais_novos_avancado.append(ui->listWidget_material_lista->item(x)->text());
            }

            continue;
        }
        else if(linha_encontrada == true && sem_materiais == false){
            QString material = linha.split('#')[0].trimmed();

            if(index_material < materiais_novos_avancado.count() && material != ""){
                texto_entrada_modificada += linha.replace(material, materiais_novos_avancado[index_material]) + '\n';
                index_material++;
                continue;
            }
            else if(index_material < materiais_novos_avancado.count() && material == ""){
                texto_entrada_modificada += materiais_novos_avancado[index_material] + "                #  " + linha.split('#')[1].trimmed() + '\n';
                index_material++;
                continue;
            }
            else if(index_material >= materiais_novos_avancado.count() && material != ""){
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
    materiais_novos_avancado.clear();

    arquivo_entradas_base.resize(0);
    entradas_base << texto_entrada_modificada;
    arquivo_entradas_base.flush();
    arquivo_entradas_base.close();

    this->close();
    MainSoppe *mainSoppe = new MainSoppe();
    mainSoppe->show();
}

QString Avancado::copiar_arquivo_para_pasta_base()
{
    QString filtro = "Todos os Arquivos (*.*) ;; Arquivo de texto (*.txt)";
    QString local_arquivo_entradas_base = QDir::currentPath();
    QString abrir_arquivo = QFileDialog::getOpenFileName(this, "Abrir", "/home/vagner/Documentos", filtro);
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

void Avancado::on_pushButton_material_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    ui->listWidget_material_lista->addItem(arquivo_copiado);
    materiais_novos_avancado.append(arquivo_copiado);
}


void Avancado::on_pushButton_fonte_energia_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    ui->field_fonte_energia->setText(arquivo_copiado);
}


void Avancado::on_pushButton_geometria_clicked()
{
    QString arquivo_copiado = copiar_arquivo_para_pasta_base();
    ui->field_geometria->setText(arquivo_copiado);
}


void Avancado::on_pushButton_material_remover_clicked()
{
    const QString mensagem = "O material selecionado será removido da listagem. Deseja continuar?";
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Cuidado", mensagem, QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes){
        QListWidgetItem *material_selecionado = ui->listWidget_material_lista->currentItem();
        materiais_novos_avancado.removeOne(material_selecionado->text());

        delete material_selecionado;

        ui->listWidget_material_lista->setCurrentRow(-1);
    }
}

