%{
	#include "estruturas.h"
    #include<stdio.h>
    #include<stdlib.h>
    #define YYERROR_VERBOSE
    
%}
%token num nome path PAI MAE ABREID FECHAID NASC MORT AVOMATERNA AVOPATERNA AVOPATERNO AVOMATERNO CNASC CMORT FOTO HIST FILHO EVENTO EVSEP FECHAEVENTO ABREEVENTO
%union{
	int valor;
	char* str;
	LPessoas lpessoas;
	Pessoa p;
	LAtrSimples lsimples;
	InformacaoPessoal informacao;
	AtrComplexos complexos;
	LParentes lparentes;
	Parente parente;
	LDocumentos ldocs;
	Documento doc;
	LEventos leventos;
	Evento evento;
	LCasamentos lcasamentos;
	Casamento casamento;
	LFilhos lfilhos;
	Filho filho;
}
%type<valor> num
%type<str> nome path
%type<lpessoas> Gen
%type<p> Pessoa
%type<lsimples> AtributosSimp
%type<informacao> InfoPessoal
%type<complexos> AtributosComp
%type<lparentes> Parentes
%type<parente> Parente
%type<ldocs> Documentos
%type<doc> Doc
%type<leventos> Eventos
%type<evento> Evento
%type<lcasamentos> Casamentos
%type<casamento> Casamento
%type<lfilhos> Filhos
%type<filho> Filho
%start Principal
%%
Principal 	: Gen '$' 						{ /*imprimeGenealogia($1);*/ criaHtmlIndex($1); return 0;}
			;

Gen			: Gen Pessoa			{ $$ = consGenealogia($1,$2); }		
			| Pessoa				{ $$ = consGenealogia(NULL,$1); }
			;

Pessoa		: nome AtributosSimp AtributosComp Eventos Casamentos 	{ $$ = criaPessoa($1,$2,$3,$4,$5); }
			;

AtributosSimp 	: AtributosSimp InfoPessoal  			{ $$ = consLAtrSimples($1,$2); }
				|										{ $$ = NULL; }
				;
			
InfoPessoal		: NASC num 								{ $$ = criaInfoPessoal("nasc",$2); }
				| CNASC num 							{ $$ = criaInfoPessoal("cnasc",$2); }
				| CMORT num 							{ $$ = criaInfoPessoal("cmort",$2); }
				| MORT num 								{ $$ = criaInfoPessoal("mort",$2); }
				| ABREID num FECHAID 					{ $$ = criaInfoPessoal("id",$2); }
				;
			
AtributosComp	: Parentes Documentos					{$$ = criaAtrComplexos($1,$2); }
				;
		


Parentes	: Parentes Parente							{ $$ = consLParentes($1,$2); }
			|											{ $$ = NULL; }
			;

Parente		: PAI nome AtributosSimp						{ $$ = criaParente("pai",$2,$3); }
			| MAE nome AtributosSimp						{ $$ = criaParente("mae",$2,$3); }
			| AVOMATERNA nome AtributosSimp					{ $$ = criaParente("avomaterna",$2,$3); }
			| AVOMATERNO nome AtributosSimp					{ $$ = criaParente("avomaterno",$2,$3); }
			| AVOPATERNO nome AtributosSimp					{ $$ = criaParente("avopaterno",$2,$3); }
			| AVOPATERNA nome AtributosSimp					{ $$ = criaParente("avopaterna",$2,$3); }
			;

Documentos	: Documentos Doc								{ $$ = consLDocumentos($1,$2); }
			|												{ $$ = NULL; }
			;

			
Doc		: FOTO path								{ $$ = criaDocumento("foto",$2); }
		| HIST path								{ $$ = criaDocumento("hist",$2); }
		;

Casamentos 	: Casamentos Casamento				{ $$ = consLCasamentos($1,$2); }
			|									{ $$ = NULL; }
			;
			
Casamento	: num ABREID num FECHAID nome AtributosSimp Filhos 		{ $$ = criaCasamento($1,$3,$5,$6,$7); }
			;
			
Filhos		: Filhos Filho								{ $$ = consLFilhos($1,$2); }
			|											{ $$ = NULL; }

Filho		: FILHO nome AtributosSimp 					{ $$ = criaFilho($2,$3); }
			;
			
			
Eventos		: Eventos Evento								{ $$ = consLEventos($1,$2); }
			|												{ $$ = NULL; }
			;

Evento		: EVENTO ABREEVENTO nome EVSEP num FECHAEVENTO			{ $$ = criaEvento($3,$5); }
			;



%%

int main(int argc, char *argv[]){
	system("cp /usr/local/share/ngen/styles.css .");
	system("cp /usr/local/share/ngen/paper005.gif .");
	extern FILE *yyin;
	if(argc == 1){
		//se não receber argumentos, lê da stdin
		yyin = stdin;
		yylex();
	}
	else{
		// se receber argumento, lê os diversos ficheiros
		int i;
		for(i=1;i<argc;i++){
			yyin = fopen(argv[i],"r");
		}
	}
	yyparse();
    return 0;
}

int yyerror(char *s){
	extern int yylineno;
	extern char* yytext;
	fprintf(stderr,"%s",s);
	fprintf(stderr,"\nErro foi: %d '%s'\n",yylineno,yytext);
}

