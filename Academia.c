// Aluno: Jose Carlos
//Matricula: UC17100669

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define TAM_NOME_ACADEMIA 50
#define TAM_ENDERECO 50
#define TAM_NOME 50
#define TAM_CPF 15
#define TAM_SEXO 10
#define TAM_DESCRICAO 50

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
		R1: Listar todos os registros ja cadastrados
		R2: Pesquisar frequentadores pelo nome(substring), em caso de varios nomes apresentar em ordenada alfabeticamente.
		R3: Mostrar os frequentadores que executaram pelo menos uma vez uma serie de exercicio
		R4: Dado um frequentador, informar todas as atividades desenvolvidas por ele na academia em datas (de ... ate...) (dia/mes/ano)
			para cada frequentador mostrar resumo da quantidade de tempo que ficou na academia e quantidade de calorias perdidas
		R5: Listar todos os frequentadores que utilizaram a academia em uma faixa de datas (de ... ate...) (dia/mes/ano),
			onde serao mostrados todos os dados cadastrados dos frequentadores em ordem alfabetica.
		R6: Pesquisar todos os frequentadores que nao frequentam a academia a uma quantidade de dias a ser fornecida pelo usuario		

*/

//Estruturas de Dados
typedef struct Frequentador
{
	int matricula;          // chave
	char nome[TAM_NOME];		
	char CPF[TAM_CPF];
    float peso;
	char sexo[TAM_SEXO];
	int dataIngresso; 
}Frequentador;

typedef struct Serie
{
	int id;			// chave
	char descricao[TAM_DESCRICAO];
	int duracao;
	float calorias;
}Serie;

typedef struct Atividade
{
	int matricula;		//id única do frequentador
	int id;			//id única da serie
	int dataSerie;
}Atividade;

  
//Prototipos funcoes basicas
int leInt(char *msn) ;
int leValidaInt(char *msn, char *msnErro, int valorMin, int valorMax);
float leFloat(char *msn);
float leValidaFloat(char *msn, char *msnErro, float valorMin, float valorMax) ;
void leValidaTexto(char *msn, char *msnErro, char *texto, int tam);
char leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas);
void strlower(char *str);
void strupper(char *str);
int verificaRepetido(int *valores, int posicao);
void tiraTerminador(char *texto);
void tiraBrEsq(char *str);

//prototipos funcoes especificas
void submenuFrequentador(char *nomeAcademia, char *enderecoAcademia);
void submenuSerie(char *nomeAcademia, char *enderecoAcademia);
void submenuAtividade(char *nomeAcademia, char *enderecoAcademia);

int main(void) 
{
	//Declarações
	char nomeAcademia[TAM_NOME_ACADEMIA], enderecoAcademia[TAM_ENDERECO], opcao;
	
	//Instruções
	
	//Apresentando tela inicial
	printf("\n\n\n\n\n\n\t\t\tBEM-VINDO AO SISTEMA DE CONTROLE DE ACADEMIAS DE GINASTICA V0.1 beta\t\t\t\n");
	printf("\n\n\t\t\t\t\tDATA: %s - HORA:%s\t\t\t\n\n\n",__DATE__,__TIME__);
	printf("\t\t\tPressione qualquer tecla para continuar ............................");
	getch();
	system("cls");
	
	//Solicitando Nome e Endereco da Academia
	leValidaTexto("Hola!, Por Favor Informe o Nome da Academia: ","Dados Invalidos!, Digite corretamente!",nomeAcademia,TAM_NOME_ACADEMIA);
	leValidaTexto("Certo!, Agora Por Favor Informe o Endereco: ","Dados Invalidos!, Digite corretamente!",enderecoAcademia,TAM_ENDERECO);
	system("cls");
	
	
	//Menu principal funcionalidades
	do
	{
		printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
		printf("MENU PRINCIPAL:\n\n");
		opcao = leValidaOpcao("[F]->Frequentador\n[S]->Serie\n[A]->Atividade\n[E]->Encerrar o programa\nOpcao desejada: ","\nOpcao invalida!","FSAE");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'F':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				submenuFrequentador(nomeAcademia,enderecoAcademia);
				getch();
				system("cls");
			break;
			
			case 'S':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				submenuSerie(nomeAcademia,enderecoAcademia);
				getch();
				system("cls");
			break;
			
			case 'A':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				submenuAtividade(nomeAcademia,enderecoAcademia);
				getch();
				system("cls");
			break;
			
			case 'E':
				exit(0);
			break;	
		}
	}while(opcao!='E');
	 	
	getch();
	
	return 0;
}

