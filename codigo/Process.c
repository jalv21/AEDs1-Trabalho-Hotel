/*  
Este é o arquivo "Process.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Process", que implementa as principais funções que são utilizadas pelo programa principal no "main.c" e as que são utilizadas na própria biblioteca para complementá-las

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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void limparEntrada();
int gerarMin();
long int gerarMax();
int geraCodigo(int min, int max);

void limparEntrada() {
  /*
  Este é o procedimento limparEntrada().

  Descrição: O procedimento lê um caractere da entrada e a percorre até econtrar uma nova linha ou fim de arquivo, com o objetivo de descartar os caracteres da entrada para limpar o buffer

  Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

struct Tcliente {
  /*
  Esta é uma estrutura para os dados do Cliente.

  Descrição: a estrutura declara variáveis com os dados do código, nome, endereço e telefone do usuário, que serão 
  preenchidos no procedimento de cadastro de cliente. 

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

void cadCliente() {
  /*
    Este é o procedimento cadCliente().

    Descrição: O procedimento é reponsável por ler informações do cliente e guardá-las na estrutura Tcliente, tal como gerar automaticamente um código para o cliente e evitar a repetição de códigos para clientes diferentes.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  cliente cli;
  int codEnter, telEnter;
  char nomeEnter[100], endEnter[200];

  cli.codigo = geraCodigo(gerarMin(), gerarMax());
  codEnter = geraCodigo(gerarMin(), gerarMax());

  while (codEnter == cli.codigo) {
    codEnter = geraCodigo(gerarMin(), gerarMax());
  }

  cli.codigo = codEnter;

  limparEntrada();

  printf(">> CADASTRAR UM CLIENTE \n\n");

  printf("Digite o nome do cliente: ");

  if (fgets(nomeEnter, sizeof(nomeEnter), stdin) == NULL) {
    printf("Erro ao ler o nome do cliente.");
  }

  strcpy(cli.nome, nomeEnter);
  nomeEnter[strcspn(nomeEnter, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");

  if (fgets(endEnter, sizeof(endEnter), stdin) == NULL) {
    printf("Erro ao ler o endereço do cliente. ");
  }

  strcpy(cli.ender, endEnter);
  endEnter[strcspn(endEnter, "\n")] = '\0';

  printf("Digite o telefone do cliente: ");

  if (scanf("%i", &telEnter) != 1) {
    printf("Erro ao ler o telefone do cliente. ");
    limparEntrada();
  }

  cli.telefone = telEnter;

  limparEntrada();

  printf("\n");
}

struct Tfuncionario {
  /*
  Esta é uma estrutura para os dados do funcionário.

  Descrição: a estrutura declara variáveis com os dados do código, nome, telefone, cargo e salário do funcionário, que
  serão preenchidos no procedimento de cadastro de funcionário

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

void cadFuncionario() {
  /*
    Este é o procedimento cadFuncionario().

    Descrição: O procedimento é reponsável por ler informações do funcionário e guardá-las na estrutura Tfuncionario, tal como gerar automaticamente um código para o funcionário e evitar a repetição de códigos para funcionários diferentes.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  funcionario fun;
  int codEnter, telEnter;
  float salEnter;
  char nomeEnter[100], cargoEnter[80];

  fun.codigo = geraCodigo(gerarMin(), gerarMax());
  codEnter = geraCodigo(gerarMin(), gerarMax());

  while(codEnter == fun.codigo) {
    codEnter = geraCodigo(gerarMin(), gerarMax());
  }

  fun.codigo = codEnter;

  limparEntrada();

  printf(">> CADASTRAR UM FUNCIONÁRIO \n\n");

  printf("Digite o nome do funcionário: ");

  if (fgets(nomeEnter, sizeof(nomeEnter), stdin) == NULL) {
    printf("Erro ao ler o nome do funcionário. ");
  }

  strcpy(fun.nome, nomeEnter);
  nomeEnter[strcspn(nomeEnter, "\n")] = '\0';

  printf("Digite o telefone do funcionário: ");

  if (scanf("%i", &telEnter) != 1) {
    printf("Erro ao ler o telefone do usuário");
    limparEntrada();
  }

  fun.telefone = telEnter;

  limparEntrada();

  printf("Digite o cargo do funcionário: ");

  if (fgets(cargoEnter, sizeof(cargoEnter), stdin) == NULL) {
    printf("Erro ao ler o cargo do funcionário");
  }

  strcpy(fun.cargo, cargoEnter);
  cargoEnter[strcspn(cargoEnter, "\n")] = '\0';

  printf("Digite o salário do funcionário: ");

  if (scanf("%f", &salEnter) != 1) {
    printf("Erro ao ler o salário do funcionário.");
    limparEntrada();
  }

  fun.salario = salEnter;

  limparEntrada();

  /* printf("\n");

  printf("%s", fun.nome);
  printf("%i\n", fun.telefone);
  printf("%s", fun.cargo);
  printf("%.2f\n", fun.salario); */

  printf("\n");
}

