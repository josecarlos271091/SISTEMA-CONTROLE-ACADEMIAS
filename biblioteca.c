#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"

// Objetivo: Abrir/Criar um arquivo
// Parâmetros: Endereco de memoria com o nome do arquivo, e o modo de abertura
// Retorno: Endereco de memoria onde localiza a stream ou NULL(em caso de erro)
FILE* abreArquivo(char *nomeArq, char *modo)
{
	FILE *arq;
	arq = fopen(nomeArq, modo);
	if(arq == NULL){
		printf("Nao foi possivel abrir o arquivo '%s' no modo %s\n", nomeArq, modo);
		getch();
		system("cls");
	}
	return arq;
}

//	Objetivo: Verificar se existe um arquivo binario.
//	Parâmetros: Nome do arquivo a ser procurado.
//	Retorno: 0 - nao existe, 1 - existe.
int verificaArquivoExistente(char *nomeArq)
{
	FILE *arq;
	int flag = 0;

	arq = fopen(nomeArq,"rb");
	if(arq!=NULL){
		flag = 1;
		fclose(arq);
	}else{
		flag = 0;
	}
	
	return flag;
}

/*      
Objetivo: Efetua a validação de uma data a partir das informações do dia mes e ano (com seculo) 
Parâmetros: dia, mes e ano                               
  Retorno   :                                              
            1 - data valida                                
            0 - data invalida                             
*/ 
int validaData(int dia, int mes, int ano)
{
int retorno=1;    
    if(ano<0 || mes<1 || mes >12 || dia >31)
       return 0;          
    switch(mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno =0;
            break;
       case 2:
            printf(" %d\n",(ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0));
            if((ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0))
            {
               if(dia >29)
                  retorno = 0;
            }      
            else
            {
               if(dia >28)
                  retorno =0;                                      
            }
            break;      
    }      
    return retorno;
}

/*                           
Objetivo : Obtem a data e hora atual do sistema        
Parâmetros:                                             
            dia, mes,ano, hora, minutos, segundos        
Retorno   : Nenhum                                       
*/ 
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora, int *minutos, int *segundos)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
   *hora     = dataAtual->tm_hour;
   *minutos  = dataAtual->tm_min;
   *segundos = dataAtual->tm_sec;
}
/*                           
Objetivo : Obtem a data atual do sistema        
Parâmetros: dia, mes,ano,         
Retorno   : Nenhum                                      
*/ 
void obtemDataAtual(int *dia, int * mes, int *ano)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
}

// Objetico: transforma dia,mes,ano em uma data inteiro
// Parâmetros: dia,mes,ano
// Retorno : data em inteiro (aaaammdd)
int transformaDataInt(int dia,int mes,int ano)
{
	return ano *10000+mes*100+dia;
}
                            
//Objetivo : Resta uma quantidade de dias a uma data  
//Parâmetros: dia, mes, ano e qtde de dias a restar           
//Retorno   : 1 - ok 0 - erro                                      
int restaDiasData(int *dia, int *mes, int *ano,int qtdeDias)
{
struct tm time_check;

    
    if(*ano < 1970 || *ano >2037)
       return 0;
       
    /* carrega a data para a estrutura time_check do tipo tm */
    time_check.tm_year = *ano - 1900;
    time_check.tm_mon  = *mes - 1;
    time_check.tm_mday = *dia-qtdeDias;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  chama  mktime para criar uma data validando-a */
    if (mktime(&time_check) == -1)
    {
       return 0; // data invalida
    }
    // verifica se data criada é igual a data de entrada 
    else 
    {
       *ano = time_check.tm_year +1900;
       *mes = time_check.tm_mon + 1;
       *dia = time_check.tm_mday;
       return 1; // data valida
    }  
}

//Objetivo: Ler e validar Data em string dd/mm/aaaa e retornar data em formato int aaaammdd
//Parametros: endereco da string mensagem
//Retorno: data em formato aaaammdd
int leValidaData(char *msg)
{
	int dataInt, dia, mes, ano, ret=0;
	
	do
	{
		printf(msg);
		fflush(stdin);
		ret = scanf("%d/%d/%d", &dia, &mes, &ano);
		fflush(stdin);
		
		if(ret != 3 || validaData(dia,mes,ano) == 0)
		{
			printf("Data Invalida!\n");
			getch();
			system("cls");	
		}
	dataInt = transformaDataInt(dia,mes,ano);
	}while(ret != 3 || validaData(dia,mes,ano) == 0);
	
	return dataInt;
}

// Objetico: transforma uma data em inteiro em dia,mes,ano 
// Parâmetros: data em inteiro, endereço de meória do dia, mes e nao
// Retorno :nenhum
void transformaIntData(int dataInt, int *dia,int *mes,int *ano)
{

    *ano= dataInt/10000;
    *mes= (dataInt%10000)/100;
    *dia= dataInt%100;
}

/*
Descricao : Tira todos os brancos a esquerda de uma string 
Parâmetros: string                                          
Retorno   : Nenhum                                          
*/ 
void tiraTodosBrEsq(char *str)
{
char *pStr;    
   pStr = str;
   while(*pStr == ' ' && *pStr != '\0')
      pStr++;
   strcpy(str,pStr);   
}    

