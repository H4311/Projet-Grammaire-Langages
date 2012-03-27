%{
# include "calc.tab.h"
# include <iostream>
# include <string>
using namespace std;
%}

digit [0-9]
ident [a-zA-Z]+

%option noyywrap
%%

{digit}+"."{digit}* { yylval.d = atof(yytext);
			return DOUBLE; }
{digit}+ { yylval.i = atoi(yytext); return INT; }
{ident} { yylval.s = strdup(yytext); return VAR; }
"+" { return PLUS; }
"-" { return MOINS; }
"*" { return FOIS; }
"/" { return SLASH; }
"(" { return PAR_OUV; }
")" { return PAR_FER; }
"=" { return EGAL; }
. { cout << "Caractère inattendu : " << yytext << endl; }

%%
