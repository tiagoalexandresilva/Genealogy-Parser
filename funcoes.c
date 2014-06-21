#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void imprimeGenealogia(LPessoas lista)
{
	printf("\n  IMPRESSAO DA GENEALOGIA\n");
	printf("============================\n");
	if(lista)
	{
		while(lista)
		{
				printf(">>>>%s<<<<\n",lista->pessoa->nome);
				imprimeLAtrSimples(lista->pessoa->simples);
				imprimeAtrComplexos(lista->pessoa->complexos);
				imprimeLEventos(lista->pessoa->leventos);
				imprimeLCasamentos(lista->pessoa->lcasamentos);
				printf("-------------------------\n");
				lista = lista->seg;
		}
	}
	else{ printf("VAZIO!\n"); }
}

void imprimeAtrComplexos(AtrComplexos lista)
{
		imprimeLParentes(lista->lparentes);
		imprimeLDocumentos(lista->ldocs);
}

void imprimeLParentes(LParentes lista)
{
	printf("--->PARENTES\n");
	if(lista)
	{
		while(lista)
		{
				printf("%s: %s\n",lista->parente->tipo,lista->parente->nome);
				imprimeLAtrSimples(lista->parente->atrparente);
				lista = lista->seg;
		}
	}
	else{ printf("PARENTES VAZIOS!\n"); }
}

void imprimeLCasamentos(LCasamentos lista)
{
	printf("--->CASAMENTOS\n");
	if(lista)
	{
		while(lista)
		{
				printf("Nome conjuge: %s\n",lista->casamento->conjuge);
				imprimeLAtrSimples(lista->casamento->atrconjuge);
				printf("Id Casamento: %d\n",lista->casamento->idcasamento);
				printf("Ano Casamento: %d\n",lista->casamento->ano);	
				imprimeLFilhos(lista->casamento->filhos);
				printf("<!><!><!><!>\n");	
				lista = lista->seg;
		}
	}
	else{ printf("CASAMENTOS VAZIOS!\n"); }
}

void imprimeLFilhos(LFilhos lista)
{
	printf(">FILHOS:\n");
	if(lista)
	{
		while(lista)
		{
				printf("Nome Filho: %s\n",lista->filho->nome);
				imprimeLAtrSimples(lista->filho->atrfilho);	
				lista = lista->seg;
		}
	}
	else{ printf("FILHOS VAZIOS!\n"); }
}	


void imprimeLDocumentos(LDocumentos lista)
{
	printf("--->DOCUMENTOS\n");
	if(lista)
	{
		while(lista)
		{
				printf("%s: %s\n",lista->doc->tipo,lista->doc->path);
				lista = lista->seg;
		}
	}
	else{ printf("DOCUMENTOS VAZIOS!\n"); }
}


void imprimeLAtrSimples(LAtrSimples lista)
{
	if(lista)
	{
		while(lista)
		{
			printf("%s: %d\n",lista->info->tipo,lista->info->num);
			lista = lista->seg;
		}
	}
	else{ printf("ATRSIMPLES VAZIOS\n"); }
}

void imprimeLEventos(LEventos lista)
{
	printf("--->EVENTOS\n");
	if(lista)
	{
		while(lista)
		{
			printf("%s: %d\n",lista->evento->nome,lista->evento->ano);
			lista = lista->seg;
		}
	}
	else{ printf("EVENTOS VAZIOS\n"); }
}

LPessoas consGenealogia(LPessoas lista, Pessoa p)
{
	LPessoas res;
	
	res = (LPessoas)malloc(sizeof(NodoLPessoas));
	
	if(!lista)
	{
			res->pessoa = p;
			res->seg = NULL;
	}
	else{
		res->pessoa	= p;
		res->seg = lista;
	}
	
	return res;
}

Pessoa criaPessoa(char* name, LAtrSimples atrs, AtrComplexos atrc, LEventos lev, LCasamentos lcas)
{
	Pessoa res;
	
	res = (Pessoa)malloc(sizeof(NodoPessoa));
	res->nome = strdup(name);
	res->simples = atrs;
	res->complexos = atrc; 
    res->leventos = lev; 
    res->lcasamentos = lcas;
    
    return res;
}

LAtrSimples consLAtrSimples(LAtrSimples lista, InformacaoPessoal informacao)
{
	LAtrSimples res;
	
	res = (LAtrSimples)malloc(sizeof(NodoLAtrSimples));
	
	if(!lista)
	{
			res->info = informacao;
			res->seg = NULL;
	}
	else{
		res->info = informacao;
		res->seg = lista;
	}
	
	return res;
}