//Objetivo: Submenu para frequentador
//Parametros: void
//Retorno: void
void submenuFrequentador(char *nomeAcademia, char *enderecoAcademia)
{
	char opcao;
	do
	{
		printf("MENU FREQUENTADOR:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Frequentador\n[A]->Alterar Frequentador\n[E]->Excluir Frequentador\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CAER");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'C':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("CADASTRAR");
				getch();
				system("cls");
			break;
			
			case 'A':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("ALTERAR");
				getch();
				system("cls");
			break;
			
			case 'E':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("EXCLUIR");
				getch();
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

//Objetivo: Submenu para Serie
//Parametros: void
//Retorno: void
void submenuSerie(char *nomeAcademia, char *enderecoAcademia)
{
	char opcao;
	do
	{
		printf("MENU SERIE:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Serie\n[A]->Alterar Serie\n[E]->Excluir Serie\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CAER");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'C':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("CADASTRAR");
				getch();
				system("cls");
			break;
			
			case 'A':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("ALTERAR");
				getch();
				system("cls");
			break;
			
			case 'E':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("EXCLUIR");
				getch();
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

//Objetivo: Submenu para Atividade
//Parametros: void
//Retorno: void
void submenuAtividade(char *nomeAcademia, char *enderecoAcademia)
{
	char opcao;
	do
	{
		printf("MENU ATIVIDADE:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Atividade\n[E]->Excluir Atividade\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CER");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'C':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("CADASTRAR");
				getch();
				system("cls");
			break;
			
			case 'E':
				printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
				printf("EXCLUIR");
				getch();
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

// Objetivo: Le numero inteiro
// Parâmetros: endereco de memoria  da string  mensagem 
// Retorna: numero inteiro
int leInt(char *msn) 
{
	int ret = 0,valor;

	do
	{
		printf(msn);
		fflush(stdin);
		ret = scanf("%d", &valor);
		fflush(stdin);
		
		if(ret == 0)
		{
			printf("Erro ao ler o numero.\n");
			getch();
			system("cls");	
		}		
		
	}while(ret == 0);
    return valor; 	

}

// Objetivo: Le e validar numero inteiro
// Parâmetros: endereco de memoria  da string  mensagem e mensagem de erro
//              valor minimo e valor maximo.
// Retorna: numero inteiro
int leValidaInt(char *msn, char *msnErro, int valorMin, int valorMax) 
{
    int valor;
	
	do
	{
	
		valor =leInt(msn);
		if(valor < valorMin || valor > valorMax)
		{
			printf(msnErro);
			getch();
			system("cls");	
		}
	
	}while(valor < valorMin || valor > valorMax);
    return valor;

}

// Objetivo: Le e numero float
// Parâmetros: endereco de memoria  da string  mensagem
// Retorna: numero real
float leFloat(char *msn) 
{
    float valor;
	int ret = 0;

	do
	{
		printf(msn);
		fflush(stdin);
		ret = scanf("%f", &valor);
		fflush(stdin);
		
		if(ret == 0)
		{
			printf("Erro ao ler o numero.\n");
			getch();
			system("cls");	
		}		
		
	}while(ret == 0);
	return valor;

}

// Objetivo: Le e validar numero float
// Parâmetros: endereco de memoria  da string  mensagem e mensagem de erro valor minimo e valor maximo.
// Retorna: numero real
float leValidaFloat(char *msn, char *msnErro, float valorMin, float valorMax) 
{
    float valor;
	do
	{
	
		valor = leFloat(msn);	
		if(valor < valorMin || valor > valorMax)
		{
			printf(msnErro);
			getch();
			system("cls");	
		}
	
	}while(valor < valorMin || valor > valorMax);
    return valor; 
}

// Objetivo: Le e validar um texto
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e do texto quantidade de caracteres a serem lidos 
// Retorna: nenhum
void leValidaTexto(char *msn, char *msnErro, char *texto, int tam)
{
	do
	{
	
		printf(msn);
		fflush(stdin);
		fgets(texto, tam, stdin);
		fflush(stdin);
		
		if(texto[strlen(texto)-1] == '\n')
     	{
	      	texto[strlen(texto)-1] = '\0';
    	}
		system("cls");

		if(strlen(texto) ==0)
		{
			printf(msnErro);
			getch();
			system("cls");
		}
		
	}while(strlen(texto) ==0);
	
}

// Objetivo: Ler uma opcao 
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e das opcoes validas
// Retorna: opcao valida
char leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas)
{
	char opcao;
    do
	{
		printf(msn);
		fflush(stdin);
	    opcao = toupper(getch());
		fflush(stdin);
		system("cls");

		if(strchr(opcoesValidas,opcao)==NULL)
		{
			printf(msnErro);
			getch();
			system("cls");
		}
		
	}while(strchr(opcoesValidas,opcao)==NULL);    
	return opcao;
}

//Objetivo: Transforma String em minuscula..
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strlower(char *str)
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = tolower(str[cont]);
}

//Objetivo: Transforma String em Maiuscula.
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strupper(char *str)
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = toupper(str[cont]);
}

//Objetivo: Verificar se existe numero repetido em um vetor.
//Parametro: Referencia ao vetor e a posicao que deve ser verificado 
//Retorno: 0 para se nao existe e 1 para se existe numero repetido
int verificaRepetido(int *valores, int posicao)
{
	int cont,flag=0;
	for(cont=0;cont<posicao;cont++)
	{
		if(valores[posicao]==valores[cont])
		{
			printf("Valor Inserido ja existe no sistema ...\n");
			flag=1;
			break;
		}
	}
	return flag;
}

// Objetivo: Tirar o \n de uma string
// Parâmetros: endereco de memoria  da string  texto
// Retorna: Nada
void tiraTerminador(char *texto)
{

	if(texto[strlen(texto)-1] == '\n')
	{
		texto[strlen(texto)-1] = '\0';
	}
		
}

// Objetivo: Tira todos os brancos a esquerda de uma string 
// Parâmetros: endereço de memória da string a ser modificada
// Retorno: nenhum
void tiraBrEsq(char *str)
{
	char *pStr;    
    pStr = str;
    while(*pStr == ' ' && *pStr != '\0')
        pStr++;
    strcpy(str,pStr);   
}
