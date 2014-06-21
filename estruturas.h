#ifndef _ESTRUTURAS_
#define _ESTRUTURAS_
#include <stdio.h>

typedef struct sEvento
{
	char* nome;
	int ano;
}*Evento, NodoEvento;

typedef struct sLEventos
{
	Evento evento;
	struct sLEventos * seg;
}*LEventos, NodoLEventos;

typedef struct sInformacaoPessoal
{
	char* tipo;
	int num;
}*InformacaoPessoal, NodoInformacaoPessoal;

typedef struct sLAtrSimples
{
	InformacaoPessoal info;
	struct sLAtrSimples * seg;
}*LAtrSimples, NodoLAtrSimples;

typedef struct sFilho
{
	char* nome;
	LAtrSimples atrfilho;
}*Filho, NodoFilho;

typedef struct sLFilhos
{
	Filho filho;
	struct sLFilhos * seg;
}*LFilhos, NodoLFilhos;

typedef struct sCasamento
{
	int idcasamento;
	int ano;
	char* conjuge;
	LAtrSimples atrconjuge;
	LFilhos filhos;
}*Casamento, NodoCasamento;

typedef struct sLCasamentos
{
	Casamento casamento;
	struct sLCasamentos * seg;
}*LCasamentos, NodoLCasamentos;

typedef struct sParente
{
	char* tipo;
	char* nome;
	LAtrSimples atrparente;
}*Parente, NodoParente;

typedef struct sLParentes
{
	Parente parente;
	struct sLParentes * seg;
}*LParentes, NodoLParentes;

typedef struct sDocumento
{
	char* tipo;
	char* path;
}*Documento, NodoDocumento;

typedef struct sLDocumentos
{
	Documento doc;
	struct sLDocumentos * seg;
}*LDocumentos, NodoLDocumentos;


typedef struct sAtrComplexos
{
	LParentes lparentes;
	LDocumentos ldocs;
}*AtrComplexos, NodoAtrComplexos;

typedef struct sPessoa
{
	char* nome;
	LAtrSimples simples;
	AtrComplexos complexos; 
	LEventos leventos; 
	LCasamentos lcasamentos;
}*Pessoa, NodoPessoa;


typedef struct sLPessoas
{
	Pessoa pessoa;
	struct sLPessoas * seg;
}*LPessoas, NodoLPessoas;


void imprimeGenealogia(LPessoas lista);
void imprimeLAtrSimples(LAtrSimples atr);
void imprimeLParentes(LParentes lista);
void imprimeAtrComplexos(AtrComplexos lista);
void imprimeLDocumentos(LDocumentos lista);
void imprimeLEventos(LEventos lista);
void imprimeLFilhos(LFilhos lista);
void imprimeLCasamentos(LCasamentos lista);
LPessoas consGenealogia(LPessoas lista, Pessoa p);
LAtrSimples consLAtrSimples(LAtrSimples lista, InformacaoPessoal informacao);
Pessoa criaPessoa(char* name, LAtrSimples atrs, AtrComplexos atrc, LEventos lev, LCasamentos lcas);
InformacaoPessoal criaInfoPessoal(char* type, int numero);
AtrComplexos criaAtrComplexos(LParentes lps, LDocumentos lds);
LParentes consLParentes(LParentes lista, Parente p);
Parente criaParente(char* type, char* name, LAtrSimples lsimples);
Documento criaDocumento(char* type, char* caminho);
LDocumentos consLDocumentos(LDocumentos lista, Documento documento);
Evento criaEvento(char* name, int num);
LEventos consLEventos(LEventos lista, Evento ev);
LCasamentos consLCasamentos(LCasamentos lista, Casamento casam);
Casamento criaCasamento(int year, int id, char* nome, LAtrSimples atrconj, LFilhos lfilhos);
LFilhos consLFilhos(LFilhos lista, Filho f);
Filho criaFilho(char* name, LAtrSimples atrf);
void criaHtmlIndex(LPessoas lpessoas);
void criaHtmlIndividuos(LPessoas lpessoas, FILE * index);
int buscaId(LAtrSimples lista);
void buscaDocumento(FILE* file, LDocumentos ldocs, char* type);
void buscaAtrSimples(FILE* file, LAtrSimples simples);
char* leFicheiro(char* path);
void buscaEventos(FILE* file,LEventos levs);
void buscaCasamentos(FILE* file,LCasamentos lcasam);
void buscaFilhos(FILE* file,LFilhos lf);
void buscaPais(FILE* file, LParentes lps);
void buscaAvos(FILE* file, LParentes lps);
int encontraAvo(LParentes lista);

#endif
