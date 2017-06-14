#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "series.h"
#include "estruturas.h"
#include "biblioteca.h"
#include "funcoesBasicas.h"
#include "apresentaDadosAcademia.h"
#include "atividades.h"

#define MIN_ID 1
#define MAX_ID 99999
#define MIN_DURACAO 1
#define MAX_DURACAO 59
#define MIN_CALORIAS 100
#define MAX_CALORIAS 10000
#define NOME_ARQ "series.txt"
#define NOME_ARQ_ATIV "atividades.txt"

//	Objetivo: Ler os dados de uma serie.
//	Parâmetros: Endereço de momoria do nome do arquivo
//	Retorno: Nenhum.
void leSerie(char *nomeArq)
{
	FILE *arq;
	int flag = 0;
	Serie serie;
    
	//Obtendo e Validando ID serie
	
	serie.id = leValidaInt("Informe ID da Serie: ","Dados Invalidos!, Digite Novamente",MIN_ID,MAX_ID);
	flag = obtemNroSerie(serie.id, nomeArq);
	if(flag!=0)
	{
		printf("ID Existente .........");
		getch();
	}
	else
	{
		leValidaTexto("Informe Descricao da Serie: ","Dados Invalidos!, Digite Novamente ",serie.descricao,TAM_DESCRICAO);
		serie.duracao = leValidaInt("Informe Duracao da Serie em Minutos:","Dados Invalidos!, Digite novamente ",MIN_DURACAO,MAX_DURACAO);
		serie.calorias = leValidaFloat("Informe Qtde de calorias a serem perdidas: ","Dados Invalidos!, Digite Novamente ",MIN_CALORIAS, MAX_CALORIAS);
		
		//Gravando no Arquivo
		arq = fopen(nomeArq,"ab");
		if(arq!=NULL) {
			if(fwrite(&serie,sizeof(Serie),1,arq)==1) {
				printf("Dados salvos com sucesso.\n");
				getch();
			}else{
				printf("Erro ao gravar dados no arquivo.\n");
				getch();
			}
			system("cls");
			fclose(arq);
		}else{
			printf("\nNão foi possivel abrir o arquivo.\n");
			getch();
		}
		system("cls");	
	}
}

//	Objetivo: Verificar se um id é repetido.
//	Parâmetros: ID da serie e endereco de memoria do nome do arquivo.
//	Retorno:0 - nao existe, N - nro da serie
int obtemNroSerie(int id, char *nomeArq)
{
	FILE *arq;
	int cont = 0, flag =0;
	Serie serie;

	arq = fopen(nomeArq,"rb");
	if(arq != NULL) {
		while(!feof(arq)) {

			if(fread(&serie,sizeof(Serie),1,arq)==1){
				cont++;
				if(serie.id == id) {
					flag = cont;
					break;
				}
			}
		}
		fclose(arq);
	}
	return flag;
}

//	Objetivo: Apresentar os dados de todas as Series.
//	Parâmetros: Endereco de memoria do nome do arquivo.
//	Retorno: Nenhum.
void apresentaDadosSeries(char *nomeArq)
{
	FILE *arq;
	Serie serie;

	arq = fopen(nomeArq,"rb");
	if(arq!=NULL){
		printf("%-9.9s %-30.30s %-10.10s %-10.10s\n","ID","DESCRICAO","DURACAO","CALORIAS");
		while(!feof(arq)){
			if(fread(&serie,sizeof(Serie),1,arq)==1){
				printf("%-9d %-30.30s %-10d %-10.2f\n", serie.id, serie.descricao, serie.duracao, serie.calorias);
			}
		}
		getch();
		fclose(arq);
	}
}

//	Objetivo: Apresentar os dados das Series, a partir de um ID especifico.
//	Parâmetros: Endereco do nome do arquivo
//	Retorno: Nenhum.
void apresentaDadosSerieID(char *nomeArq)
{
	int id, flag;
	int nroSerie;
	Serie serie;

	system("cls");
	id = leValidaInt("Informe a ID da Serie a pesquisar: ","\nNao houve leitura!",MIN_ID,MAX_ID);
	nroSerie = obtemNroSerie(id, nomeArq);
	system("cls");
	if (nroSerie == 0){
		printf("Serie nao cadastrada\n");
	} else {
		serie = obtemDadosSerie(nroSerie, nomeArq, &flag);
		if (flag == 1 ){
			apresentaDadosAcademia();
			printf("%-9.9s %-30.30s %-10.10s %-10.10s\n","ID","DESCRICAO","DURACAO","CALORIAS");
			printf("%-9d %-30.30s %-10d %-10.2f\n", serie.id, serie.descricao, serie.duracao, serie.calorias);
		}
	}

	getch();
}

