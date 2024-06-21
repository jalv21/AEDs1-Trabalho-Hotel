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

int bissexto(int ano) {
  if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
    return 1;
  } else {
    return 0;
  }
}

int diasnomes(int ano, int mes) {
  if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
    return 31;
  } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    return 30;
  } else if (mes == 2) {
    if (bissexto(ano)) {
        return 29;
    } else {
        return 28;
    }
  } else {
    return 0;
  }
}

int diasRef(int ano, int mes, int dia) {
  int dias = 0;

  for (int a = 0; a < ano; a++) {
      if (bissexto(a)) {
          dias += 366;
      } else {
          dias += 365;
      }
  }

  for (int m = 1; m < mes; m++) {
      dias += diasnomes(ano, m);
  }

  dias += dia;

  return dias;
}