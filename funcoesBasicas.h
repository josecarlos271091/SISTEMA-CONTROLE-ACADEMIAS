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
