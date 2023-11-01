# 1. Introdução

O SOPPE (Software de Paralelização do Penelope) é um código de simulação que utilizado o Método de Monte Carlo para gerar imagens sintéticas radiográficas e tomografias computadorizadas utilizando o poder computacional de placas de unidade de processamento gráfico (GPU). Para isso, ele utiliza modelos realistas da anatomia humana e realiza simulações com a implementação da simulação de Monte Carlo de forma paralela para realizar o transporte de raios-X em uma geometria voxelizada. 

O SOPPE utiliza como base o MC-GPU, um software de código livre, com última release em 2012, que realiza o transporte de raios-X de forma paralela utilizado o poder computacional presente nas GPUs NVIDIA usando o modelo de programação CUDA, no qual seus modelos de interação e propriedades dos materiais foram adaptados do PENELOPE 2006, sendo este também um software de código livre. 

Para utilização do software é necessário estar utilizando um sistema Linux além da instalação e configuração de algumas ferramentas como as bibliotecas CUDA, o compilador GNU GCC e a biblioteca openMPI.

# 2. Instalação

## 2.1 CUDA Toolkit

Caso seja solicitado durante a instalação, digite a senha que utiliza para acessar o sistema operacional para continuar.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Acesse o site https://developer.nvidia.com/cuda-downloads;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Escolha as opções para o sistema Linux que estiver utilizando (no exemplo utilizamos o Ubuntu) com a última opção sendo runfile (local);

