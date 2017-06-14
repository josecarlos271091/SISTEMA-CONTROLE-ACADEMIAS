#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define TAM_NOME 50
#define TAM_CPF 12
#define TAM_DESCRICAO 30

#ifndef INCLUIU_ESTRUTURAS
//Estruturas de Dados
typedef struct Frequentador
{
	int matricula;          // chave
	char nome[TAM_NOME];		
	char CPF[TAM_CPF];
    float peso;
	char sexo;
	//data ingresso em formato inteiro - aaaammdd
	int dataIngresso;
}Frequentador;

typedef struct Serie
{
	int id;			// chave
	char descricao[TAM_DESCRICAO];
	int duracao; //Duracao da serie em minutos
	float calorias;
}Serie;

typedef struct Atividade
{
	int matricula;		//id única do frequentador
	int id;			//id única da serie
	//Data e Hora que iniciou a serie separados em dataInicio (aaaammdd) - hora, minutos, segundos
	int dataInicio;
	int hora;
	int minutos;
	int segundos; 
}Atividade;
#define INCLUIU_ESTRUTURAS
#endif
