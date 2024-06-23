/*  
Este é o arquivo "Datas.h"

Descrição: Este é o arquivo de header da biblioteca "Datas", que declara as funções devidamente construídas no código da biblioteca "Datas.c" para serem usadas pelo arquivo principal ao incluir este arquivo com #include "Datas.h"

Funções: 
int bissexto(int ano)
int diasnomes(int ano, int mes)
int diasRef(int ano, int mes, int dia)

Autor: João Alvaro Rodrigues Araujo
Data de início: 14 Jun. 2024
*/
#include <stdio.h>
#ifndef DATAS_H
#define DATAS_H

int bissexto(int ano);
int diasnomes(int ano, int mes);
int diasRef(int ano, int mes, int dia);

#endif 