/*
Descricao : Tira todos os brancos a direita de uma string 
Parâmetros: string                                          
Retorno   : Nenhum                                          
*/ 
void tiraTodosBrDir(char *str)
{
char *pStr; 
   if(*str == '\0')
      return;   
   pStr = str+strlen(str)-1;
   while(*pStr == ' ')
      pStr--;
   *(pStr+1) = '\0';
}

/**************************************************************
*  Nome      : validaCPF                                      *  
*  Descricao : Valida um CPF                                  *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : 1 - cpf válido, 0 - cpf inválido               * 
**************************************************************/ 
int validaCPF (char *cpf)
	{
       // cpfs inválidos        
       char *cpfInval[] = {"11111111111",
                         "22222222222",
                         "33333333333",
                         "44444444444",
                         "55555555555",
                         "66666666666",
                         "77777777777",
                         "88888888888",
                         "99999999999"}; 
		
		int cont,retorno =1,aux2,dig[11],soma=0,digVeri[2];
		
		if(strlen(cpf) != 11)
		   return 0;
		 
         // verifica se cpf so contem nros iguais  
	     for(cont=0;cont<9;cont++)
         {
               if(strcmp(cpfInval[cont],cpf)==0)
               {
                  retorno =0;
                  break;
               }
         } 
         
         if(retorno ==0)
            return retorno;
          
         // transforma os caracteres do cpf em números     
         for(cont=0;cont<strlen(cpf);cont++)
         {
                dig[cont] = cpf[cont] - '0';
         }
         
         // obtem o primeiro digito verificador
         aux2=10;
         for(cont=0;cont<9;cont++,aux2--)
         {
            soma+= dig[cont] * aux2;
         }
         digVeri[0]=soma % 11;
         digVeri[0]= digVeri[0]<2 ? 0 : 11-digVeri[0];
         
         // obtem o segundo digito verificador
         soma=0;
         aux2=11;
         for(cont=0;cont<10;cont++,aux2--)
         {
               if(cont==9)
                  soma+= digVeri[0] * aux2;
               else
                  soma+= dig[cont] * aux2;
         }
         digVeri[1]=soma % 11;
         digVeri[1]= digVeri[1]<2 ? 0 : 11-digVeri[1];
         if(digVeri[0]!=dig[9] || digVeri[1]!=dig[10])
         {
               retorno =0;               
         }
         return retorno;
}
/**************************************************************
*  Nome      : formataCPF                                     *  
*  Descricao : Formata um CPF                                 *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : endereço de memória onde comeca a string       * 
*               com CPF formatado ou NULL                     *
**************************************************************/ 
char * formataCPF (char *cpf)
{
static char cpfFormatado[15];
   if(validaCPF(cpf) == 0)
      return NULL;
   else
   {
        sprintf(cpfFormatado,"%3.3s.%3.3s.%3.3s-%2.2s",
            cpf,cpf+3,cpf+6,cpf+9);
        return cpfFormatado;    
   }   
    
}

// Objetivo : compara duas strings ignorando case         
//Parâmetros: duas strings                                 
//Retorno   : 0, >0 ou < 0
int strIncmp(char *str1, char *str2,int tam)
{
char*pStr1,*pStr2;
int retorno=0;
   pStr1 = (char*) malloc(sizeof(char) * (tam+1));
   if(pStr1 != NULL)
   {
        strncpy(pStr1,str1,tam);
        pStr1[tam] = '\0';
        strUpper(pStr1);
        pStr2 = (char*) malloc(sizeof(char) * (tam+1));
        if(pStr2 != NULL)
        {
           strncpy(pStr2,str2,tam);
           pStr1[tam] = '\0';
           strUpper(pStr2);
           retorno = strncmp(pStr1,pStr2,tam);
           free(pStr1);
           free(pStr2);
        }  
        else
        {
            free(pStr1);
        }     
   }  
   return retorno;  
} 


// Descricao : compara duas strings ignorando case         
// Parâmetros: duas strings                                 
//Retorno   :  endereço foi encontrada a string ou NULL      
char * strIstr(char *str1, char *str2)
{
char*pStr1,*pStr2;
char *retorno=NULL;
   pStr1 = (char*) malloc(sizeof(char) * (strlen(str1)+1));
   if(pStr1 != NULL)
   {
        strcpy(pStr1,str1);
        strUpper(pStr1);
        pStr2 = (char*) malloc(sizeof(char) * (strlen(str2)+1));
        if(pStr2 != NULL)
        {
           strcpy(pStr2,str2);
           strUpper(pStr2);
           retorno = strstr(pStr1,pStr2);
           free(pStr1);
           free(pStr2);
        }  
        else
        {
            free(pStr1);
        }     
   }  
   return retorno;  
} 

// Objetivo   : Converte uma string para maiuscula
// Parâmetros : str - endereço de memória da string a ser convertida para maiuscul
// Retorno   :  void
void strUpper(char * str)
{
int i;
  for (i=0;i<strlen(str);i++)
  {
      str[i] = (char) toupper(str[i]);
  }        
}

