/*
Este é o arquivo "Process.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Process", que
implementa as principais funções que são utilizadas pelo programa principal no
"main.c" e as que são utilizadas na própria biblioteca para complementá-las

Funções:
void limparEntrada()

int geraCodigo(int min, int max)

int localizaCliente(FILE *f, int codigo)
int localizaFuncionario(FILE *f, int codigo)
int localizaQuarto(FILE *f, int numero)
int localizaQuartoPorInfo(FILE *f_qua, int quantHosp)
float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli)

int calculaDiarias(int dataIn, int dataOut)
void desmontaData(int data, int *ano, int *mes, int *dia)
float diariaQuartoPorNum(FILE *f, int numero)
int calculaPtsEstadia(FILE *f_est, int codCli)

void imprimeCliente(FILE *f, int codigo)
void imprimeFuncionario(FILE *f, int codigo)
int imprimeEstadia(FILE *f_est, FILE *f_qua, int codigo)

Autor: João Alvaro Rodrigues Araujo
Data de início: 14 Jun. 2024
*/

#include "Datas.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tcliente {
  /*
  Esta é uma estrutura para os dados do Cliente.

  Descrição: a estrutura declara variáveis com os dados do código, nome,
  endereço e telefone do usuário, que serão preenchidos no procedimento de
  cadastro de cliente.

  Atributos:
  int codigo
  char nome[100]
  char ender[200]
  int telefone
  */

  int codigo;
  char nome[100];
  char ender[200];
  int telefone;
};
typedef struct Tcliente cliente;

struct Tfuncionario {
  /*
  Esta é uma estrutura para os dados do funcionário.

  Descrição: a estrutura declara variáveis com os dados do código, nome,
  telefone, cargo e salário do funcionário, que serão preenchidos no
  procedimento de cadastro de funcionário

  Atributos:
  int codigo
  char nome[100]
  int telefone
  char cargo[80]
  float salario
  */

  int codigo;
  char nome[100];
  int telefone;
  char cargo[80];
  float salario;
};
typedef struct Tfuncionario funcionario;

struct Tquarto {
  /*
  Esta é uma estrutura para os dados do quarto.

  Descrição: a estrutura declara variáveis com os dados do número do quarto a
  ser cadastrado, a quantidade de hóspedes, o valor da diária e o status do
  quarto (ocupado e desocupado)

  Atributos:
  int numero
  int quantHosp
  float diaria
  char status[10]
  */

  int numero;
  int quantHosp;
  float diaria;
  char status[10];
};
typedef struct Tquarto quarto;

struct Testadia {
  /*
  Esta é uma estrutura para os dados da estadia.

  Descrição: a estrutura declara variáveis com os dados do código do cliente no
  qual a estadia vai ser ser cadastrada, a quantidade de hóspedes desejada, as
  datas de entrada e saída da estadia e o número do quarto reservado.

  Atributos:
  int codCli
  int quantHosp
  int dataEntrada
  int dataSaida
  int quarto
  */
  int codCli;
  int quantHosp;
  int dataEntrada;
  int dataSaida;
  int quarto;
};
typedef struct Testadia estadia;

void limparEntrada();

int geraCodigo(int min, int max);

int localizaCliente(FILE *f, int codigo);
int localizaFuncionario(FILE *f, int codigo);
int localizaQuarto(FILE *f, int numero);
int localizaQuartoPorInfo(FILE *f_qua, int quantHosp);
float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli);

int calculaDiarias(int dataIn, int dataOut);
void desmontaData(int data, int *ano, int *mes, int *dia);
int calculaPtsEstadia(FILE *f_est, int codCli);

void imprimeCliente(FILE *f, int codigo);
void imprimeFuncionario(FILE *f, int codigo);
int imprimeEstadia(FILE *f_est, int codigo);

