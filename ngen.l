%{
	#include "estruturas.h"
	#include "y.tab.h"
%}
%option yylineno
%option noyywrap
%x PESSOA DOCS CASAMENTO
%%
<*>#P																			BEGIN PESSOA;
<PESSOA,CASAMENTO>(á|Á|à|À|â|Â|ã|Ã|é|É|ó|Ó|ç|Ç|[a-zA-Z ])+[ \n]					{ yytext[strlen(yytext)-1] = '\0'; 
																				  yylval.str = strdup(yytext); 
																				  return nome; }
<PESSOA>\<M\>[ ]																return MAE;
<PESSOA>\<P\>[ ]																return PAI;
<PESSOA>\<MM\>[ ]																return AVOMATERNA;
<PESSOA>\<MP\>[ ]																return AVOPATERNA;									  
<PESSOA>\<PP\>[ ]																return AVOPATERNO;									  
<PESSOA>\<PM\>[ ]																return AVOMATERNO;									  
<PESSOA,CASAMENTO>[0-9]{4}														{ yylval.valor = atoi(yytext); return num; }
<PESSOA,CASAMENTO>[0-9]+														{ yylval.valor = atoi(yytext); return num; }
<PESSOA,CASAMENTO>\[															return ABREID;
<PESSOA,CASAMENTO>\]															return FECHAID;
<PESSOA,CASAMENTO>\*															return NASC;
<PESSOA,CASAMENTO>\*c															return CNASC;
<PESSOA,CASAMENTO>\+c															return CMORT;
<PESSOA,CASAMENTO>\+															return MORT;
<PESSOA>\<FOTO\>[ ]																{ BEGIN DOCS; return FOTO; }
<PESSOA>\<HIST\>[ ]																{ BEGIN DOCS; return HIST; }
<PESSOA>\:																		return EVSEP;
<PESSOA>\(																		return ABREEVENTO;
<PESSOA>\)																		return FECHAEVENTO;
<PESSOA>\<EV\>[ ]																return EVENTO;
<DOCS>[a-zA-Z0-9\-\/\.\~_]+\.[a-zA-Z]+[^\n]										{ yylval.str = strdup(yytext); 
																				  BEGIN PESSOA;
																				  return path; }
<*>\<CC\>[ ]																	BEGIN CASAMENTO;
<CASAMENTO>\<F\>[ ]																return FILHO;
<*>[ \t\n]																		{ }
<*>.																			;
<<EOF>>																			return '$';				