struct Tquarto {
  /*
  Esta é uma estrutura para os dados do quarto.

  Descrição: a estrutura declara variáveis com os dados do número do quarto a ser cadastrado, a quantidade de hóspedes, o 
  valor da diária e o status do quarto (ocupado e desocupado)

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

void cadQuarto() {
  /*
    Este é o procedimento cadQuarto().

    Descrição: O procedimento é reponsável por ler informações do quarto e guardá-las na estrutura Tquarto, tal como 
    processar o número inserido pelo usuário e atribuir o status ao quarto e garantir que quartos diferentes não tenham o 
    mesmo número.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  quarto qrt;
  int numEnter, ocupado;

  limparEntrada();

  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");

  if (scanf("%i", &numEnter) != 1) {
    printf("Erro ao ler o número do quarto.");
    limparEntrada();
  }

  while(numEnter <= 0) {
    printf("\nErro! Nº de quarto inválido! Digite um novo número: ");
    if (scanf("%i", &numEnter) != 1) {
      printf("Erro ao ler o número do quarto.");
      limparEntrada();
    }
  } 

  while(numEnter == qrt.numero) {
    printf("\nErro! Já existe um quarto com esse número! Digite um novo número: ");
    if (scanf("%i", &numEnter) != 1) {
      printf("Erro ao ler o número do quarto.");
      limparEntrada();
    }
  }

  qrt.numero = numEnter;

  printf("Digite a quantidade de hóspedes: ");

  if (scanf("%i", &qrt.quantHosp) != 1) {
    printf("Erro ao ler a quantidade de hóspedes.");
    limparEntrada();
  }

  printf("Digite o valor da diária: ");

  if (scanf("%f", &qrt.diaria) != 1) {
    printf("Erro ao ler o valor da diaria.");
    limparEntrada();
  }

  printf("O quarto está ocupado? (0 não, 1 sim): ");

  if (scanf("%i", &ocupado) != 1) {
    printf("Erro ao ler o status do quarto. ");
    limparEntrada();
  };

  if (ocupado != 0 && ocupado != 1) {
    printf("ERRO! Status do quarto inválido!");
  } else {
    if (ocupado == 0) {
      strcpy(qrt.status, "desocupado");
    } else {
      strcpy(qrt.status, "ocupado");
    }
  }

  limparEntrada();

  printf("\n");
  printf("O número do quarto é: %i \n", qrt.numero);
  printf("A quantidade de hóspedes do quarto é: %i \n", qrt.quantHosp);
  printf("O valor da diária do quarto é: R$ %.2f \n", qrt.diaria);
  printf("O quarto está %s\n", qrt.status);

  printf("\n");
}

int carregaData(int part) {
  time_t t = time(NULL);
  struct tm *data = localtime(&t);

  return part;
}

struct Testadia {
  int codCli;
  int quantHosp;
  int dataEntrada;
  int dataSaida;
};
typedef struct Testadia estadia;

void cadEstadia() {
  /*
    Este é o procedimento cadEstadia().

    Descrição: 

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  estadia est;
  int dEntrEnter, dSaiEnter;

  limparEntrada();

  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer se cadastrar: ");
  scanf("%i", &est.codCli);

  printf("\nDigite a quantidade de hóspedes: ");
  scanf("%i", &est.quantHosp);

  printf("\nDigite a data de entrada: ");
  scanf("%i", &dEntrEnter);

  printf("\nDigite a data de saída: ");
  scanf("%i", &dSaiEnter);

  /* printf("Ano: %d\n", data->tm_year + 1900);
  printf("Mês: %d\n", data->tm_mon + 1);
  printf("Dia: %d\n", data->tm_mday); */
}