void limparEntrada() {
  /*
  Este é o procedimento limparEntrada().

  Descrição: O procedimento lê um caractere da entrada e a percorre até econtrar
  uma nova linha ou fim de arquivo, com o objetivo de descartar os caracteres da
  entrada para limpar o buffer

  Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
  código não vai retornar um valor.
  */

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void lerClientes(FILE *f) {
  /*
  Este é o procedimento lerClientes

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de clientes e exibir todas as estruturas registradas no
  arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadCliente, que
  por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  cliente cli;
  fseek(f, 0, SEEK_SET);
  while (fread(&cli, sizeof(cli), 1, f) == 1) {
    printf("Código: %d\n", cli.codigo);
    printf("Nome: %s\n", cli.nome);
    printf("Endereço: %s\n", cli.ender);
    printf("Telefone: %d\n\n", cli.telefone);
  }
}

void cadCliente(FILE *f) {
  /*
    Este é o procedimento cadCliente().

    Descrição: O procedimento é reponsável por ler informações do cliente e
    guardá-las na estrutura Tcliente, tal como gerar automaticamente um código
    para o cliente e evitar a repetição de códigos para clientes diferentes.

    Parâmetros:
    FILE *f: Ponteiro para o arquivo passado pelo main() no arquivo main.c ao
    selecionar a respectiva opção no menu, é o arquivo em que a função escreve,
    verifica a existência do código informado e exibe os dados através dos
    procedimentos localizaCliente e lerClientes.
  */

  cliente cli;
  int posicao;

  cli.codigo = geraCodigo(10000, 99999);
  fflush(stdin);
  posicao = localizaCliente(f, cli.codigo);

  while (posicao != -1) {
    cli.codigo = geraCodigo(10000, 99999);
    posicao = localizaCliente(f, cli.codigo);
  }

  limparEntrada();
  printf(">> CADASTRAR UM CLIENTE \n\n");

  printf("Digite o nome do cliente: ");
  fgets(cli.nome, sizeof(cli.nome), stdin);
  cli.nome[strcspn(cli.nome, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");
  fgets(cli.ender, sizeof(cli.ender), stdin);
  cli.ender[strcspn(cli.ender, "\n")] = '\0';

  printf("Digite o telefone do cliente: ");
  scanf("%i", &cli.telefone);
  limparEntrada();

  fseek(f, 0, SEEK_END);
  fwrite(&cli, sizeof(cli), 1, f);
  fflush(f);

  printf("\n");

  lerClientes(f);
}

void lerFuncionarios(FILE *f) {
  /*
  Este é o procedimento lerFuncionarios

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de funcionários e exibir todas as estruturas
  registradas no arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadFuncionario,
  que por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  funcionario fun;
  fseek(f, 0, SEEK_SET);
  while (fread(&fun, sizeof(fun), 1, f) == 1) {
    printf("Código: %d\n", fun.codigo);
    printf("Nome: %s\n", fun.nome);
    printf("Cargo: %s\n", fun.cargo);
    printf("Telefone: %i\n", fun.telefone);
    printf("Salário: R$ %.2f\n\n", fun.salario);
  }
}

void cadFuncionario(FILE *f) {
  /*
    Este é o procedimento cadFuncionario.

    Descrição: O procedimento é reponsável por ler informações do funcionário e
    guardá-las na estrutura Tfuncionario, tal como gerar automaticamente um
    código para o funcionário e evitar a repetição de códigos para funcionários
    diferentes.

    Parâmetros:
    FILE *f: Um ponteiro para o arquivo passado pelo programa principal no
    arquivo main.c, onde serão registrados todos os dados dos fucionários
    cadastrados para então serem exibidos através do procedimento
    lerFuncionarios
  */

  funcionario fun;
  int posicao;

  fun.codigo = geraCodigo(10000, 99999);
  fflush(stdin);
  posicao = localizaFuncionario(f, fun.codigo);

  while (posicao != -1) {
    fun.codigo = geraCodigo(10000, 99999);
    posicao = localizaFuncionario(f, fun.codigo);
  }

  limparEntrada();
  printf(">> CADASTRAR UM FUNCIONÁRIO \n\n");

  printf("Digite o nome do funcionário: ");
  fgets(fun.nome, sizeof(fun.nome), stdin);
  fun.nome[strcspn(fun.nome, "\n")] = '\0';

  printf("Digite o cargo do funcionário: ");
  fgets(fun.cargo, sizeof(fun.cargo), stdin);
  fun.cargo[strcspn(fun.cargo, "\n")] = '\0';

  printf("Digite o telefone do funcionário: ");
  scanf("%i", &fun.telefone);
  limparEntrada();

  printf("Digite o salário do funcionário: ");
  scanf("%f", &fun.salario);

  fseek(f, 0, SEEK_END);
  fwrite(&fun, sizeof(fun), 1, f);
  fflush(f);

  printf("\n");

  lerFuncionarios(f);
}

void lerQuartos(FILE *f) {
  /*
  Este é o procedimento lerQuartos

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de quartos e exibir todas as estruturas registradas no
  arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadQuarto, que
  por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  quarto qua;
  fseek(f, 0, SEEK_SET);
  while (fread(&qua, sizeof(qua), 1, f) == 1) {
    printf("Número: %i\n", qua.numero);
    printf("Quantidade de hóspedes: %i\n", qua.quantHosp);
    printf("Valor da diária: R$ %.2f\n", qua.diaria);
    printf("O quarto está %s.\n\n", qua.status);
  }
}

void cadQuarto(FILE *f) {
  /*
    Este é o procedimento cadQuarto().

    Descrição: O procedimento é reponsável por ler informações do quarto e
    guardá-las na estrutura Tquarto, tal como processar o número inserido pelo
    usuário e atribuir o status ao quarto e garantir que quartos diferentes não
    tenham o mesmo número.

    Parâmetros:
    FILE *f: Um ponteiro para o arquivo passado em main.c onde os quartos serão
    registrados a cada novo cadastro, e depois serão utilizados para
    verificações e exibições no procedimento.
  */

  quarto qua;
  int ocupado;

  limparEntrada();
  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");
  scanf("%i", &qua.numero);
  int posicao = localizaQuarto(f, qua.numero);

  while (qua.numero <= 0) {
    printf("\nErro! Número de quarto inválido!\n");
    printf("Digite outro número: ");
    scanf("%i", &qua.numero);
  }

  while (posicao != -1) {
    printf("\nErro! Já há um quarto com esse número!\n");
    printf("Digite outro número: ");
    scanf("%i", &qua.numero);
    posicao = localizaQuarto(f, qua.numero);
  }

  printf("Digite a quantidade de hóspedes: ");
  scanf("%i", &qua.quantHosp);

  printf("Digite o valor da diária: ");
  scanf("%f", &qua.diaria);

  printf("Digite o status do quarto (0 desocupado, 1 ocupado): ");
  scanf("%i", &ocupado);

  while (ocupado != 0 && ocupado != 1) {
    printf("\nErro! Status de quarto inválido! \n");
    printf("Digite novamente: ");
    scanf("%i", &ocupado);
  }

  if (ocupado == 1) {
    strcpy(qua.status, "ocupado");
  } else {
    strcpy(qua.status, "desocupado");
  }

  limparEntrada();

  fseek(f, 0, SEEK_END);
  fwrite(&qua, sizeof(qua), 1, f);
  fflush(f);
  printf("\n");

  lerQuartos(f);
}

void lerEstadias(FILE *f) {
  /*
  Este é o procedimento lerEstadias

  O procedimento é responsável por exibir no console os dados da estrutura
  Testadia no arquivo de estadias percorrendo o arquivo e imprimindo todos os
  dados de cada um dos registros feitos.

  Parâmetros:
  FILE *f: É um ponteiro para um arquivo passado pelo procedimento cadEstadia,
  que por sua vez é passado pelo programa principal, é o arquivo em que todas as
  operações com estadias serão realizadas.
  */
  estadia est;
  fseek(f, 0, SEEK_SET);
  while (fread(&est, sizeof(est), 1, f) == 1) {
    printf("Código do cliente: %i\n", est.codCli);
    printf("Quantidade de hóspedes: %i\n", est.quantHosp);
    printf("Data de entrada: %i \n", est.dataEntrada);
    printf("Data de saída: %i \n", est.dataSaida);
    printf("Quarto reservado: %i \n\n", est.quarto);
  }
}

void cadEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  /*
    Este é o procedimento cadEstadia().

    Descrição: O procedimento é responsável por guardar os dados fornecidos na
    estrutura Testadia e escrevê-los no arquivo de estadias, tal como exibí-los
    no console através do procedimento lerEstadias. O procedimento verifica se o
    cliente informado está cadastrado e se há um quarto disponível para a
    quantidade informada de hóspedes ou superior, caso não haja um

    Parâmetros:
    FILE *f_est: É o ponteiro para o arquivo de estadias, que é usado para
    guardar os registros feitos pelo usuário e exibí-los pelo procedimento
    lerEstadias

    FILE *f_cli: Este agora é um ponteiro para o arquivo de clientes, que é
    usado para verificar se o cliente informado pelo usuário existe através da
    função localizaCliente

    FILE *f_qua: E este é o ponteiro para o arquivo de quartos, onde estão
    guardados todos os registros de quartos já feitos pelo usuário, que serão
    verificados pela função localizaQuarto para encontrar um que possua a
    capacidade adequada
  */

  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer cadastrar sua estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);

  while (checkCli == -1) {
    printf("O cliente não está cadastrado! \n");
    printf("Digite outro código: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
  }

  printf("\n> Cadastrando estadia do cliente. \n\n");

  printf("Digite a quantidade de hóspedes que querem se hospedar: ");
  scanf("%i", &est.quantHosp);

  printf("Digite a data de check-in no hotel ('ANOMESDIA' - sem espaços, "
         "hífens ou barras): ");
  scanf("%i", &est.dataEntrada);
  printf("Digite a data de check-out no hotel ('ANOMESDIA' - sem espaços, "
         "hífens ou barras): ");
  scanf("%i", &est.dataSaida);

  int checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);

  while (est.quantHosp <= 0) {
    printf("\nQuantidade de hóspedes inválida! \n");
    printf("Digite outra quantidade de hóspedes: ");
    scanf("%i", &est.quantHosp);
  }

  while (checkQua == -1) {
    printf("Não há quartos disponíveis para %i hóspedes por enquanto. ",
           est.quantHosp);
    printf("Digite outra quantidade de hóspedes: ");
    scanf("%i", &est.quantHosp);
    checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);
  }

  est.quarto = localizaQuartoPorInfo(f_qua, est.quantHosp);

  printf("\nO número de diárias a serem pagas é %i\n",
         calculaDiarias(est.dataEntrada, est.dataSaida));

  fseek(f_est, 0, SEEK_END);
  fwrite(&est, sizeof(est), 1, f_est);
  fflush(f_est);

  printf("\n");

  lerEstadias(f_est);
}

void baixaEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  /*
  Este é o procedimento baixaEstadia

  Descrição: O procedimento é responsável por ler o código de cliente informado e dar baixa na primeira estadia
  em aberto encontrada com este código, e exibir o valor final a ser pago no console.

  Parâmetros:
  FILE *f_est: É o ponteiro para o arquivo de estadias, que é usado para encontrar a estadia registrada com o código
  informado.

  FILE *f_cli: Este agora é um ponteiro para o arquivo de clientes, que é
  usado para verificar se o cliente informado pelo usuário existe através da
  função localizaCliente

  FILE *f_qua: E este é o ponteiro para o arquivo de quartos, onde estão
  guardados todos os registros de quartos já feitos pelo usuário, que serão
  percorridos pela função calculaValorEstadia para encontrar o valor da diária do quarto e usá-lo para calcular o
  preço final da estadia
  */
  estadia est;
  cliente cli;
  quarto qua;

  limparEntrada();
  printf(">> DAR BAIXA EM UMA ESTADIA\n\n");

  printf("Digite o código do cliente que cadastrou a estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);
  int checkEst = calculaValorEstadia(f_est, f_qua, est.codCli);

  while (checkCli == -1 || checkEst == -1) {
    printf("\nO cliente ou a estadia não estão cadastrados! \n");
    printf("\nDigite o código de um cliente cadastrado que possui uma estadia "
           "cadastrada: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
    checkEst = calculaValorEstadia(f_est, f_qua, est.codCli);
  }

  printf("\n> Dando baixa na estadia do cliente. \n\n");

  float valor = calculaValorEstadia(f_est, f_qua, est.codCli);
  printf("\nO valor total a ser pago é R$ %.2f", valor);
}

void pesquisa(FILE *f_cli, FILE *f_fun) {
  /*
  Este é o procedimento pesquisa

  O procedimento serve para ler o código de um cliente ou funcionário e exibir seus dados no console, lendo os arquivos
  de clientes e funcionários até encontrar um código correspondente. Caso não exista nem um cliente nem um funcionário
  com o código informado, o procedimento pede um novo código ao usuário até que a condição seja verdadeira para um deles

  Parâmetros:
  FILE *f_cli: O ponteiro para o arquivo de clientes, percorrido pela função localizaCliente para encontrar o cliente
  correspondente ao código caso exista

  FILE *f_fun: O ponteiro para o arquivo de funcionários, percorrido pela função localizaFuncionario para encontrar
  o funcionário correspondente ao código caso exista
  */
  cliente cli;
  funcionario fun;
  int codSearch;

  limparEntrada();
  printf(">> PESQUISAR CLIENTES E FUNCIONÁRIOS \n\n");

  printf("Digite o código do cliente ou funcionário que deseja pesquisar: ");
  scanf("%i", &codSearch);

  int checkCli = localizaCliente(f_cli, codSearch);
  int checkFun = localizaFuncionario(f_fun, codSearch);

  while (checkCli == -1 && checkFun == -1) {
    printf("\nNão há um funcionário ou cliente correspondente. ");
    printf("\nDigite outro código: ");
    scanf("%i", &codSearch);
    checkCli = localizaCliente(f_cli, codSearch);
    checkFun = localizaFuncionario(f_fun, codSearch);
  }

  imprimeCliente(f_cli, codSearch);
  imprimeFuncionario(f_fun, codSearch);
}

void buscaEstadia(FILE *f_est, FILE *f_qua, FILE *f_cli) {
  /*
  Este é o procedimento buscaEstadia

  O procedimento tem como objetivo ler e exibir todas as estadias cadastradas em um determinado código de usuário
  no console.

  Parâmetros:
  FILE *f_est: Ponteiro para o arquivo de estadias, usado para verificar as estadias correspondentes ao código e exibir
  na tela através do procedimento imprimeEstadia

  FILE *f_qua: Ponteiro para o arquivo de quartos, passado para o procedimento imprimeEstadia para imprimir os dados
  da estadia

  FILE *f_cli: Ponteiro para o arquivo de clientes, passado para a função localizaCliente para verificar se o cliente
  informado existe.
  */
  estadia est;
  quarto qua;
  cliente cli;
  int cont = 0;

  printf(">> BUSCAR ESTADIAS DE UM CLIENTE: \n\n");

  printf("Digite o código do cliente que quer exibir as estadias: ");
  scanf("%i", &cli.codigo);

  int checkCli = localizaCliente(f_cli, cli.codigo);

  while (checkCli == -1) {
    printf("\nO cliente não está cadastrado! ");
    printf("\nDigite um novo código: ");
    scanf("%i", &cli.codigo);

    checkCli = localizaCliente(f_cli, cli.codigo);
  }

  int checkEst = imprimeEstadia(f_est, cli.codigo);
}

void calculaPts(FILE *f_est, FILE *f_cli) {
  /*
  Este é o procedimento calculaPts

  O procedimento é responsável por calcular os pontos de fidelidade acumulados por um determinado cliente em todas as
  suas estadias e exibí-los no console

  Parâmetros:
  FILE *f_est: É o ponteiro para o arquivo de estadias, percorrido pela função calculaPtsEstadia para acumular os pontos
  de fidelidade ganhos por cada estadia (10 pontos para cada dia de uma estadia)

  FILE *f_cli: É o ponteiro para o arquivo de clientes, percorrido pela função localizaCliente para verificar
  se o cliente informado existe.
  */
  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> CALCULAR PONTOS DE FIDELIDADE \n\n");

  printf("Digite o código do cliente para exibir os pontos de fidelidade: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);

  while (checkCli == -1) {
    printf("\nO cliente não foi encontrado.");
    printf("\nDigite um outro código: ");
    scanf("%i", &est.codCli);

    checkCli = localizaCliente(f_cli, est.codCli);
  }

  int pontosTotais = calculaPtsEstadia(f_est, est.codCli);
  while (pontosTotais == -1) {
    printf("\nEstadias do cliente não encontradas. ");
    printf("Digite outro código: ");
    scanf("%i", &est.codCli);
    pontosTotais = calculaPtsEstadia(f_est, est.codCli);
  }

  printf("\nO cliente informado possui %i pontos no programa de fidelidade. ",
         pontosTotais);
  printf("\n\n");
}

int geraCodigo(int min, int max) {
  /*
    Esta é a função geraCodigo

    Descrição: A função gera um número de cinco dígitos aleatório para atuar como um código de identificação pessoal
    dentro do contexto em que é utilizada

    Parâmetros:
    int min: número mínimo do intervalo
    int max: número máximo do intervalo

    Retorno:
    tipo: int
    Valores: número aleatório entre o número mínimo e máximo para ser usado como
    código
  */

  return min + rand() % (max - min + 1);
}

int localizaCliente(FILE *f, int codigo) {
  /*
  Esta é a função localizaCliente

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código do cliente informado, que será usado na condição if que verifica se este código corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;
  cliente cli;

  fseek(f, 0, SEEK_SET);
  fread(&cli, sizeof(cli), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (cli.codigo == codigo) {
      achou = 1;
    }
    fread(&cli, sizeof(cli), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaFuncionario(FILE *f, int codigo) {
  /*
  Esta é a função localizaFuncionario

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código do funcionário informado, que será usado na condição if que verifica se este código corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;

  funcionario fun;
  fseek(f, 0, SEEK_SET);
  fread(&fun, sizeof(fun), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (fun.codigo == codigo) {
      achou = 1;
    }
    fread(&fun, sizeof(fun), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaQuarto(FILE *f, int numero) {
  /*
  Esta é a função localizaQuarto

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O número do quarto informado, que será usado na condição if que verifica se este número corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o número novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;

  quarto qua;
  fseek(f, 0, SEEK_SET);
  fread(&qua, sizeof(qua), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (qua.numero == numero) {
      achou = 1;
    }
    fread(&qua, sizeof(qua), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaQuartoPorInfo(FILE *f_qua, int quantHosp) {
  /*
  Esta é a função localizaQuartoPorInfo

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde a quantidade de hóspedes e possui a string de status com valor "desocupado" 
  então o número do quarto encontrado

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int quantHosp: A quantidade de hóspedes que precisam se hospedar em um quarto, a função encontra um quarto que
  acomode a exata quantidade necessária ou superior caso não exista um que acomode a quantidade exata

  Retorno:
  tipo: int
  Valores: 
  qua.numero: o atributo número da estrutura de quartos que foi encontrada.
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0, minDif = INT_MAX, menor;

  quarto qua;
  fseek(f_qua, 0, SEEK_SET);

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if (strcmp(qua.status, "desocupado") == 0 && qua.quantHosp == quantHosp) {
      achou = 1;
      strcpy(qua.status, "ocupado");

      fseek(f_qua, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f_qua);
      fflush(f_qua);

      return qua.numero;
    }
    posicao++;
  }

  fseek(f_qua, 0, SEEK_SET);
  posicao = 1;

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if (strcmp(qua.status, "desocupado") == 0 && qua.quantHosp > quantHosp) {
      strcpy(qua.status, "ocupado");
      printf("\nEncontrado quarto %i", qua.numero);

      fseek(f_qua, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f_qua);
      fflush(f_qua);

      return qua.numero;
    }
    posicao++;
  }
  return -1;
}

float diariaQuartoPorNum(FILE *f, int numero) {
  /*
  Esta é a função diariaQuartoPorNum

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número do quarto na estadia encontrada, para então buscar o atributo qua.diaria
  que contém o valor da diária deste quarto e multiplicar pela quantidade de diárias da estadia

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int numero: O número do quarto da estadia

  Retorno:
  tipo: float
  Valores: 
  valor: o valor final a ser pago pelo cliente na estadia calculado pela função calculaValorEstadia.
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;
  float valor;

  quarto qua;
  fseek(f, 0, SEEK_SET);
  fread(&qua, sizeof(qua), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (qua.numero == numero) {
      achou = 1;
      valor = qua.diaria;
      strcpy(qua.status, "desocupado");

      fseek(f, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f);
      fflush(f);
    }
    fread(&qua, sizeof(qua), 1, f);
  }
  if (achou) {
    return valor;
  } else {
    return -1;
  }
}

float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli) {
  /*
  Esta é a função calculaValorEstadia

  Descrição: A função tem como parâmetro os arquivos de estadias, quartos e o código de cliente passado pela
  função que a chama

  Parâmetros:
  FILE *f_est: O ponteiro para o arquivo de estadias que será percorrido até achar uma estadia correspondente ao código
  de cliente 

  FILE *f_qua: O ponteiro para o arquivo de quartos que será usado na função diariaQuartoPorNum para ler o valor
  da diária do quarto correspondente

  int codCli: O código informado

  Retorno:
  tipo: float
  Valores: 
  valor: o valor final a ser pago pelo cliente na estadia (diárias a serem pagas * valor da diária no quarto).
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int achou = 0;
  float valor = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1 && !achou) {
    if (est.codCli == codCli) {
      achou = 1;

      int diarias = calculaDiarias(est.dataEntrada, est.dataSaida);
      valor = diarias * diariaQuartoPorNum(f_qua, est.quarto);
    }
  }
  if (!achou) {
    return -1;
  } else {
    return valor;
  }
}

void imprimeCliente(FILE *f, int codigo) {
  /*
  Este é o procedimento imprimeCliente

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, posicao = 1;
  cliente cli;

  fseek(f, 0, SEEK_SET);

  while (fread(&cli, sizeof(cli), 1, f) == 1) {
    posicao++;
    if (cli.codigo == codigo) {
      achou = 1;

      printf("\nCliente código %i", cli.codigo);
      printf("\nNome: %s", cli.nome);
      printf("\nEndereço: %s", cli.ender);
      printf("\nTelefone: %i", cli.telefone);

      printf("\n\n");
    }
  }

  if (!achou) {
    return;
  }
}

void imprimeFuncionario(FILE *f, int codigo) {
  /*
  Este é o procedimento imprimeFuncionario

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, posicao = 1;
  funcionario fun;

  fseek(f, 0, SEEK_SET);

  while (fread(&fun, sizeof(fun), 1, f) == 1) {
    posicao++;
    if (fun.codigo == codigo) {
      achou = 1;

      printf("\nCliente código %i", fun.codigo);
      printf("\nNome: %s", fun.nome);
      printf("\nTelefone: %i", fun.telefone);
      printf("\nCargo: %s", fun.cargo);
      printf("\nSalário: R$ %.2f", fun.salario);

      printf("\n\n");
    }
  }

  if (!achou) {
    return;
  }
}

int imprimeEstadia(FILE *f_est, int codCli) {
  /*
  Este é o procedimento imprimeEstadia

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, cont = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1) {
    if (est.codCli == codCli) {
      achou = 1;
      cont++;

      int anoE, mesE, diaE, anoS, diaS, mesS;

      desmontaData(est.dataEntrada, &anoE, &mesE, &diaE);
      desmontaData(est.dataSaida, &anoS, &mesS, &diaS);

      printf("\nESTADIA %i:\n", cont);

      printf("\nEstadia para %i hóspedes", est.quantHosp);
      printf("\nCheck-in: %i/%i/%i ", diaE, mesE, anoE);
      printf("\nCheck-out: %i/%i/%i \n", diaS, mesS, anoS);

      printf("\n");
    }
  }
  if (!achou) {
    printf("\nNenhuma estadia encontrada para o cliente. \n\n");
  }
}

int calculaDiarias(int dataIn, int dataOut) {
  /*
  Esta é a função calculaEstadias

  A função recebe como parâmetros a data de chek-in e check-out de uma determinada estadia para calcular a quantidade
  de diárias que devem ser pagas.

  Parâmetros: 
  int dataIn: data de checkin da estadia no formato "ANOMESDIA" sem hífens ou barras

  int dataOut: data de checkout da estadia no formato "ANOMESDIA" sem hífens ou barras

  Retorno:
  tipo: int
  Valores: 
  diasOut - diasIn: a diferença entre as datas da estadia em formato de dias do ano
  */
  int anoIn = dataIn / 10000;
  int mesIn = (dataIn % 10000) / 100;
  int diaIn = dataIn % 100;

  int anoOut = dataOut / 10000;
  int mesOut = (dataOut % 10000) / 100;
  int diaOut = dataOut % 100;

  int diasIn = diasRef(anoIn, mesIn, diaIn);
  int diasOut = diasRef(anoOut, mesOut, diasOut);

  return diasOut - diasIn;
}

void desmontaData(int data, int *ano, int *mes, int *dia) {
  /*
  Este é o procedimento desmontaData

  O procedimento recebe uma data bruta e a desmembra nas variáveis de mês, ano e dia

  Parâmetros:
  int data: A data bruta a ser desmembrada

  int *ano: ponteiro para ano, passado por referência que será usado em uma impressão no console

  int *mes: ponteiro para mes, passado por referência que será usado em uma impressão no console

  int *dia: ponteiro para dia, passado por referência que será usado em uma impressão no console
  */
  *ano = data / 10000;
  *mes = (data % 10000) / 100;
  *dia = data % 100;
}

int calculaPtsEstadia(FILE *f_est, int codCli) {
  /*
  Esta é a função calculaPtsEstadia

  A função lê o arquivo e encontra o registro correspondente ao código, e então usa o valor das diárias com base na
  data de checkin e checkout da estadia atual e as multiplica por 10, armazenando o valor em uma variável que soma
  os valores dos pontos de cada estadia que atende à condição.

  Parâmetros:
  FILE *f_est: O ponteiro para o arquivo onde estão guardadas as estadias
  int codCli: o código do cliente informado

  Retorno:/*
Este é o arquivo "Process.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Process", que
implementa as principais funções que são utilizadas pelo programa principal no
"main.c" e as que são utilizadas na própria biblioteca para complementá-las

Funções:
void limparEntrada()

int geraCodigo(int min, int max)

int localizaCliente(FILE *f, int codigo)
int localizaFuncionario(FILE *f, int codigo)
int localizaQuarto(FILE *f, int numero)
int localizaQuartoPorInfo(FILE *f_qua, int quantHosp)
float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli)

int calculaDiarias(int dataIn, int dataOut)
void desmontaData(int data, int *ano, int *mes, int *dia)
float diariaQuartoPorNum(FILE *f, int numero)
int calculaPtsEstadia(FILE *f_est, int codCli)

void imprimeCliente(FILE *f, int codigo)
void imprimeFuncionario(FILE *f, int codigo)
int imprimeEstadia(FILE *f_est, FILE *f_qua, int codigo)

Autor: João Alvaro Rodrigues Araujo
Data de início: 14 Jun. 2024
*/

#include "Datas.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tcliente {
  /*
  Esta é uma estrutura para os dados do Cliente.

  Descrição: a estrutura declara variáveis com os dados do código, nome,
  endereço e telefone do usuário, que serão preenchidos no procedimento de
  cadastro de cliente.

  Atributos:
  int codigo
  char nome[100]
  char ender[200]
  int telefone
  */

  int codigo;
  char nome[100];
  char ender[200];
  int telefone;
};
typedef struct Tcliente cliente;

struct Tfuncionario {
  /*
  Esta é uma estrutura para os dados do funcionário.

  Descrição: a estrutura declara variáveis com os dados do código, nome,
  telefone, cargo e salário do funcionário, que serão preenchidos no
  procedimento de cadastro de funcionário

  Atributos:
  int codigo
  char nome[100]
  int telefone
  char cargo[80]
  float salario
  */

  int codigo;
  char nome[100];
  int telefone;
  char cargo[80];
  float salario;
};
typedef struct Tfuncionario funcionario;

struct Tquarto {
  /*
  Esta é uma estrutura para os dados do quarto.

  Descrição: a estrutura declara variáveis com os dados do número do quarto a
  ser cadastrado, a quantidade de hóspedes, o valor da diária e o status do
  quarto (ocupado e desocupado)

  Atributos:
  int numero
  int quantHosp
  float diaria
  char status[10]
  */

  int numero;
  int quantHosp;
  float diaria;
  char status[10];
};
typedef struct Tquarto quarto;

struct Testadia {
  /*
  Esta é uma estrutura para os dados da estadia.

  Descrição: a estrutura declara variáveis com os dados do código do cliente no
  qual a estadia vai ser ser cadastrada, a quantidade de hóspedes desejada, as
  datas de entrada e saída da estadia e o número do quarto reservado.

  Atributos:
  int codCli
  int quantHosp
  int dataEntrada
  int dataSaida
  int quarto
  */
  int codCli;
  int quantHosp;
  int dataEntrada;
  int dataSaida;
  int quarto;
};
typedef struct Testadia estadia;

void limparEntrada();

int geraCodigo(int min, int max);

int localizaCliente(FILE *f, int codigo);
int localizaFuncionario(FILE *f, int codigo);
int localizaQuarto(FILE *f, int numero);
int localizaQuartoPorInfo(FILE *f_qua, int quantHosp);
float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli);

int calculaDiarias(int dataIn, int dataOut);
void desmontaData(int data, int *ano, int *mes, int *dia);
int calculaPtsEstadia(FILE *f_est, int codCli);

void imprimeCliente(FILE *f, int codigo);
void imprimeFuncionario(FILE *f, int codigo);
int imprimeEstadia(FILE *f_est, int codigo);

void limparEntrada() {
  /*
  Este é o procedimento limparEntrada().

  Descrição: O procedimento lê um caractere da entrada e a percorre até econtrar
  uma nova linha ou fim de arquivo, com o objetivo de descartar os caracteres da
  entrada para limpar o buffer

  Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
  código não vai retornar um valor.
  */

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void lerClientes(FILE *f) {
  /*
  Este é o procedimento lerClientes

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de clientes e exibir todas as estruturas registradas no
  arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadCliente, que
  por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  cliente cli;
  fseek(f, 0, SEEK_SET);
  while (fread(&cli, sizeof(cli), 1, f) == 1) {
    printf("Código: %d\n", cli.codigo);
    printf("Nome: %s\n", cli.nome);
    printf("Endereço: %s\n", cli.ender);
    printf("Telefone: %d\n\n", cli.telefone);
  }
}

void cadCliente(FILE *f) {
  /*
    Este é o procedimento cadCliente().

    Descrição: O procedimento é reponsável por ler informações do cliente e
    guardá-las na estrutura Tcliente, tal como gerar automaticamente um código
    para o cliente e evitar a repetição de códigos para clientes diferentes.

    Parâmetros:
    FILE *f: Ponteiro para o arquivo passado pelo main() no arquivo main.c ao
    selecionar a respectiva opção no menu, é o arquivo em que a função escreve,
    verifica a existência do código informado e exibe os dados através dos
    procedimentos localizaCliente e lerClientes.
  */

  cliente cli;
  int posicao;

  cli.codigo = geraCodigo(10000, 99999);
  fflush(stdin);
  posicao = localizaCliente(f, cli.codigo);

  while (posicao != -1) {
    cli.codigo = geraCodigo(10000, 99999);
    posicao = localizaCliente(f, cli.codigo);
  }

  limparEntrada();
  printf(">> CADASTRAR UM CLIENTE \n\n");

  printf("Digite o nome do cliente: ");
  fgets(cli.nome, sizeof(cli.nome), stdin);
  cli.nome[strcspn(cli.nome, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");
  fgets(cli.ender, sizeof(cli.ender), stdin);
  cli.ender[strcspn(cli.ender, "\n")] = '\0';

  printf("Digite o telefone do cliente: ");
  scanf("%i", &cli.telefone);
  limparEntrada();

  fseek(f, 0, SEEK_END);
  fwrite(&cli, sizeof(cli), 1, f);
  fflush(f);

  printf("\n");

  lerClientes(f);
}

void lerFuncionarios(FILE *f) {
  /*
  Este é o procedimento lerFuncionarios

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de funcionários e exibir todas as estruturas
  registradas no arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadFuncionario,
  que por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  funcionario fun;
  fseek(f, 0, SEEK_SET);
  while (fread(&fun, sizeof(fun), 1, f) == 1) {
    printf("Código: %d\n", fun.codigo);
    printf("Nome: %s\n", fun.nome);
    printf("Cargo: %s\n", fun.cargo);
    printf("Telefone: %i\n", fun.telefone);
    printf("Salário: R$ %.2f\n\n", fun.salario);
  }
}

void cadFuncionario(FILE *f) {
  /*
    Este é o procedimento cadFuncionario.

    Descrição: O procedimento é reponsável por ler informações do funcionário e
    guardá-las na estrutura Tfuncionario, tal como gerar automaticamente um
    código para o funcionário e evitar a repetição de códigos para funcionários
    diferentes.

    Parâmetros:
    FILE *f: Um ponteiro para o arquivo passado pelo programa principal no
    arquivo main.c, onde serão registrados todos os dados dos fucionários
    cadastrados para então serem exibidos através do procedimento
    lerFuncionarios
  */

  funcionario fun;
  int posicao;

  fun.codigo = geraCodigo(10000, 99999);
  fflush(stdin);
  posicao = localizaFuncionario(f, fun.codigo);

  while (posicao != -1) {
    fun.codigo = geraCodigo(10000, 99999);
    posicao = localizaFuncionario(f, fun.codigo);
  }

  limparEntrada();
  printf(">> CADASTRAR UM FUNCIONÁRIO \n\n");

  printf("Digite o nome do funcionário: ");
  fgets(fun.nome, sizeof(fun.nome), stdin);
  fun.nome[strcspn(fun.nome, "\n")] = '\0';

  printf("Digite o cargo do funcionário: ");
  fgets(fun.cargo, sizeof(fun.cargo), stdin);
  fun.cargo[strcspn(fun.cargo, "\n")] = '\0';

  printf("Digite o telefone do funcionário: ");
  scanf("%i", &fun.telefone);
  limparEntrada();

  printf("Digite o salário do funcionário: ");
  scanf("%f", &fun.salario);

  fseek(f, 0, SEEK_END);
  fwrite(&fun, sizeof(fun), 1, f);
  fflush(f);

  printf("\n");

  lerFuncionarios(f);
}

void lerQuartos(FILE *f) {
  /*
  Este é o procedimento lerQuartos

  Descrição: O procedimento é responsável por percorrer o arquivo onde estão
  guardados os registros de quartos e exibir todas as estruturas registradas no
  arquivo até o momento com seus dados devidamente organizados.

  Parâmetros:
  FILE *f: Um ponteiro para um arquivo passado pelo procedimento cadQuarto, que
  por sua vez é passado pelo programa principal em main.c É o arquivo que a
  função vai ler e detectar os dados que devem ser impressos.
  */
  quarto qua;
  fseek(f, 0, SEEK_SET);
  while (fread(&qua, sizeof(qua), 1, f) == 1) {
    printf("Número: %i\n", qua.numero);
    printf("Quantidade de hóspedes: %i\n", qua.quantHosp);
    printf("Valor da diária: R$ %.2f\n", qua.diaria);
    printf("O quarto está %s.\n\n", qua.status);
  }
}

void cadQuarto(FILE *f) {
  /*
    Este é o procedimento cadQuarto().

    Descrição: O procedimento é reponsável por ler informações do quarto e
    guardá-las na estrutura Tquarto, tal como processar o número inserido pelo
    usuário e atribuir o status ao quarto e garantir que quartos diferentes não
    tenham o mesmo número.

    Parâmetros:
    FILE *f: Um ponteiro para o arquivo passado em main.c onde os quartos serão
    registrados a cada novo cadastro, e depois serão utilizados para
    verificações e exibições no procedimento.
  */

  quarto qua;
  int ocupado;

  limparEntrada();
  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");
  scanf("%i", &qua.numero);
  int posicao = localizaQuarto(f, qua.numero);

  while (qua.numero <= 0) {
    printf("\nErro! Número de quarto inválido!\n");
    printf("Digite outro número: ");
    scanf("%i", &qua.numero);
  }

  while (posicao != -1) {
    printf("\nErro! Já há um quarto com esse número!\n");
    printf("Digite outro número: ");
    scanf("%i", &qua.numero);
    posicao = localizaQuarto(f, qua.numero);
  }

  printf("Digite a quantidade de hóspedes: ");
  scanf("%i", &qua.quantHosp);

  printf("Digite o valor da diária: ");
  scanf("%f", &qua.diaria);

  printf("Digite o status do quarto (0 desocupado, 1 ocupado): ");
  scanf("%i", &ocupado);

  while (ocupado != 0 && ocupado != 1) {
    printf("\nErro! Status de quarto inválido! \n");
    printf("Digite novamente: ");
    scanf("%i", &ocupado);
  }

  if (ocupado == 1) {
    strcpy(qua.status, "ocupado");
  } else {
    strcpy(qua.status, "desocupado");
  }

  limparEntrada();

  fseek(f, 0, SEEK_END);
  fwrite(&qua, sizeof(qua), 1, f);
  fflush(f);
  printf("\n");

  lerQuartos(f);
}

void lerEstadias(FILE *f) {
  /*
  Este é o procedimento lerEstadias

  O procedimento é responsável por exibir no console os dados da estrutura
  Testadia no arquivo de estadias percorrendo o arquivo e imprimindo todos os
  dados de cada um dos registros feitos.

  Parâmetros:
  FILE *f: É um ponteiro para um arquivo passado pelo procedimento cadEstadia,
  que por sua vez é passado pelo programa principal, é o arquivo em que todas as
  operações com estadias serão realizadas.
  */
  estadia est;
  fseek(f, 0, SEEK_SET);
  while (fread(&est, sizeof(est), 1, f) == 1) {
    printf("Código do cliente: %i\n", est.codCli);
    printf("Quantidade de hóspedes: %i\n", est.quantHosp);
    printf("Data de entrada: %i \n", est.dataEntrada);
    printf("Data de saída: %i \n", est.dataSaida);
    printf("Quarto reservado: %i \n\n", est.quarto);
  }
}

void cadEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  /*
    Este é o procedimento cadEstadia().

    Descrição: O procedimento é responsável por guardar os dados fornecidos na
    estrutura Testadia e escrevê-los no arquivo de estadias, tal como exibí-los
    no console através do procedimento lerEstadias. O procedimento verifica se o
    cliente informado está cadastrado e se há um quarto disponível para a
    quantidade informada de hóspedes ou superior, caso não haja um

    Parâmetros:
    FILE *f_est: É o ponteiro para o arquivo de estadias, que é usado para
    guardar os registros feitos pelo usuário e exibí-los pelo procedimento
    lerEstadias

    FILE *f_cli: Este agora é um ponteiro para o arquivo de clientes, que é
    usado para verificar se o cliente informado pelo usuário existe através da
    função localizaCliente

    FILE *f_qua: E este é o ponteiro para o arquivo de quartos, onde estão
    guardados todos os registros de quartos já feitos pelo usuário, que serão
    verificados pela função localizaQuarto para encontrar um que possua a
    capacidade adequada
  */

  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer cadastrar sua estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);

  while (checkCli == -1) {
    printf("O cliente não está cadastrado! \n");
    printf("Digite outro código: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
  }

  printf("\n> Cadastrando estadia do cliente. \n\n");

  printf("Digite a quantidade de hóspedes que querem se hospedar: ");
  scanf("%i", &est.quantHosp);

  printf("Digite a data de check-in no hotel ('ANOMESDIA' - sem espaços, "
         "hífens ou barras): ");
  scanf("%i", &est.dataEntrada);
  printf("Digite a data de check-out no hotel ('ANOMESDIA' - sem espaços, "
         "hífens ou barras): ");
  scanf("%i", &est.dataSaida);

  int checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);

  while (est.quantHosp <= 0) {
    printf("\nQuantidade de hóspedes inválida! \n");
    printf("Digite outra quantidade de hóspedes: ");
    scanf("%i", &est.quantHosp);
  }

  while (checkQua == -1) {
    printf("Não há quartos disponíveis para %i hóspedes por enquanto. ",
           est.quantHosp);
    printf("Digite outra quantidade de hóspedes: ");
    scanf("%i", &est.quantHosp);
    checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);
  }

  est.quarto = localizaQuartoPorInfo(f_qua, est.quantHosp);

  printf("\nO número de diárias a serem pagas é %i\n",
         calculaDiarias(est.dataEntrada, est.dataSaida));

  fseek(f_est, 0, SEEK_END);
  fwrite(&est, sizeof(est), 1, f_est);
  fflush(f_est);

  printf("\n");

  lerEstadias(f_est);
}

void baixaEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  /*
  Este é o procedimento baixaEstadia

  Descrição: O procedimento é responsável por ler o código de cliente informado e dar baixa na primeira estadia
  em aberto encontrada com este código, e exibir o valor final a ser pago no console.

  Parâmetros:
  FILE *f_est: É o ponteiro para o arquivo de estadias, que é usado para encontrar a estadia registrada com o código
  informado.

  FILE *f_cli: Este agora é um ponteiro para o arquivo de clientes, que é
  usado para verificar se o cliente informado pelo usuário existe através da
  função localizaCliente

  FILE *f_qua: E este é o ponteiro para o arquivo de quartos, onde estão
  guardados todos os registros de quartos já feitos pelo usuário, que serão
  percorridos pela função calculaValorEstadia para encontrar o valor da diária do quarto e usá-lo para calcular o
  preço final da estadia
  */
  estadia est;
  cliente cli;
  quarto qua;

  limparEntrada();
  printf(">> DAR BAIXA EM UMA ESTADIA\n\n");

  printf("Digite o código do cliente que cadastrou a estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);
  int checkEst = calculaValorEstadia(f_est, f_qua, est.codCli);

  while (checkCli == -1 || checkEst == -1) {
    printf("\nO cliente ou a estadia não estão cadastrados! \n");
    printf("\nDigite o código de um cliente cadastrado que possui uma estadia "
           "cadastrada: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
    checkEst = calculaValorEstadia(f_est, f_qua, est.codCli);
  }

  printf("\n> Dando baixa na estadia do cliente. \n\n");

  float valor = calculaValorEstadia(f_est, f_qua, est.codCli);
  printf("\nO valor total a ser pago é R$ %.2f", valor);
}

void pesquisa(FILE *f_cli, FILE *f_fun) {
  /*
  Este é o procedimento pesquisa

  O procedimento serve para ler o código de um cliente ou funcionário e exibir seus dados no console, lendo os arquivos
  de clientes e funcionários até encontrar um código correspondente. Caso não exista nem um cliente nem um funcionário
  com o código informado, o procedimento pede um novo código ao usuário até que a condição seja verdadeira para um deles

  Parâmetros:
  FILE *f_cli: O ponteiro para o arquivo de clientes, percorrido pela função localizaCliente para encontrar o cliente
  correspondente ao código caso exista

  FILE *f_fun: O ponteiro para o arquivo de funcionários, percorrido pela função localizaFuncionario para encontrar
  o funcionário correspondente ao código caso exista
  */
  cliente cli;
  funcionario fun;
  int codSearch;

  limparEntrada();
  printf(">> PESQUISAR CLIENTES E FUNCIONÁRIOS \n\n");

  printf("Digite o código do cliente ou funcionário que deseja pesquisar: ");
  scanf("%i", &codSearch);

  int checkCli = localizaCliente(f_cli, codSearch);
  int checkFun = localizaFuncionario(f_fun, codSearch);

  while (checkCli == -1 && checkFun == -1) {
    printf("\nNão há um funcionário ou cliente correspondente. ");
    printf("\nDigite outro código: ");
    scanf("%i", &codSearch);
    checkCli = localizaCliente(f_cli, codSearch);
    checkFun = localizaFuncionario(f_fun, codSearch);
  }

  imprimeCliente(f_cli, codSearch);
  imprimeFuncionario(f_fun, codSearch);
}

void buscaEstadia(FILE *f_est, FILE *f_qua, FILE *f_cli) {
  /*
  Este é o procedimento buscaEstadia

  O procedimento tem como objetivo ler e exibir todas as estadias cadastradas em um determinado código de usuário
  no console.

  Parâmetros:
  FILE *f_est: Ponteiro para o arquivo de estadias, usado para verificar as estadias correspondentes ao código e exibir
  na tela através do procedimento imprimeEstadia

  FILE *f_qua: Ponteiro para o arquivo de quartos, passado para o procedimento imprimeEstadia para imprimir os dados
  da estadia

  FILE *f_cli: Ponteiro para o arquivo de clientes, passado para a função localizaCliente para verificar se o cliente
  informado existe.
  */
  estadia est;
  quarto qua;
  cliente cli;
  int cont = 0;

  printf(">> BUSCAR ESTADIAS DE UM CLIENTE: \n\n");

  printf("Digite o código do cliente que quer exibir as estadias: ");
  scanf("%i", &cli.codigo);

  int checkCli = localizaCliente(f_cli, cli.codigo);

  while (checkCli == -1) {
    printf("\nO cliente não está cadastrado! ");
    printf("\nDigite um novo código: ");
    scanf("%i", &cli.codigo);

    checkCli = localizaCliente(f_cli, cli.codigo);
  }

  int checkEst = imprimeEstadia(f_est, cli.codigo);
}

void calculaPts(FILE *f_est, FILE *f_cli) {
  /*
  Este é o procedimento calculaPts

  O procedimento é responsável por calcular os pontos de fidelidade acumulados por um determinado cliente em todas as
  suas estadias e exibí-los no console

  Parâmetros:
  FILE *f_est: É o ponteiro para o arquivo de estadias, percorrido pela função calculaPtsEstadia para acumular os pontos
  de fidelidade ganhos por cada estadia (10 pontos para cada dia de uma estadia)

  FILE *f_cli: É o ponteiro para o arquivo de clientes, percorrido pela função localizaCliente para verificar
  se o cliente informado existe.
  */
  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> CALCULAR PONTOS DE FIDELIDADE \n\n");

  printf("Digite o código do cliente para exibir os pontos de fidelidade: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);

  while (checkCli == -1) {
    printf("\nO cliente não foi encontrado.");
    printf("\nDigite um outro código: ");
    scanf("%i", &est.codCli);

    checkCli = localizaCliente(f_cli, est.codCli);
  }

  int pontosTotais = calculaPtsEstadia(f_est, est.codCli);
  while (pontosTotais == -1) {
    printf("\nEstadias do cliente não encontradas. ");
    printf("Digite outro código: ");
    scanf("%i", &est.codCli);
    pontosTotais = calculaPtsEstadia(f_est, est.codCli);
  }

  printf("\nO cliente informado possui %i pontos no programa de fidelidade. ",
         pontosTotais);
  printf("\n\n");
}

int geraCodigo(int min, int max) {
  /*
    Esta é a função geraCodigo

    Descrição: A função gera um número de cinco dígitos aleatório para atuar como um código de identificação pessoal
    dentro do contexto em que é utilizada

    Parâmetros:
    int min: número mínimo do intervalo
    int max: número máximo do intervalo

    Retorno:
    tipo: int
    Valores: número aleatório entre o número mínimo e máximo para ser usado como
    código
  */

  return min + rand() % (max - min + 1);
}

int localizaCliente(FILE *f, int codigo) {
  /*
  Esta é a função localizaCliente

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código do cliente informado, que será usado na condição if que verifica se este código corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;
  cliente cli;

  fseek(f, 0, SEEK_SET);
  fread(&cli, sizeof(cli), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (cli.codigo == codigo) {
      achou = 1;
    }
    fread(&cli, sizeof(cli), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaFuncionario(FILE *f, int codigo) {
  /*
  Esta é a função localizaFuncionario

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código do funcionário informado, que será usado na condição if que verifica se este código corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;

  funcionario fun;
  fseek(f, 0, SEEK_SET);
  fread(&fun, sizeof(fun), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (fun.codigo == codigo) {
      achou = 1;
    }
    fread(&fun, sizeof(fun), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaQuarto(FILE *f, int numero) {
  /*
  Esta é a função localizaQuarto

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número passado, e então retorna a posição do número

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O número do quarto informado, que será usado na condição if que verifica se este número corresponde a 
  algum registro no arquivo

  Retorno:
  tipo: int
  Valores: 
  posicao: A posição no arquivo no qual o registro compatível foi encontrado
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o número novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;

  quarto qua;
  fseek(f, 0, SEEK_SET);
  fread(&qua, sizeof(qua), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (qua.numero == numero) {
      achou = 1;
    }
    fread(&qua, sizeof(qua), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int localizaQuartoPorInfo(FILE *f_qua, int quantHosp) {
  /*
  Esta é a função localizaQuartoPorInfo

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde a quantidade de hóspedes e possui a string de status com valor "desocupado" 
  então o número do quarto encontrado

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int quantHosp: A quantidade de hóspedes que precisam se hospedar em um quarto, a função encontra um quarto que
  acomode a exata quantidade necessária ou superior caso não exista um que acomode a quantidade exata

  Retorno:
  tipo: int
  Valores: 
  qua.numero: o atributo número da estrutura de quartos que foi encontrada.
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0, minDif = INT_MAX, menor;

  quarto qua;
  fseek(f_qua, 0, SEEK_SET);

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if (strcmp(qua.status, "desocupado") == 0 && qua.quantHosp == quantHosp) {
      achou = 1;
      strcpy(qua.status, "ocupado");

      fseek(f_qua, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f_qua);
      fflush(f_qua);

      return qua.numero;
    }
    posicao++;
  }

  fseek(f_qua, 0, SEEK_SET);
  posicao = 1;

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if (strcmp(qua.status, "desocupado") == 0 && qua.quantHosp > quantHosp) {
      strcpy(qua.status, "ocupado");
      printf("\nEncontrado quarto %i", qua.numero);

      fseek(f_qua, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f_qua);
      fflush(f_qua);

      return qua.numero;
    }
    posicao++;
  }
  return -1;
}

float diariaQuartoPorNum(FILE *f, int numero) {
  /*
  Esta é a função diariaQuartoPorNum

  Descrição: A função recebe como parâmetro um arquivo e um número. Ela percorre o arquivo fornecido até encontrar uma
  parte do registro que corresponde ao número do quarto na estadia encontrada, para então buscar o atributo qua.diaria
  que contém o valor da diária deste quarto e multiplicar pela quantidade de diárias da estadia

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int numero: O número do quarto da estadia

  Retorno:
  tipo: float
  Valores: 
  valor: o valor final a ser pago pelo cliente na estadia calculado pela função calculaValorEstadia.
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int posicao = 1, achou = 0;
  float valor;

  quarto qua;
  fseek(f, 0, SEEK_SET);
  fread(&qua, sizeof(qua), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (qua.numero == numero) {
      achou = 1;
      valor = qua.diaria;
      strcpy(qua.status, "desocupado");

      fseek(f, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f);
      fflush(f);
    }
    fread(&qua, sizeof(qua), 1, f);
  }
  if (achou) {
    return valor;
  } else {
    return -1;
  }
}

float calculaValorEstadia(FILE *f_est, FILE *f_qua, int codCli) {
  /*
  Esta é a função calculaValorEstadia

  Descrição: A função tem como parâmetro os arquivos de estadias, quartos e o código de cliente passado pela
  função que a chama

  Parâmetros:
  FILE *f_est: O ponteiro para o arquivo de estadias que será percorrido até achar uma estadia correspondente ao código
  de cliente 

  FILE *f_qua: O ponteiro para o arquivo de quartos que será usado na função diariaQuartoPorNum para ler o valor
  da diária do quarto correspondente

  int codCli: O código informado

  Retorno:
  tipo: float
  Valores: 
  valor: o valor final a ser pago pelo cliente na estadia (diárias a serem pagas * valor da diária no quarto).
  -1: indica que o registro não foi encontrado, pode ser utilizado para pedir o código novamente na função que irá 
  executar esta
  */
  int achou = 0;
  float valor = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1 && !achou) {
    if (est.codCli == codCli) {
      achou = 1;

      int diarias = calculaDiarias(est.dataEntrada, est.dataSaida);
      valor = diarias * diariaQuartoPorNum(f_qua, est.quarto);
    }
  }
  if (!achou) {
    return -1;
  } else {
    return valor;
  }
}

void imprimeCliente(FILE *f, int codigo) {
  /*
  Este é o procedimento imprimeCliente

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, posicao = 1;
  cliente cli;

  fseek(f, 0, SEEK_SET);

  while (fread(&cli, sizeof(cli), 1, f) == 1) {
    posicao++;
    if (cli.codigo == codigo) {
      achou = 1;

      printf("\nCliente código %i", cli.codigo);
      printf("\nNome: %s", cli.nome);
      printf("\nEndereço: %s", cli.ender);
      printf("\nTelefone: %i", cli.telefone);

      printf("\n\n");
    }
  }

  if (!achou) {
    return;
  }
}

void imprimeFuncionario(FILE *f, int codigo) {
  /*
  Este é o procedimento imprimeFuncionario

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, posicao = 1;
  funcionario fun;

  fseek(f, 0, SEEK_SET);

  while (fread(&fun, sizeof(fun), 1, f) == 1) {
    posicao++;
    if (fun.codigo == codigo) {
      achou = 1;

      printf("\nCliente código %i", fun.codigo);
      printf("\nNome: %s", fun.nome);
      printf("\nTelefone: %i", fun.telefone);
      printf("\nCargo: %s", fun.cargo);
      printf("\nSalário: R$ %.2f", fun.salario);

      printf("\n\n");
    }
  }

  if (!achou) {
    return;
  }
}

int imprimeEstadia(FILE *f_est, int codCli) {
  /*
  Este é o procedimento imprimeEstadia

  O procedimento recebe um arquivo e um código e retorna todos os registros correspondentes a esse código no arquivo
  com seus respectivos dados

  Parâmetros:
  FILE *f: O ponteiro para o arquivo a ser percorrido

  int codigo: O código passado para a função
  */
  int achou = 0, cont = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1) {
    if (est.codCli == codCli) {
      achou = 1;
      cont++;

      int anoE, mesE, diaE, anoS, diaS, mesS;

      desmontaData(est.dataEntrada, &anoE, &mesE, &diaE);
      desmontaData(est.dataSaida, &anoS, &mesS, &diaS);

      printf("\nESTADIA %i:\n", cont);

      printf("\nEstadia para %i hóspedes", est.quantHosp);
      printf("\nCheck-in: %i/%i/%i ", diaE, mesE, anoE);
      printf("\nCheck-out: %i/%i/%i \n", diaS, mesS, anoS);

      printf("\n");
    }
  }
  if (!achou) {
    printf("\nNenhuma estadia encontrada para o cliente. \n\n");
  }
}

int calculaDiarias(int dataIn, int dataOut) {
  /*
  Esta é a função calculaEstadias

  A função recebe como parâmetros a data de chek-in e check-out de uma determinada estadia para calcular a quantidade
  de diárias que devem ser pagas.

  Parâmetros: 
  int dataIn: data de checkin da estadia no formato "ANOMESDIA" sem hífens ou barras

  int dataOut: data de checkout da estadia no formato "ANOMESDIA" sem hífens ou barras

  Retorno:
  tipo: int
  Valores: 
  diasOut - diasIn: a diferença entre as datas da estadia em formato de dias do ano
  */
  int anoIn = dataIn / 10000;
  int mesIn = (dataIn % 10000) / 100;
  int diaIn = dataIn % 100;

  int anoOut = dataOut / 10000;
  int mesOut = (dataOut % 10000) / 100;
  int diaOut = dataOut % 100;

  int diasIn = diasRef(anoIn, mesIn, diaIn);
  int diasOut = diasRef(anoOut, mesOut, diasOut);

  return diasOut - diasIn;
}

void desmontaData(int data, int *ano, int *mes, int *dia) {
  /*
  Este é o procedimento desmontaData

  O procedimento recebe uma data bruta e a desmembra nas variáveis de mês, ano e dia

  Parâmetros:
  int data: A data bruta a ser desmembrada

  int *ano: ponteiro para ano, passado por referência que será usado em uma impressão no console

  int *mes: ponteiro para mes, passado por referência que será usado em uma impressão no console

  int *dia: ponteiro para dia, passado por referência que será usado em uma impressão no console
  */
  *ano = data / 10000;
  *mes = (data % 10000) / 100;
  *dia = data % 100;
}

int calculaPtsEstadia(FILE *f_est, int codCli) {
  /*
  Esta é a função calculaPtsEstadia

  A função lê o arquivo e encontra o registro correspondente ao código, e então usa o valor das diárias com base na
  data de checkin e checkout da estadia atual e as multiplica por 10, armazenando o valor em uma variável que soma
  os valores dos pontos de cada estadia que atende à condição.

  Parâmetros:
  FILE *f_est: O ponteiro para o arquivo onde estão guardadas as estadias
  int codCli: o código do cliente informado

  Retorno:
  tipo: int
  valores:
  somaPts: a soma total de pontos de fidelidade acumulados das estadias de um cliente
  -1: indica que as estadias não foram encontradas. pode ser tratado por outra função para pedir um novo código.
  */
  int achou = 0, somaPts = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1) {
    if (est.codCli == codCli) {
      achou = 1;

      int diarias = calculaDiarias(est.dataEntrada, est.dataSaida);
      int pts = 10 * diarias;
      somaPts += pts;
    }
  }
  if (!achou) {
    return -1;
  } else {
    return somaPts;
  }
}
  tipo: int
  valores:
  somaPts: a soma total de pontos de fidelidade acumulados das estadias de um cliente
  -1: indica que as estadias não foram encontradas. pode ser tratado por outra função para pedir um novo código.
  */
  int achou = 0, somaPts = 0;
  estadia est;

  fseek(f_est, 0, SEEK_SET);

  while (fread(&est, sizeof(est), 1, f_est) == 1) {
    if (est.codCli == codCli) {
      achou = 1;

      int diarias = calculaDiarias(est.dataEntrada, est.dataSaida);
      int pts = 10 * diarias;
      somaPts += pts;
    }
  }
  if (!achou) {
    return -1;
  } else {
    return somaPts;
  }
}