InformacaoPessoal criaInfoPessoal(char* type, int numero)
{
	InformacaoPessoal res;
	
	res = (InformacaoPessoal)malloc(sizeof(NodoInformacaoPessoal));
	res->tipo = strdup(type);
	res->num = numero;
	
	return res;
}


AtrComplexos criaAtrComplexos(LParentes lps, LDocumentos lds)
{
	AtrComplexos res;
	
	res = (AtrComplexos)malloc(sizeof(NodoAtrComplexos));
	res->lparentes = lps;
	res->ldocs = lds;
    
    return res;
}

LParentes consLParentes(LParentes lista, Parente p)
{
	LParentes res;
	
	res = (LParentes)malloc(sizeof(NodoLParentes));
	
	if(!lista)
	{
			res->parente = p;
			res->seg = NULL;
	}
	else{
		res->parente = p;
		res->seg = lista;
	}
	
	return res;
}


Parente criaParente(char* type, char* name, LAtrSimples lsimples)
{
	Parente res;
	
	res = (Parente)malloc(sizeof(NodoParente));
	res->nome = strdup(name);
	res->tipo = strdup(type);
	res->atrparente = lsimples;
    
    return res;
}

Documento criaDocumento(char* type, char* caminho)
{
	Documento res;
	
	res = (Documento)malloc(sizeof(NodoDocumento));
	res->path = strdup(caminho);
	res->tipo = strdup(type);
    
    return res;
}

LDocumentos consLDocumentos(LDocumentos lista, Documento documento)
{
	LDocumentos res;
	
	res = (LDocumentos)malloc(sizeof(NodoLDocumentos));
	
	if(!lista)
	{
			res->doc = documento;
			res->seg = NULL;
	}
	else{
		res->doc = documento;
		res->seg = lista;
	}
	
	return res;
}

Evento criaEvento(char* name, int num)
{
	Evento res;
	
	res = (Evento)malloc(sizeof(NodoEvento));
	res->nome = strdup(name);
	res->ano = num;
    
    return res;
}

LEventos consLEventos(LEventos lista, Evento ev)
{
	LEventos res;
	
	res = (LEventos)malloc(sizeof(NodoLEventos));
	
	if(!lista)
	{
			res->evento = ev;
			res->seg = NULL;
	}
	else{
		res->evento = ev;
		res->seg = lista;
	}
	
	return res;
}

LCasamentos consLCasamentos(LCasamentos lista, Casamento casam)
{
	LCasamentos res;
	
	res = (LCasamentos)malloc(sizeof(NodoLCasamentos));
	
	if(!lista)
	{
			res->casamento = casam;
			res->seg = NULL;
	}
	else{
		res->casamento = casam;
		res->seg = lista;
	}
	
	return res;
}

Casamento criaCasamento(int year, int id, char* nome, LAtrSimples atrconj, LFilhos lfilhos)
{
	Casamento res;
	
	res = (Casamento)malloc(sizeof(NodoCasamento));
	res->conjuge = strdup(nome);
	res->ano = year;
	res->idcasamento = id;
	res->atrconjuge = atrconj;
	res->filhos = lfilhos;
    
    return res;
}

LFilhos consLFilhos(LFilhos lista, Filho f)
{
	LFilhos res;
	
	res = (LFilhos)malloc(sizeof(NodoLFilhos));
	
	if(!lista)
	{
			res->filho = f;
			res->seg = NULL;
	}
	else{
		res->filho = f;
		res->seg = lista;
	}
	
	return res;
}

Filho criaFilho(char* name, LAtrSimples atrf)
{
	Filho res;
	
	res = (Filho)malloc(sizeof(NodoFilho));
	res->nome = strdup(name);
	res->atrfilho = atrf;
    
    return res;
}


void criaHtmlIndex(LPessoas lpessoas)
{
	FILE* index = fopen("Index.html","w");
	
	if(index)
	{
		fprintf(index,"<html>\n<head>\n<title>NGEN Index</title>\n<link href='http://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700' rel='stylesheet' type='text/css'><link href='http://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,400,700,600,300' rel='stylesheet' type='text/css'><link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\"><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n</head>\n<body>\n");
		fprintf(index,"<div id=\"wrapper\">\n");
		fprintf(index,"<br><h1>NGEN Index</h1><hr>\n");
		fprintf(index,"<br><h2>Elementos familiares</h2>\n");
		fprintf(index,"<ul>\n");
		criaHtmlIndividuos(lpessoas,index);
		fprintf(index,"</ul>\n");
		fprintf(index,"</div>\n");
		fprintf(index,"</body></html>\n");
		fclose(index);		
	}
	else{ printf("Erro ao criar html de Index!\n"); }
}