int gerarMin() {
  /*
    Este é o procedimento gerarMin().

    Descrição: O procedimento é reponsável por gerar um número aleatório para servir como o menor valor para um intervalo 
    de números que será usado pela função geraCodigo para gerar um código aleatório.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  int min = rand() % (9999 - 1000 + 1) + 1000;

  return min;
}

long int gerarMax() {
  /*
    Este é o procedimento gerarMax().

    Descrição: O procedimento é reponsável por gerar um número aleatório para servir como o maior valor para um intervalo 
    de números que será usado pela função geraCodigo para gerar um código aleatório.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  long int max = rand() % (9999999 - 1000000 + 1) + 1000000;

  return max;
}

int geraCodigo(int min, int max) {
  /*
    Esta é a função geraCodigo(int min, int max).

    Descrição: A função utiliza os dois números gerados pelos procedimentos como menor e maior número dentro de um 
    intervalo de números aleatórios que podem ser gerados e retorna o número para ser usado como código para os
    procedimentos cadCliente e cadFuncionario

    Parâmetros:
    int min: número retornado pelo procedimento gerarMin
    int max: número retornado pelo procedimento gerarMax

    Retorno:
    tipo: int
    Valores: número aleatório entre o número mínimo e máximo para ser usado como código
  */

  int codigo = rand() % (max - min + 1) + min;
  return codigo;
}

