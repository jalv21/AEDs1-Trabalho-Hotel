#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

// funções usadas na biblioteca
void limparBuffer();
int gerarMin();
long int gerarMax();
int geraCodigo(int min, int max);

// limpar o buffer na entrada do usuário
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// estrutura cliente
struct Tcliente {
  int codigo;
  char nome[100];
  char ender[200];
  int telefone;
};
typedef struct Tcliente cliente;

// função para cadastrar um cliente
void cadCliente() {
  cliente cli;
  int codCli, telCli;
  char nomeCli[100], endCli[200];
  
  cli.codigo = geraCodigo(gerarMin(), gerarMax());
  codCli = geraCodigo(gerarMin(), gerarMax()); 

  while(codCli == cli.codigo) {
    codCli = geraCodigo(gerarMin(), gerarMax());
  }

  cli.codigo = codCli;

  limparBuffer();
  
  printf(">> CADASTRAR UM CLIENTE \n\n");

  printf("Digite o nome do cliente: ");
  
  if(fgets(nomeCli, sizeof(nomeCli), stdin) == NULL) {
    printf("Erro ao ler o nome do cliente.");
  }
  
  strcpy(cli.nome, nomeCli);
  nomeCli[strcspn(nomeCli, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");
  
  if(fgets(endCli, sizeof(endCli), stdin) == NULL) {
    printf("Erro ao ler o endereço do cliente. ");
  }
  
  strcpy(cli.ender, endCli);
  endCli[strcspn(endCli, "\n")] = '\0';

  printf("Digite o telefone do cliente: ");
    
  if(scanf("%i", &telCli) != 1) {
    printf("Erro ao let o telefone do cliente. ");
    limparBuffer();
  }
  
  cli.telefone = telCli;

  limparBuffer();

  printf("\n");
  printf("O código do cliente é: %i \n", cli.codigo);
  printf("O nome do cliente é: %s \n", cli.nome);
  printf("O endereco do cliente é: %s \n", cli.ender);
  printf("O telefone do cliente é: %i\n", cli.telefone);

  printf("\n");
}

// estrutura funcionário
struct Tfuncionario {
  int codigo;
  char nome[100];
  int telefone;
  char cargo[80];
  float salario;
};
typedef struct Tfuncionario funcionario;

// função para cadastrar um funcionário
void cadFuncionario() {
  funcionario fun;

  fun.codigo = geraCodigo(gerarMin(), gerarMax());

  limparBuffer();

  printf(">> CADASTRAR UM FUNCIONÁRIO \n\n");

  printf("Digite o nome do funcionário: ");
  
  if(fgets(fun.nome, sizeof(fun.nome), stdin) == NULL) {
    printf("Erro ao ler o nome do funcionário. ");
  }
  
  fun.nome[strcspn(fun.nome, "\n")] = '\0';

  printf("Digite o telefone do funcionário: ");
  
  if(scanf("%i", &fun.telefone) != 1) {
    printf("Erro ao ler o telefone do usuário");
    limparBuffer();
  }

  limparBuffer();

  printf("Digite o cargo do funcionário: ");
  
  if(fgets(fun.cargo, sizeof(fun.cargo), stdin) == NULL) {
    printf("Erro ao ler o cargo do funcionário");
  }
  
  fun.cargo[strcspn(fun.cargo, "\n")] = '\0';

  printf("Digite o salário do funcionário: ");
  
  if(scanf("%f", &fun.salario) != 1) {
    printf("Erro ao ler o salário do funcionário.");
    limparBuffer();
  }

  limparBuffer();

  printf("\n");
  printf("O código do funcionário é: %i \n", fun.codigo);
  printf("O nome do funcionário é: %s \n", fun.nome);
  printf("O cargo do funcionário é: %s \n", fun.cargo);
  printf("O salário do funcionário é: R$ %.2f\n", fun.salario);

  printf("\n");
}

// estrutura quarto
struct Tquarto {
  int numero;
  int quantHosp;
  float diaria;
  char status[10];
};
typedef struct Tquarto quarto;

// função para cadastrar um quarto
void cadQuarto() {
  quarto quarto;
  int ocupado;

  limparBuffer();

  printf(">> CADASTRAR UM QUARTO \n\n");

  printf("Digite o número do quarto: ");
  
  if(scanf("%i", &quarto.numero) != 1) {
    printf("Erro ao ler o número do quarto.");
    limparBuffer();
  }

  printf("Digite a quantidade de hóspedes: ");
  
  if(scanf("%i", &quarto.quantHosp) != 1) {
    printf("Erro ao ler a quantidade de hóspedes.");
    limparBuffer();
  }

  printf("Digite o valor da diária: ");
  
  if(scanf("%f", &quarto.diaria) != 1) {
    printf("Erro ao ler o valor da diaria.");
    limparBuffer();
  }
  

  printf("O quarto está ocupado? (0 não, 1 sim) ");
  
  if(scanf("%i", &ocupado) != 1) {
    printf("Erro ao ler o status do quarto. ");
    limparBuffer();
  };
  

  if(ocupado != 0 && ocupado != 1) {
    printf("ERRO! Status do quarto inválido!");
  } else {
    if(ocupado == 0) {
      strcpy(quarto.status, "desocupado");
    } else {
      strcpy(quarto.status, "ocupado");
    }
  }

  limparBuffer();

  printf("\n");
  printf("O número do quarto é: %i \n", quarto.numero);
  printf("A quantidade de hóspedes do quarto é: %i \n", quarto.quantHosp);
  printf("O valor da diária do quarto é: %.2f \n", quarto.diaria);
  printf("O quarto está %s\n", quarto.status);

  printf("\n");
}

// função para gerar um mínimo aleatório para o intervalo do número do código entre 1000 e 9999
int gerarMin() {
  int min = rand() % (9999 - 1000 + 1) + 1000;

  return min; 
}

// função para gerar um máximo aleatório para o intervalo do número do código entre 1 000 000 e 9 999 999
long int gerarMax() {
  long int max = rand() % (9999999 - 1000000 + 1) + 1000000;

  return max; 
}

// função para gerar um código aleatório
int geraCodigo(int min, int max) {
  int codigo = rand() % (max - min + 1) + min;
  return 100;
}



