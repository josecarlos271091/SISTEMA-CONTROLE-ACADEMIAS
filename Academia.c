// Aluno: Jose Carlos
//Matricula: UC17100669

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"

/* 
Sintese:

Objetivo: Controlar as atividades desenvolvidas pelos frequentadores de uma rede de academias.

Entrada: Dados da Academia: Nome e endereco,
 
		->Para cada Frequentador:
			matricula, nome, cpf, peso, sexo, data de ingresso
			
			Funcionaliades especificas: 
			Cadastrar Frequentador: Tomando o devido cuidado de nao permitir recadastramento de funcionario existente.
			Alterar Frequentador: Alteracao/complementacao dos dados cadastrais com execao de matricula.
			Exlucusao: Sendo so possivel se ele nunca frequentou a academia (nenhuma serie de exercicios executada por ele). 
			
		->Para cada Serie:
			id,	descricao, duracao, calorias
			
			Funcionaliades especificas: 
			Cadastrar Serie: Tomando o devido cuidado de nao permitir recadastramento de serie existente.
			Alterar Serie: Alteracao/complementacao dos dados cadastrais com execao de id de Serie.
			Exlucusao: Sendo so possivel se ela nunca foi executada por nenhum frequentador. 
			
		->Para cada Atividade:
			matricula(do Frequentador), id(da Serie), data e hora em que foi iniciada a serie
			
			Funcionaliades especificas: 
			Cadastrar Atividade: Inclusao de uma nova atividade para um frequentador a traves da selecao entre as series existentes, 
								 nao e possivel repetir uma serie no mesmo dia, 
			Exlucusao: Sendo so possivel se ela nunca foi executada por nenhum frequentador. 

Saida: ->Relatorios
		R1: Listar todos os registros ja cadastrados ou pela chave primaria
		R2: Pesquisar frequentadores pelo nome(substring), em caso de varios nomes apresentar em ordenada alfabeticamente.
		R3: Mostrar os frequentadores que executaram pelo menos uma vez uma serie de exercicio
		R4: Dado um frequentador, informar todas as atividades desenvolvidas por ele na academia em datas (de ... ate...) (dia/mes/ano)
			para cada frequentador mostrar resumo da quantidade de tempo que ficou na academia e quantidade de calorias perdidas
		R5: Listar todos os frequentadores que utilizaram a academia em uma faixa de datas (de ... ate...) (dia/mes/ano),
			onde serao mostrados todos os dados cadastrados dos frequentadores em ordem alfabetica.
		R6: Pesquisar todos os frequentadores que nao frequentam a academia a uma quantidade de dias a ser fornecida pelo usuario		

*/

int main(void) {
	//Declaracoes
	int dia, mes, ano, hora, minutos, segundos;
	
	//Instrucoes
	
	//Apresentando tela inicial
	printf("\n\n\n\n\n\n\n\n\t\t\tBEM-VINDO AO SISTEMA DE CONTROLE DE ACADEMIAS DE GINASTICA V1.0.1 Final\t\t\t\n");
	obtemDataHoraAtual(&dia, &mes, &ano, &hora, &minutos, &segundos);
	printf("\n\n\t\t\t\t\tDATA: %02d/%02d/%d - HORA: %2.2d:%2.2d:%2.2d\t\t\t\n\n\n",dia , mes, ano, hora, minutos, segundos);
	printf("\t\t\tPressione qualquer tecla para continuar ............................");
	getch();
	system("cls");
	
	//Apresentando Menu Principal
	menuPrincipal();
	
	return 0;
}