void CalculaData() {

}/*  
Este é o arquivo "Process.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Process", que implementa as principais funções que são utilizadas pelo programa principal no "main.c" e as que são utilizadas na própria biblioteca para complementá-las

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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void limparEntrada();
int gerarMin();
long int gerarMax();
int geraCodigo(int min, int max);

void limparEntrada() {
  /*
  Este é o procedimento limparEntrada().

  Descrição: O procedimento lê um caractere da entrada e a percorre até econtrar uma nova linha ou fim de arquivo, com o objetivo de descartar os caracteres da entrada para limpar o buffer

  Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

struct Tcliente {
  /*
  Esta é uma estrutura para os dados do Cliente.
  
  Descrição: a estrutura declara variáveis com os dados do código, nome, endereço e telefone do usuário, que serão 
  preenchidos no procedimento de cadastro de cliente. 
  
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

void cadCliente() {
  /*
    Este é o procedimento cadCliente().

    Descrição: O procedimento é reponsável por ler informações do cliente e guardá-las na estrutura Tcliente, tal como gerar automaticamente um código para o cliente e evitar a repetição de códigos para clientes diferentes.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  cliente cli;
  int codEnter, telEnter;
  char nomeEnter[100], endEnter[200];

  cli.codigo = geraCodigo(gerarMin(), gerarMax());
  codEnter = geraCodigo(gerarMin(), gerarMax());

  while (codEnter == cli.codigo) {
    codEnter = geraCodigo(gerarMin(), gerarMax());
  }

  cli.codigo = codEnter;

  limparEntrada();

  printf(">> CADASTRAR UM CLIENTE \n\n");

  printf("Digite o nome do cliente: ");

  if (fgets(nomeEnter, sizeof(nomeEnter), stdin) == NULL) {
    printf("Erro ao ler o nome do cliente.");
  }

  strcpy(cli.nome, nomeEnter);
  nomeEnter[strcspn(nomeEnter, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");

  if (fgets(endEnter, sizeof(endEnter), stdin) == NULL) {
    printf("Erro ao ler o endereço do cliente. ");
  }

  strcpy(cli.ender, endEnter);
  endEnter[strcspn(endEnter, "\n")] = '\0';

  printf("Digite o telefone do cliente: ");

  if (scanf("%i", &telEnter) != 1) {
    printf("Erro ao ler o telefone do cliente. ");
    limparEntrada();
  }

  cli.telefone = telEnter;

  limparEntrada();

  printf("\n");
}

struct Tfuncionario {
  /*
  Esta é uma estrutura para os dados do funcionário.
  
  Descrição: a estrutura declara variáveis com os dados do código, nome, telefone, cargo e salário do funcionário, que
  serão preenchidos no procedimento de cadastro de funcionário
  
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

void cadFuncionario() {
  /*
    Este é o procedimento cadFuncionario().

    Descrição: O procedimento é reponsável por ler informações do funcionário e guardá-las na estrutura Tfuncionario, tal como gerar automaticamente um código para o funcionário e evitar a repetição de códigos para funcionários diferentes.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  funcionario fun;
  int codEnter, telEnter;
  float salEnter;
  char nomeEnter[100], cargoEnter[80];

  fun.codigo = geraCodigo(gerarMin(), gerarMax());
  codEnter = geraCodigo(gerarMin(), gerarMax());

  while(codEnter == fun.codigo) {
    codEnter = geraCodigo(gerarMin(), gerarMax());
  }

  fun.codigo = codEnter;

  limparEntrada();

  printf(">> CADASTRAR UM FUNCIONÁRIO \n\n");

  printf("Digite o nome do funcionário: ");

  if (fgets(nomeEnter, sizeof(nomeEnter), stdin) == NULL) {
    printf("Erro ao ler o nome do funcionário. ");
  }

  strcpy(fun.nome, nomeEnter);
  nomeEnter[strcspn(nomeEnter, "\n")] = '\0';

  printf("Digite o telefone do funcionário: ");

  if (scanf("%i", &telEnter) != 1) {
    printf("Erro ao ler o telefone do usuário");
    limparEntrada();
  }

  fun.telefone = telEnter;

  limparEntrada();

  printf("Digite o cargo do funcionário: ");

  if (fgets(cargoEnter, sizeof(cargoEnter), stdin) == NULL) {
    printf("Erro ao ler o cargo do funcionário");
  }

  strcpy(fun.cargo, cargoEnter);
  cargoEnter[strcspn(cargoEnter, "\n")] = '\0';

  printf("Digite o salário do funcionário: ");

  if (scanf("%f", &salEnter) != 1) {
    printf("Erro ao ler o salário do funcionário.");
    limparEntrada();
  }

  fun.salario = salEnter;
  
  limparEntrada();

  /* printf("\n");
  
  printf("%s", fun.nome);
  printf("%i\n", fun.telefone);
  printf("%s", fun.cargo);
  printf("%.2f\n", fun.salario); */
  
  printf("\n");
}

struct Tquarto {
  /*
  Esta é uma estrutura para os dados do quarto.

  Descrição: a estrutura declara variáveis com os dados do número do quarto a ser cadastrado, a quantidade de hóspedes, o 
  valor da diária e o status do quarto (ocupado e desocupado)

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

void cadQuarto() {
  /*
    Este é o procedimento cadQuarto().

    Descrição: O procedimento é reponsável por ler informações do quarto e guardá-las na estrutura Tquarto, tal como 
    processar o número inserido pelo usuário e atribuir o status ao quarto e garantir que quartos diferentes não tenham o 
    mesmo número.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  quarto qrt;
  int numEnter, ocupado;
  
  limparEntrada();

  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");

  if (scanf("%i", &numEnter) != 1) {
    printf("Erro ao ler o número do quarto.");
    limparEntrada();
  }

  while(numEnter <= 0) {
    printf("\nErro! Nº de quarto inválido! Digite um novo número: ");
    if (scanf("%i", &numEnter) != 1) {
      printf("Erro ao ler o número do quarto.");
      limparEntrada();
    }
  } 

  while(numEnter == qrt.numero) {
    printf("\nErro! Já existe um quarto com esse número! Digite um novo número: ");
    if (scanf("%i", &numEnter) != 1) {
      printf("Erro ao ler o número do quarto.");
      limparEntrada();
    }
  }
 
  qrt.numero = numEnter;

  printf("Digite a quantidade de hóspedes: ");

  if (scanf("%i", &qrt.quantHosp) != 1) {
    printf("Erro ao ler a quantidade de hóspedes.");
    limparEntrada();
  }

  printf("Digite o valor da diária: ");

  if (scanf("%f", &qrt.diaria) != 1) {
    printf("Erro ao ler o valor da diaria.");
    limparEntrada();
  }

  printf("O quarto está ocupado? (0 não, 1 sim): ");

  if (scanf("%i", &ocupado) != 1) {
    printf("Erro ao ler o status do quarto. ");
    limparEntrada();
  };

  if (ocupado != 0 && ocupado != 1) {
    printf("ERRO! Status do quarto inválido!");
  } else {
    if (ocupado == 0) {
      strcpy(qrt.status, "desocupado");
    } else {
      strcpy(qrt.status, "ocupado");
    }
  }

  limparEntrada();

  printf("\n");
  printf("O número do quarto é: %i \n", qrt.numero);
  printf("A quantidade de hóspedes do quarto é: %i \n", qrt.quantHosp);
  printf("O valor da diária do quarto é: R$ %.2f \n", qrt.diaria);
  printf("O quarto está %s\n", qrt.status);

  printf("\n");
}

int carregaData(int part) {
  time_t t = time(NULL);
  struct tm *data = localtime(&t);

  return part;
}

struct Testadia {
  int codCli;
  int quantHosp;
  int dataEntrada;
  int dataSaida;
};
typedef struct Testadia estadia;

void cadEstadia() {
  /*
    Este é o procedimento cadEstadia().

    Descrição: 

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */

  estadia est;
  int dEntrEnter, dSaiEnter;

  limparEntrada();

  printf(">> CADASTRAR UMA ESTADIA \n\n");

  printf("Digite o código do cliente que quer se cadastrar: ");
  if(scanf("%i", &est.codCli) != 1) {
    printf("Erro ao ler o código. ");
    limparEntrada();
  }

  printf("\nDigite a quantidade de hóspedes: ");
  if(scanf("%i", &est.quantHosp) != 1) {
    printf("Erro ao ler a quant. de hóspedes. ");
    limparEntrada();
  }

  printf("\nDigite a data de entrada: ");
  if(scanf("%i", &dEntrEnter) != 1) {
    printf("Erro ao ler a data de entrada. ");
    limparEntrada();
  }

  printf("\nDigite a data de saída: ");
  if(scanf("%i", &dSaiEnter) != 1) {
    printf("Erro ao ler a data de saída. ");
    limparEntrada();
  }

  /* printf("Ano: %d\n", data->tm_year + 1900);
  printf("Mês: %d\n", data->tm_mon + 1);
  printf("Dia: %d\n", data->tm_mday); */
}

int gerarMin() {
  /*
    Este é o procedimento gerarMin().

    Descrição: O procedimento é reponsável por gerar um número aleatório para servir como o menor valor para um intervalo 
    de números que será usado pela função geraCodigo para gerar um código aleatório.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  int min = rand() % (9999 - 1000 + 1) + 1000;

  return min;
}

long int gerarMax() {
  /*
    Este é o procedimento gerarMax().

    Descrição: O procedimento é reponsável por gerar um número aleatório para servir como o maior valor para um intervalo 
    de números que será usado pela função geraCodigo para gerar um código aleatório.

    Este procedimento não tem parâmetros, e, por se tratar de um procedimento, o código não vai retornar um valor.
  */
  
  long int max = rand() % (9999999 - 1000000 + 1) + 1000000;

  return max;
}

int geraCodigo(int min, int max) {
  /*
    Esta é a função geraCodigo(int min, int max).

    Descrição: A função utiliza os dois números gerados pelos procedimentos como menor e maior número dentro de um 
    intervalo de números aleatórios que podem ser gerados e retorna o número para ser usado como código para os
    procedimentos cadCliente e cadFuncionario

    Parâmetros:
    int min: número retornado pelo procedimento gerarMin
    int max: número retornado pelo procedimento gerarMax

    Retorno:
    tipo: int
    Valores: número aleatório entre o número mínimo e máximo para ser usado como código
  */
  
  int codigo = rand() % (max - min + 1) + min;
  return codigo;
}

void CalculaData() {
  
}