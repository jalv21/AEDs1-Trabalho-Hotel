/*
Este é o arquivo "Datas.c"

Descrição: Este é o arquivo contendo o código da biblioteca "Datas", que
implementa as principais funções que são utilizadas pelo programa principal no
"main.c" e as que são utilizadas na própria biblioteca para complementá-la

Funções:
int bissexto(int ano)
int diasnomes(int ano, int mes)
int diasRef(int ano, int mes, int dia)

Autor: João Alvaro Rodrigues Araujo
Data de início: 14 Jun. 2024
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int bissexto(int ano) {
  /*
  Esta é a função bissexto

  A função verifica se um ano é bissexto para então passar essa informação para outra função

  Parâmetros:
  int ano: O ano fornecido

  Retorno:
  tipo: int
  valores:
  1: verdadeiro
  0: falso
  */
  if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
    return 1;
  } else {
    return 0;
  }
}

int diasnomes(int ano, int mes) {
  /*
  Esta é a função diasnomes

  A função calcula quantos dias há em cada mês do ano

  Parâmetros:
  int ano: o ano fornecido
  int mes: o mes fornecido

  Retorno:
  tipo: int
  valores:
  31: caso o mês tenha 31 dias
  30: caso o mês tenha 30 dias
  29: fevereiro(bissexto)
  28: fevereiro(não bissexto)
  */
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
  /*
  Esta é a função diasRef

  A função utiliza a quantidade de anos e meses passados para calcular a quantidade de dias

  Parâmetros:
  int ano: o ano fornecido
  int mes: o mes fornecido
  int dia: o dia fornecido

  Retorno
  tipo: int
  valores: 
  dias: a quantidade de dias passados desde o dia de checkin
  */
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