void criaHtmlIndividuos(LPessoas lpessoas, FILE * index)
{
	char nomehtml[1024];
	LPessoas aux = lpessoas;
	int i = 1, id;
	FILE* file;
	
	while(aux)
	{
		id = buscaId(aux->pessoa->simples);
		sprintf(nomehtml, "Individuo %d.html",id);
		file = fopen(nomehtml,"w");
		if(file)
		{
			fprintf(file,"<html>\n<head>\n<title>NGEN - %s</title>\n<link href='http://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700' rel='stylesheet' type='text/css'><link href='http://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,400,700,600,300' rel='stylesheet' type='text/css'><link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\"><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n</head><body>\n",aux->pessoa->nome);
			fprintf(file,"<div id=\"wrapper\">\n");
			fprintf(index,"<p><li><a href=\"%s\" target=\"_blank\">%s</a></li></p>\n",nomehtml,aux->pessoa->nome);
			fprintf(file,"<br><h1>%s</h1><hr>\n",aux->pessoa->nome);
			buscaDocumento(file,aux->pessoa->complexos->ldocs,"foto");
			buscaAtrSimples(file,aux->pessoa->simples);
			buscaDocumento(file,aux->pessoa->complexos->ldocs,"hist");
			buscaEventos(file,aux->pessoa->leventos);
			buscaCasamentos(file,aux->pessoa->lcasamentos);
			if(aux->pessoa->complexos->lparentes)
			{
				fprintf(file,"<h2>Parentescos</h2>\n");
				buscaPais(file, aux->pessoa->complexos->lparentes);
				buscaAvos(file, aux->pessoa->complexos->lparentes);
			}
			fprintf(file,"<div style=\"text-align:center;\"><a href=\"Index.html\"><u>Voltar ao Index</u></a></div>\n");
			fprintf(file,"</div>\n");
			fprintf(file,"</body></html>\n");
			fclose(file);
		}else{ printf("Erro ao criar html do Individuo %d!\n",i); }
		i++;
		aux = aux->seg;
	}
}


int buscaId(LAtrSimples lista)
{
	LAtrSimples aux = lista;
	int found = 0, res = 0;
	
	while(aux && !found)
	{
		if(strcmp(aux->info->tipo,"id") == 0 )
		{
			res = aux->info->num;
			found = 1;
		}
	}
	
	return res;
}

void buscaDocumento(FILE* file, LDocumentos ldocs, char* type)
{
	LDocumentos aux = ldocs;
	
	while(aux)
	{
		if( (strcmp(type,"foto") == 0 ) && (strcmp(aux->doc->tipo,type) == 0) )
			fprintf(file,"<img src=\"%s\">\n",aux->doc->path);
		
		if( (strcmp(type,"hist") == 0 ) && (strcmp(aux->doc->tipo,type) == 0) )
			fprintf(file,"<p><b>Acerca: </b></p>\n<blockquote style=\"font: 14px/22px normal helvetica, sans-serif;margin-top: 10px;margin-bottom: 10px;margin-left: 50px;padding-left: 15px;font-style: italic;background: #f9f9f9;border-left: 3px solid #ccc;\">\"%s\"</blockquote>\n",leFicheiro(aux->doc->path));
		
		aux = aux -> seg;	
	}
}

void buscaAtrSimples(FILE* file, LAtrSimples simples)
{
	LAtrSimples aux = simples;
	
	while(aux)
	{
			if(strcmp(aux->info->tipo,"nasc") == 0) fprintf(file,"<p><b>Nascimento: </b>%d</p>\n",aux->info->num);
			if(strcmp(aux->info->tipo,"cnasc") == 0) fprintf(file,"<p><b>Nascimento: </b>Por volta de %d</p>\n",aux->info->num);
			if(strcmp(aux->info->tipo,"mort") == 0) fprintf(file,"<p><b>Falecimento: </b>%d<br></p>\n",aux->info->num);
			if(strcmp(aux->info->tipo,"cmort") == 0) fprintf(file,"<p><b>Falecimento: </b>Por volta de %d</p>\n",aux->info->num);
			
			aux = aux->seg;
	}
}

char* leFicheiro(char* path)
{
	FILE* file;
	static char linha[200];
	char* erro;
	file = fopen(path,"r");
	
	if(file)
	{
		while(!feof(file))
		{
			fgets(linha, 200, file);
		}
		return linha;
	}
	else
	{ 
		printf("Erro ao abrir ficheiro!\n"); 
		erro = strdup("Erro ao abrir ficheiro!\n");
		return erro;
	}
}