//  Objetivo: Alterar os dados de uma Serie
//  Parâmetros: Endereco de memoria do nome do arquivo.
//  Retorno: nenhum
void alteraDadosSerie(char *nomeArq)
{
    int id, numSerie, flag;
    char opcao;
    Serie serie;
    FILE *arq;


    system("cls");
    apresentaDadosSeries(nomeArq);
    id = leValidaInt("\nInforme ID da Serie: ", "ID INVALIDO!!", MIN_ID, MAX_ID);
    numSerie = obtemNroSerie(id,nomeArq);
    if(numSerie == 0){
        printf("Serie nao cadastrada...");
        getch();
        return;
    }else{
        system("cls");
        printf("\n Serie n%c %02d", 167, numSerie);
        serie = obtemDadosSerie(numSerie, nomeArq, &flag);
        if(flag == 1){
            printf("\nID SERIE: %d\n\t", serie.id);
            opcao = leValidaOpcao("Confirma a Serie <S/N> ? ", "ERRO", "SN");
            if (opcao == 'S')
			{
                system("cls");
                
                leValidaTexto("Informe o nova descricao: ", "Descricao Invalida", serie.descricao, TAM_DESCRICAO);
               	serie.duracao = leValidaInt("Informe nova Duracao: ","Dados Invalidos!, Digite Novamente ",MIN_DURACAO,MAX_DURACAO);
               	serie.calorias = leValidaFloat("Informe Qtde de calorias a perder: ","Dados Invalidos!, Digite Novamente ",MIN_CALORIAS,MAX_CALORIAS);
			
			//Gravando Nova Serie em arquivo
			gravaSerie(&serie, numSerie, nomeArq);
		    }
		}
	}
}

// Objetivo: Excluir uma Serie
// Parâmetros: Endereco ao nome do arquivo
// Retorno: Nenhum
void excluiSerie(char *nomeArq)
{
	int id, numSerie, flag, existeErro;
    char opcao;
    Serie serie;
    FILE *arq, *arqAux;
	
	system("cls");
    apresentaDadosSeries(nomeArq);
    id = leValidaInt("\nInforme o ID da Serie: ", "ID INVALIDO!!", MIN_ID, MAX_ID);
    numSerie = obtemNroSerie(id,nomeArq);
    if(numSerie == 0){
        printf("Serie nao cadastrada...");
    }else{
    	//Verificando se o Frequentador frequentou a academia
    	if(verificaSerieAtividade(id,NOME_ARQ_ATIV) != 0)
    	{
    		printf("Impossivel excluir Serie!, Atividades estao sendo executadas com essa Serie!\n");
    		getch();
    		return;
		}
        system("cls");
        printf("\n Serie n%c %02d", 167, numSerie);
        serie = obtemDadosSerie(numSerie, nomeArq, &flag);
        if(flag == 1)
		{
            printf("\n\tDESCRICAO: %s\n\tID: %d\n\t", serie.descricao, serie.id);
            opcao = leValidaOpcao("Confirma a Serie <S/N> ? ", "ERRO", "SN");
            if (opcao == 'S')
			{
                system("cls");
                existeErro = 0;
            	if((arq = abreArquivo(NOME_ARQ, "rb")) != NULL){
            		if((arqAux = abreArquivo("serieTemp.txt", "wb")) != NULL){
            			while(!feof(arq)){
            				if(fread(&serie, sizeof(Serie), 1, arq) == 1){
            					if (serie.id != id){
            						if(fwrite(&serie, sizeof(Serie), 1, arqAux) != 1){
            							printf("Erro ao gravar os dados no arquivo auxiliar.\n");
            							existeErro = 1;
            							break;
									}
								}
							}
						}
						fclose(arqAux);
					}else
						existeErro = 1;
					fclose(arq);
				}else
					existeErro = 1;          
            
	            if (existeErro == 1){
					printf("Não foi possivel remover o serie...\n");
				}else{
					if(remove(nomeArq) == 0){
						if(rename("serieTemp.txt", nomeArq) == 0){
							printf("Serie excluida com sucesso!\n");
						}else{
							printf("Erro ao renomear o arquivo\n");
						}
					}else
					{
						printf("Erro ao remover o arquivo\n");
					}
				}
			}
   	    }
    }
    getch();
}
// Objetivo :  Gravar o dado da serie no arquivo
// Parâmetros: Endereco da variavel serie, o numero da serie e o nome do arqivo
//Retorno :   Nenhum
void gravaSerie(Serie *serie,int numSerie, char *nomeArq)
{
	FILE *arq;
	arq=fopen(nomeArq, "r+b");
	if(arq!=NULL){
		if(fseek(arq, sizeof(Serie)*(numSerie-1), SEEK_SET)==0){
			if(fwrite(serie, sizeof(Serie),1,arq)==1){
				printf("Sucesso!");
			}else
				printf("Erro ao escrever os dados no arquivo!");
		}else
			printf("Erro ao posicionar os dados no arquivo!");
		fclose(arq);
	}
}

//  Objetivo: Dado um número da serie obter os seus dados
//  Parâmetros: número da serie, endereço de memória com o nome do arquivo
//			endereço do flag (0 - erro, 1 - correto)
//  Retorno: Estrutura com os dados da Serie
Serie obtemDadosSerie(int nroSerie, char *nomeArq, int *flag)
{
	FILE *arq;
	Serie serie;

	arq = fopen (nomeArq, "rb");

	if (arq == NULL){
		printf("Nao foi possivel abrir o arquivo");
		*flag = 0;
	} else {
		*flag = 1;
		if(fseek(arq, sizeof(Serie)*(nroSerie-1), SEEK_SET) != 0) {
			printf("erro a posicionar arquivo\n");
			*flag = 0;
			getch();
		} else {
			if (fread(&serie, sizeof(Serie), 1, arq)!=1){
				printf("erro ao ler a Serie\n");
				*flag = 0;
				getch();
			}
		}
		fclose(arq);
	}

	return serie;
}

