%{
#include <iostream>
#include <map>
#include <string>
using namespace std;

int yylex();
void yyerror(double* d, const char* msg);

map<string, double> variables;
%}


%union {
	double d;
	int i;
	char* s;
}

%token PLUS MOINS FOIS SLASH PAR_OUV PAR_FER EGAL
%token <s> VAR
%token <d> DOUBLE
%token <i> INT

%type <d> expr

%right EGAL
%left PLUS MOINS
%left FOIS SLASH

%parse-param {double* d}

%%

main : expr { *d = $1;  }
     ;

expr : 	DOUBLE { $$ = $1; }
     	| INT { $$ = $1; }
     	| expr PLUS expr { $$ = $1 + $3; }
	| expr MOINS expr { $$ = $1 - $3; }
	| expr FOIS expr { $$ = $1 * $3; }
	| expr SLASH expr { $$ = $1 / $3; }
	| PAR_OUV expr PAR_FER { $$ = $2; }
	| VAR { $$ = variables[$1]; }
	| VAR EGAL expr { $$ = (variables[string($1)] = $3); }
	;

%%
# include <iostream>
# include <map>
using namespace std;

int main(void) {
	double * d = new double;

	cout << "Entrez des expressions littérales simples (a=3, 4+7*8,...) "
	     << "puis appuyez sur Ctrl+D pour évaluer. Pour arrêter, entrez 0"
	     << "(ou arrangez vous pour que le résultat fasse 0 ^^.";
	do {
		yyparse(d);
		cout << "Valeur calculée : " << *d << endl;
	} while (*d != 0);
	delete d;
}

void yyerror(double* d, const char* msg) {
	cout << msg;
}
