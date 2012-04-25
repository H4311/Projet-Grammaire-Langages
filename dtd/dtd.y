%{

#include "common.h"
using namespace std;
using namespace dtd;

#include <stdio.h>
void yyerror(char *msg);
int dtdwrap(void);
void dtdrestart(FILE *);
int yylex(void);

%}

%union { 
	char *s;
	DeclarationList *dl;
	ChildrenList *cl;
	Element *e;
	Attribute *a;
}

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA COLON
%token <s> IDENT TOKENTYPE DECLARATION STRING

%parse-param { Document** doc } 

%%

main: dtd_list_opt 
    ;

ident
: IDENT
| IDENT COLON IDENT
;

dtd_list_opt
: dtd_list_opt ATTLIST ident att_definition_opt CLOSE
| dtd_list_opt ELEMENT ident contentspec CLOSE            
| /* empty */                     
;

att_definition_opt
: att_definition_opt attribute
| /* empty */
;

attribute
: ident att_type default_declaration
;

att_type
: CDATA    
| TOKENTYPE
| enumerate
;

enumerate
: OPENPAR enum_list_plus CLOSEPAR
;

enum_list_plus
: enum_list PIPE item_enum
;

enum_list
: item_enum               
| enum_list PIPE item_enum
;

item_enum
: ident
;

default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;

/* Définition de ELEMENT : */
contentspec
: EMPTY
| ANY
| children
| mixed
;

card_opt
: QMARK
| AST
| PLUS
| /* empty */
;

children
: choice card_opt
| seq card_opt
;

cp
: children
| IDENT card_opt
;

choice
: OPENPAR cp list_choice CLOSEPAR
;

list_choice
: list_choice PIPE cp
| PIPE cp
;

seq
: OPENPAR cp list_seq_opt CLOSEPAR
;

list_seq_opt
: list_seq_opt COMMA cp
| /* empty */
;

mixed
: OPENPAR PCDATA list_mixed CLOSEPAR AST
| OPENPAR PCDATA CLOSEPAR ast_opt
;

ast_opt
: AST
| /* empty */
;

list_mixed
: list_mixed PIPE IDENT
| PIPE IDENT
;

%%

extern FILE *dtdin;

int parseDTD(const char * file)
{
  int err;
  
  dtdin = fopen(file, "r");
  dtdrestart(dtdin);

  //yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  if (dtdin != NULL)
  {
    err = dtdparse();
    if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with success\n", err);
    fclose(dtdin);
  }
  
  return 0;
}

int dtdwrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


