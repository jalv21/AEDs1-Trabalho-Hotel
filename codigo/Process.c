/*
Este é o arquivo "Process.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Process", que
implementa as principais funções que são utilizadas pelo programa principal no
"main.c" e as que são utilizadas na própria biblioteca para complementá-las

Funções:
void limparEntrada()

int gerarMin()
int gerarMax()
int geraCodigo(int min, int max)

void cadCliente()
void cadFuncionario()
void cadQuarto()


Autor: J
Data de início: 14 Jun. 2024
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Datas.h"

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
  int codCli;
  int quantHosp;
  int dataEntrada;
  int dataSaida;
};
typedef struct Testadia estadia;

void limparEntrada();
int geraCodigo(int min, int max);
int localizaCliente(FILE *f, int codigo);
int localizaFuncionario(FILE *f, int codigo);
int localizaQuarto(FILE *f, int numero);
int localizaQuartoPorInfo(FILE *f_qua, int quantHosp);
int calculaDiarias(int dataIn, int dataOut);
int localizaEstadia(FILE *f, int codigo);

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
  cliente cli;
  fseek(f, 0, SEEK_SET); // Voltar ao início do arquivo
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

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
    código não vai retornar um valor.
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
  funcionario fun;
  fseek(f, 0, SEEK_SET); // Voltar ao início do arquivo
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
    Este é o procedimento cadFuncionario().

    Descrição: O procedimento é reponsável por ler informações do funcionário e
    guardá-las na estrutura Tfuncionario, tal como gerar automaticamente um
    código para o funcionário e evitar a repetição de códigos para funcionários
    diferentes.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
    código não vai retornar um valor.
  */

  funcionario fun;
  int posicao;

  fun.codigo = geraCodigo(10000, 99999);
  fflush(stdin);
  posicao = localizaFuncionario(f, fun.codigo);

  while(posicao != -1) {
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
  quarto qua;
  fseek(f, 0, SEEK_SET); // Voltar ao início do arquivo
  while (fread(&qua, sizeof(qua), 1, f) == 1) {
    printf("Número: %d\n", qua.numero);
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

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
    código não vai retornar um valor.
  */

  quarto qua;
  int ocupado;

  limparEntrada();
  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");
  scanf("%i", &qua.numero);
  int posicao = localizaQuarto(f, qua.numero);

  while(qua.numero <= 0) {
    printf("\nErro! Número de quarto inválido!\n");
    printf("Digite outro número: ");
    scanf("%i", &qua.numero);
  }

  while(posicao != -1) {
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

  while(ocupado != 0 && ocupado != 1) {
    printf("\nErro! Status de quarto inválido! \n");
    printf("Digite novamente: ");
    scanf("%i", &ocupado);
  }

  if(ocupado == 1) {
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
  estadia est;
  fseek(f, 0, SEEK_SET); // Voltar ao início do arquivo
  while (fread(&est, sizeof(est), 1, f) == 1) {
    printf("Código do cliente: %d\n", est.codCli);
    printf("Quantidade de hóspedes: %i\n", est.quantHosp);
    printf("Data de entrada: %i \n", est.dataEntrada);
    printf("Data de saída: %i \n\n", est.dataSaida);
  }
}

void cadEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  /*
    Este é o procedimento cadEstadia().

    Descrição:

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o
    código não vai retornar um valor.
  */

  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer cadastrar sua estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);
  int checkEst = localizaEstadia(f_est, est.codCli);

  while(checkCli == -1) {
    printf("O cliente não está cadastrado! \n");
    printf("Digite outro código: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
  }

  printf("\n> Cadastrando estadia do cliente. \n\n");

  printf("Digite a quantidade de hóspedes que querem se hospedar: ");
  scanf("%i", &est.quantHosp);

  printf("Digite a data de check-in no hotel ('ANOMESDIA' - sem espaços, hífens ou barras): ");
  scanf("%i", &est.dataEntrada);
  printf("Digite a data de check-out no hotel ('ANOMESDIA' - sem espaços, hífens ou barras): ");
  scanf("%i", &est.dataSaida);

  int checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);

  while(est.quantHosp <= 0) {
    printf("\nQuantidade de hóspedes inválida! \n");
    printf("Digite outra quantidade de hóspedes: ");
    scanf("%i", &est.quantHosp);
  }

  while(checkQua == -1) {
      printf("Não há quartos disponíveis para %i hóspedes por enquanto. ", est.quantHosp);
      printf("Digite outra quantidade de hóspedes: ");
      scanf("%i", &est.quantHosp);
      checkQua = localizaQuartoPorInfo(f_qua, est.quantHosp);
  }

  printf("\nO número de estadias a serem pagas é %i\n", calculaDiarias(est.dataEntrada, est.dataSaida));

  fseek(f_est, 0, SEEK_END);
  fwrite(&est, sizeof(est), 1, f_est);
  fflush(f_est);

  printf("\n");

  lerEstadias(f_est);

  /* limparEntrada();

  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer se cadastrar: ");
  if (scanf("%i", &est.codCli) != 1) {
    printf("Erro de leitura na entrada de dados.");
  }

  printf("\nDigite a quantidade de hóspedes: ");
  if (scanf("%i", &est.quantHosp) != 1) {
    printf("Erro de leitura na entrada de dados.");
  }

  printf("\nDigite a data de entrada: ");
  if (scanf("%i", &dEntrEnter) != 1) {
    printf("Erro de leitura na entrada de dados.");
  }

  printf("\nDigite a data de saída: ");
  if (scanf("%i", &dSaiEnter) != 1) {
    printf("Erro de leitura na entrada de dados.");
  } */
}

void baixaEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua) {
  estadia est;
  cliente cli;

  limparEntrada();
  printf(">> DAR BAIXA EM UMA ESTADIA\n\n");

  printf("Digite o código do cliente que cadastrou a estadia: ");
  scanf("%i", &est.codCli);
  int checkCli = localizaCliente(f_cli, est.codCli);
  int checkEst = localizaEstadia(f_est, est.codCli);

  while(checkCli == -1 || checkEst == -1) {
    printf("O cliente ou a estadia não estão cadastrados! \n");
    printf("Digite o código de um cliente cadastrado que possui uma estadia cadastrada: ");
    scanf("%i", &est.codCli);
    checkCli = localizaCliente(f_cli, est.codCli);
    checkEst = localizaEstadia(f_est, est.codCli);
  }

  printf("\n> Dando baixa na estadia do cliente. \n\n");


}