void buscaEventos(FILE* file,LEventos levs)
{
	LEventos aux = levs;
	
	if(aux)
	{ 
		fprintf(file,"<h2>Eventos</h2>\n");
		fprintf(file,"<ul>\n");		
		while(aux)
		{
			fprintf(file,"<li><b>%s</b> em %d</li><br>\n",aux->evento->nome,aux->evento->ano);
			aux = aux -> seg;
		}
		fprintf(file,"</ul>\n");	
	}
}

void buscaCasamentos(FILE* file,LCasamentos lcasam)
{
	LCasamentos aux = lcasam;
	
	if(aux)
	{ 
		fprintf(file,"<h2>Casamentos</h2>\n");		
		while(aux)
		{
			fprintf(file,"<p><b>Cônjuge: </b><a href=\"Individuo %d.html\" target=\"_blank\">%s</a></p>\n",buscaId(aux->casamento->atrconjuge),aux->casamento->conjuge);
			fprintf(file,"<p><b>Casados em: </b>%d</p>\n",aux->casamento->ano);
			buscaFilhos(file,aux->casamento->filhos);
			aux = aux -> seg;
		}	
	}
}

void buscaFilhos(FILE* file,LFilhos lf)
{
	LFilhos aux = lf;
	
	if(aux)
	{
		fprintf(file,"<p><b>Filhos:</b></p>\n");
		fprintf(file,"<ul>\n");
		while(aux)
		{
			fprintf(file,"<li><a href=\"Individuo %d.html\" target=\"_blank\">%s</a></li><br>\n",buscaId(aux->filho->atrfilho),aux->filho->nome);
			aux = aux -> seg;	
		}
		fprintf(file,"</ul>\n");
	}		
}


void buscaPais(FILE* file, LParentes lps)
{
	LParentes aux = lps;
	
	if(aux)
	{
		fprintf(file,"<p><b>Pais:</b></p>\n");
		fprintf(file,"<ul>\n");
		while(aux)
		{
			if( (strcmp(aux->parente->tipo,"mae") == 0) || (strcmp(aux->parente->tipo,"pai") == 0) )
				fprintf(file,"<li><a href=\"Individuo %d.html\" target=\"_blank\">%s</a></li><br>\n",buscaId(aux->parente->atrparente),aux->parente->nome);
			
			aux = aux->seg;
		}
		fprintf(file,"</ul>\n");
	}
	
}

void buscaAvos(FILE* file, LParentes lps)
{
	LParentes aux = lps;
	int found = 0;
	
	if(aux)
	{
		found = encontraAvo(aux);
		if(found){
			fprintf(file,"<p><b>Avós:</b></p>\n");
			fprintf(file,"<ul>\n");
		}
		
		while(found && aux)
		{
			if(strcmp(aux->parente->tipo,"avomaterna") == 0)
				fprintf(file,"<li><u>Avó Materna:</u><a href=\"Individuo %d.html\" target=\"_blank\"> %s</a></li><br>\n",buscaId(aux->parente->atrparente),aux->parente->nome);
				
			if(strcmp(aux->parente->tipo,"avomaterno") == 0)
				fprintf(file,"<li><u>Avô Materno:</u><a href=\"Individuo %d.html\" target=\"_blank\"> %s</a></li><br>\n",buscaId(aux->parente->atrparente),aux->parente->nome);
				
			if(strcmp(aux->parente->tipo,"avopaterna") == 0)
				fprintf(file,"<li><u>Avó Paterna:</u><a href=\"Individuo %d.html\" target=\"_blank\"> %s</a></li><br>\n",buscaId(aux->parente->atrparente),aux->parente->nome);
				
			if(strcmp(aux->parente->tipo,"avopaterno") == 0)
				fprintf(file,"<li><u>Avô Paterno:</u><a href=\"Individuo %d.html\" target=\"_blank\"> %s</a></li><br>\n",buscaId(aux->parente->atrparente),aux->parente->nome);
			
			aux = aux->seg;
		}
		if(found)
			fprintf(file,"</ul>\n");
	}
}

int encontraAvo(LParentes lista)
{
	LParentes aux = lista;
	int found = 0;
	
	while(!found && aux)
	{
		if( (strcmp(aux->parente->tipo,"avopaterno") == 0) || (strcmp(aux->parente->tipo,"avopaterna") == 0) || (strcmp(aux->parente->tipo,"avomaterno") == 0) || (strcmp(aux->parente->tipo,"avomaterna") == 0))
			found = 1;
			
		aux = aux->seg;
	}
	return found;
}
