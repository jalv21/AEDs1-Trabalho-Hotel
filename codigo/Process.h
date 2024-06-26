/*
Este é o arquivo "Process.h"

Descrição: Este é o arquivo de header da biblioteca "Process", que declara as
funções devidamente construídas no código da biblioteca "Process.c" para serem
usadas pelo arquivo principal ao incluir este arquivo com #include "Process.h"

Funções:
void cadCliente()
void cadFuncionario()
void cadQuarto()
void cadEstadia()

Autor: João Alvaro Rodrigues Araujo
Data de início: 14 Jun. 2024
*/
#include <stdio.h>
#ifndef PROCESS_H
#define PROCESS_H

void cadCliente(FILE *f);
void cadFuncionario(FILE *f);
void cadQuarto(FILE *f);
void cadEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua);
void baixaEstadia(FILE *f_est, FILE *f_cli, FILE *f_qua);
void pesquisa(FILE *f_cli, FILE *f_fun);
void buscaEstadia(FILE *f_est, FILE *f_qua, FILE *f_cli);
void calculaPts(FILE *f_est, FILE *f_cli);

#endif