![Imagem1](https://github.com/VagnerSJ/SOPPE/assets/33886298/e3e988cf-a107-4f51-bd44-5bea479645a4)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Após escolher a última opção, será apresentado os comandos para continuar a instalação;

![Imagem3](https://github.com/VagnerSJ/SOPPE/assets/33886298/224b70ca-dfde-4c6a-b752-00d6aa52b492)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; d.	Abra o terminal;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; e.	Digite sudo apt update;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; f.	Digite sudo apt upgrade-y;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; g.	Digite apt search nvidia-driver;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; h.	Digite sudo apt install nvidia-driver-numero da versao, substituindo o número da versão pelo número do último driver sem o sufixo -server que apareceu no item anterior (no exemplo driver 530);

![Imagem4](https://github.com/VagnerSJ/SOPPE/assets/33886298/68867ffb-7b2f-4fb9-82aa-b467a9951f0a)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; i.	Após a instalação, repita os passo e e f e reinicie a máquina;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; j.	No terminal, execute a primeira instrução que apareceu na tela do passo c (no exemplo a versão 12.1.1);

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; k.	Após o término do download, execute a segunda instrução;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; l.	Aparecerá os termos de uso. Aceitos digitando accept e apertando Enter;

![Imagem5](https://github.com/VagnerSJ/SOPPE/assets/33886298/d47f6787-2375-4b3d-a3ba-da5f74870a0e)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; m.	Nesse tela, não instalaremos o driver novamente. Para desmarcar a opção de driver, mantenha na seleção em driver e aperte a tecla de Espaço, sumindo assim o X da marcação. Em seguida, desça até a opção Install e aperte Enter;

![Imagem6](https://github.com/VagnerSJ/SOPPE/assets/33886298/c701598a-b90e-4068-a723-a388cd5aadfc)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; n.	Após a instalação, digite o comando sudo nano .bashrc;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; o.	Dentro do arquivo que foi aberto no terminal, digite as seguintes linhas (substituindo  o número da versão com segundo número pelo que foi baixado, no exemplo versão 12.1):

```bash

export PATH=$PATH:/usr/local/cuda-numero da versao com segundo numero/bin
export LD_LIBRARY_PATH=/usr/local/cuda-numero da versao com segundo numero/lib64

```

![Imagem7](https://github.com/VagnerSJ/SOPPE/assets/33886298/5ffe0bb6-dae4-4d0a-9718-18ea7fc1eb3d)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; p.	Aperte Ctrl+O para salvar o arquivo. Após salvar, aperte Ctrl+X para fechar o arquivo;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; q.	Digite source .bashrc e aperte Enter;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; r.	Digite nvcc --version para verificar se foi instalado com sucesso.

![Imagem8](https://github.com/VagnerSJ/SOPPE/assets/33886298/f328f476-e957-43c8-ab6b-62a8d5ca036d)

## 2.2 GNU GCC

Caso seja solicitado durante a instalação, digite a senha que utiliza para acessar o sistema operacional para continuar.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Abra o terminal;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Digite sudo apt-get update;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Digite sudo apt-get install gcc;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; d.	Após a conclusão, digite gcc --version para verificar se foi instalado com sucesso.

![Imagem9](https://github.com/VagnerSJ/SOPPE/assets/33886298/acf6860d-5430-4639-89d4-4433c9ee5355)

## 2.3 MPI

Caso seja solicitado durante a instalação, digite a senha que utiliza para acessar o sistema operacional para continuar.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Abra o terminal;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Digite sudo apt install mpich;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Após a conclusão, digite mpicc --version para verificar se foi instalado com sucesso.

![Imagem10](https://github.com/VagnerSJ/SOPPE/assets/33886298/d30653b2-23c5-4b92-8dcd-a1a3be8361d4)

## 2.4 Arquivos da aplicação

Após instalar os pré-requisitos, podemos baixar os arquivos da aplicação. Eles podem ser encontrados no repositório no GitHub da aplicação.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Acesse a página https://github.com/VagnerSJ/SOPPE;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Clique no botão Code e em seguida baixe o arquivo ZIP;

![Imagem11](https://github.com/VagnerSJ/SOPPE/assets/33886298/7e6cf5fa-00fb-4b93-b669-42b1d28808a1)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Descompacte o arquivo ZIP baixado. Nele estão todos os arquivos necessários para o funcionamento do SOPPE, incluindo alguns exemplos de demonstração.

# 3. Configurações

## 3.1 Compilação da versão GPU

<b>Obs.: Caso ocorra algum erro de reconhecimento da NVidia CUDA, utilize o comando sudo source .bashrc para carregar as pastas da biblioteca nas variáveis de ambiente.</b>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Acesse a página https://developer.nvidia.com/cuda-gpus;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Clique na seção que corresponde a GPU que será utilizada (no exemplo do passo ‘c’ GTX/GeForce);

![Imagem12](https://github.com/VagnerSJ/SOPPE/assets/33886298/e138c50c-a16c-4831-96cb-e6c12f1b05ef)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Na seção expandida, encontre o poder computacional da GPU que será utilizada (no exemplo GTX 1060);

![Imagem13](https://github.com/VagnerSJ/SOPPE/assets/33886298/e302bfce-82ab-45a3-b811-70fb66d8f0c6)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; d.	Na pasta do código fonte do SOPPE, clique com o botão direito e abra o terminal;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; e.	Execute o comando sudo source .bashrc;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; f.	Execute o comando abaixo para compilar o programa, substituindo nos locais indicados pelos poder computacional adquirido no passo ‘c’, sem os pontos separadores (exemplo 6.1 -> 61);

```bash

nvcc -DUSING_CUDA -DUSING_MPI SOPPE.cu -o SOPPE.x -O3 -use_fast_math -L/usr/lib/ -I. -I/usr/local/cuda/include  -I/usr/local/cuda/samples/common/inc -I/usr/local/cuda/samples/shared/inc/  -I/usr/lib/x86_64-linux-gnu/openmpi/include -lmpi -lz --ptxas-options=-v  -gencode=arch=compute_61,code=sm_61 -gencode=arch=compute_61,code=sm_61

```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; g.	Será gerado o arquivo SOPPE.x que será utilizado para realizar as simulações utilizando a GPU.

## 3.2 Compilação da versão CPU

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Na pasta do código fonte do SOPPE, clique com o botão direito e abra o terminal;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Execute o comando abaixo para compilar o programa;

```bash

gcc -x c -O3 SOPPE.cu -o SOPPE_CPU.x -I./ -lm -lz

```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Será gerado o arquivo SOPPE_CPU.x que será utilizado para realizar as simulações utilizando a CPU.

# 4. Instruções de uso

No arquivo de entrada, existem diversos parâmetros e configurações para manipular uma simulação. No passo a passo vamos nos ater aos parâmetros necessários para executar uma simulação.

<b>Obs.: caso tenha realizado alguma modificação no código fonte, copie o novo executável gerado para a pasta de execução do SOPPE.</b>

![Imagem14](https://github.com/VagnerSJ/SOPPE/assets/33886298/9d5c193e-661d-4968-9d05-af002df8bdd4)

## 4.1 Configuração das entradas

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Na primeira linha da seção [SECTION SIMULATION CONFIG] podemos determinar o número de histórias que serão realizadas na simulação. Caso o número seja abaixo de 100.000, ele será considerado como tempo total de simulação;

![Imagem15](https://github.com/VagnerSJ/SOPPE/assets/33886298/ea045d03-0e8d-416c-bd10-baafe512eb87)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Na primeira linha da seção [SECTION SOURCE] podemos determinar o arquivo de fonte de energia da simulação;

![Imagem16](https://github.com/VagnerSJ/SOPPE/assets/33886298/e8ba0743-c233-41b9-b224-862e640e7b1d)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	Nas seções [SECTION VOXELIZED GEOMETRY FILE] e [SECTION MATERIAL FILE LIST] determinamos o arquivo de geometria e os arquivos de materiais que serão utilizados nas simulações. A aplicação também aceita esses arquivos no formato do PENELOPE. Em relação aos materiais, o número máximo que se pode colocar são 15;

![Imagem17](https://github.com/VagnerSJ/SOPPE/assets/33886298/45cccfe4-9d17-4518-870f-4896b12764d8)

## 4.2 Executando uma simulação

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; a.	Na pasta do código fonte do SOPPE, clique com o botão direito e abra o terminal;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; b.	Execute o comando abaixo para iniciar uma simulação, onde:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; i.	SOPPE.x é o arquivo compilado, podendo ser tanto o para CPU (3.2) quanto GPU (3.1);

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ii.	SOPPE.in é o arquivo de entrada com as configurações importantes para simulação (4.1);

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; iii.	SOPPE.out é o arquivo de saída com os resultados.

```bash

./SOPPE.x SOPPE.in | tee SOPPE.out

```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; c.	A simulação será iniciada, com seu tempo variando de acordo com as configurações que foram fornecidas;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; d.	Ao término da simulação, serão gerados o arquivo de saída (<i>.out</i>) e os arquivos <i>.dat</i> e <i>.raw</i> contendo as imagens geradas e suas doses;

![Imagem18](https://github.com/VagnerSJ/SOPPE/assets/33886298/f652bd01-612d-4984-807f-b329e4e7627a)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; e.	No arquivo de saída, são descritas várias informações sobre a simulação. No final do arquivo é informado o tempo total que levou a simulação;

![Imagem19](https://github.com/VagnerSJ/SOPPE/assets/33886298/851c73a2-7598-4681-ae61-ef313b79aba1)