int geraCodigo(int min, int max) {
  /*
    Esta é a função geraCodigo(int min, int max).

    Descrição: A função utiliza os dois números gerados pelos procedimentos como
    menor e maior número dentro de um intervalo de números aleatórios que podem
    ser gerados e retorna o número para ser usado como código para os
    procedimentos cadCliente e cadFuncionario

    Parâmetros:
    int min: número retornado pelo procedimento gerarMin
    int max: número retornado pelo procedimento gerarMax

    Retorno:
    tipo: int
    Valores: número aleatório entre o número mínimo e máximo para ser usado como
    código
  */

  return min + rand() % (max - min + 1);
}

int localizaCliente(FILE *f, int codigo) {
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
  int posicao = 1, achou = 0;

  quarto qua;
  fseek(f_qua, 0, SEEK_SET);

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if(strcmp(qua.status, "desocupado") == 0 && qua.quantHosp == quantHosp) {
        achou = 1;
        strcpy(qua.status, "ocupado");
        printf("Encontrado quarto %i", qua.numero);

        fseek(f_qua, -sizeof(qua), SEEK_CUR);
        fwrite(&qua, sizeof(qua), 1, f_qua);
        fflush(f_qua);

        return posicao;
    }
    posicao++;
  }

  fseek(f_qua, 0, SEEK_SET);
  posicao = 1;

  while (fread(&qua, sizeof(qua), 1, f_qua) == 1 && !achou) {
    if(strcmp(qua.status, "desocupado") == 0 && qua.quantHosp > quantHosp) {
      achou = 1;

      strcpy(qua.status, "ocupado");
      printf("Encontrado quarto %i", qua.numero);

      fseek(f_qua, -sizeof(qua), SEEK_CUR);
      fwrite(&qua, sizeof(qua), 1, f_qua);
      fflush(f_qua);

      return posicao;
    }
    posicao++;
  }
  return -1;
}

int localizaEstadia(FILE *f, int codCli) {
  int posicao = 1, achou = 0;

  estadia est;
  fseek(f, 0, SEEK_SET);
  fread(&est, sizeof(est), 1, f);

  while (!feof(f) && !achou) {
    posicao++;
    if (est.codCli == codCli) {
      achou = 1;
    }
    fread(&est, sizeof(est), 1, f);
  }
  if (achou) {
    return posicao;
  } else {
    return -1;
  }
}

int calculaDiarias(int dataIn, int dataOut) {
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