%{
#include <stdio.h>
#include <string>
#include "common.h"
using namespace std;
using namespace dtd;

int dtderror(Document ** doc, char *msg);
int dtdwrap(void);
void dtdrestart(FILE *);
int yylex(void);

%}

%union { 
	char *s;
	std::string *stds;
	AttDefList *adl;
	DeclarationList *dl;
	ChildrenList *cl;
	dtd::Element *e;
	dtd::Attribute *a;
	dtd::ContentSpec *cs;
	dtd::Children *ch;
	dtd::Choice *dtdc;
	dtd::Seq *dtds;
}

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA COLON 
%token <s> IDENT TOKENTYPE DECLARATION STRING

%type <dl> dtd_list_opt
%type <stds> ident attribute att_type enumerate enum_list enum_list_plus item_enum default_declaration 
%type <adl> att_definition_opt
%type <cs> contentspec
%type <s> card_opt ast_opt
%type <dtdc> choice
%type <dtds> seq
%type <ch> children cp
%type <cl> list_choice list_seq_opt

%parse-param { Document** doc } 
/* Elements à définir : */
/* main ident dtd_list_opt att_definition_opt attribute att_type enumerate
enum_list_plus enum_list item_enum default_declaration contentspec card_opt 
children cp choice list_choice seq list_seq_opt mixed ast_opt list_mixed */

%%

main: dtd_list_opt 
	{
		*doc = new Document($1);
	}
    ;

ident
: IDENT
	{
		$$ = new string($1);
		free($1);
	}
| IDENT COLON IDENT
	{
		$$ = new string($1);
		*$$ += ":";
		*$$ += string($3);
		free($1);
		free($3);
	}
;

dtd_list_opt
: dtd_list_opt ATTLIST ident att_definition_opt CLOSE
	{
		$1->push_back(new Attribute(*$3, *$4));
		delete $3;
		delete $4;
		$$ = $1;
	}
| dtd_list_opt ELEMENT ident contentspec CLOSE            
	{
		$1->push_back(new Element(*$3, $4));
		delete $3;
		$$ = $1;
	}
| /* empty */
	{
		$$ = new DeclarationList;
	}
;

att_definition_opt
: att_definition_opt attribute
	{
		$1->push_back(*$2);
		delete $2;
		$$ = $1;
	}
| /* empty */
	{
		$$ = new AttDefList;
	}
;

attribute
: ident att_type default_declaration
	{
		*$1 += *$2;
		delete $2;
		*$1 += *$3;
		delete $3;
		$$ = $1;
	}
;

att_type
: CDATA    
	{
		$$ = new string("CDATA");
	}
| TOKENTYPE
	{
		$$ = new string($1);
		free($1);
	}
| enumerate
	{
		$$ = $1;
	}
;

enumerate
: OPENPAR enum_list_plus CLOSEPAR
	{
		$$ = new string("(");
		*$$ += *$2;
		delete $2;
		*$$ += ')';
	}
;

enum_list_plus
: enum_list PIPE item_enum
	{
		*$1 += '|';
		*$1 += *$3;
		delete $3;
		$$ = $1;
	}
;

enum_list
: item_enum               
	{
		$$ = $1;
	}
| enum_list PIPE item_enum
	{
		*$1 += '|';
		*$1 += *$3;
		delete $3;
		$$ = $1;
	}
;

item_enum
: ident
	{
		$$ = $1;
	}
;

default_declaration
: DECLARATION 
	{
		$$ = new string($1);
		free($1);
	}
| STRING     
	{
		$$ = new string($1);
		free($1);
	}
| FIXED STRING 
	{
		$$ = new string("FIXED");	
		*$$ += string($2);
		free($2);
	}
;

/* Définition de ELEMENT : */
contentspec
: EMPTY
	{
		$$ = new Empty();
	}
| ANY
	{
		$$ = new Any();
	}
| children
	{
		$$ = $1;
	}
| mixed
	{
		// TODO
		// Dixit arnaud : "on le gère comme un Choice, avec 
		// juste #PCDATA en premier membre."
	}
;

card_opt
: QMARK
	{
		$$ = new char('?');
	}
| AST
	{
		$$ = new char('*');
	}
| PLUS
	{
		$$ = new char('+');
	}
| /* empty */
	{
		$$ = new char;
	}
;

children
: choice card_opt
	{
		$1->SetCard(*$2);
		delete $2;
		$$ = $1;
	}
| seq card_opt
	{
		$1->SetCard(*$2);
		delete $2;
		$$ = $1;
	}
;

cp
: children
	{
		$$ = $1;
	}
| IDENT card_opt
	{
		$$ = new Name($1, *$2);
		free($1);
		delete $2;
	}
;

choice
: OPENPAR cp list_choice CLOSEPAR
	{
		$3->push_front($2);
		$$ = new Choice(*$3);
		delete $3;
	}
;

list_choice
: list_choice PIPE cp
	{
		$1->push_back($3);
		$$ = $1;
	}
| PIPE cp
	{
		$$ = new ChildrenList;
		$$->push_back($2);
	}
;

seq
: OPENPAR cp list_seq_opt CLOSEPAR
	{
		$3->push_front($2);
		$$ = new Seq(*$3);
		delete $3;	
	}
;

list_seq_opt
: list_seq_opt COMMA cp
	{
		$1->push_back($3);
		$$ = $1;	
	}
| /* empty */
	{
		$$ = new ChildrenList;
	}
;

mixed
: OPENPAR PCDATA list_mixed CLOSEPAR AST
| OPENPAR PCDATA CLOSEPAR ast_opt
;

ast_opt
: AST
	{
		$$ = new char('*');
	}
| /* empty */
	{
		$$ = new char;
	}
;

list_mixed
: list_mixed PIPE IDENT
| PIPE IDENT
;

%%

extern FILE *dtdin;
// extern void yylex_destroy();

Document* parseDTD(const char * file)
{
  int err;
  Document * document = NULL;
  
  dtdin = fopen(file, "r");
  dtdrestart(dtdin);

  //yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  if (dtdin != NULL)
  {
    err = dtdparse(&document);
    if (err != 0) 
    {
	printf("Parse ended with %d error(s)\n", err);
	if (document != NULL) delete document;
    }
    else  printf("Parse ended with success\n", err);
    fclose(dtdin);
    // yylex_destroy();
  }
  
  return document;
}

int dtdwrap(void)
{
  return 1;
}

int dtderror(Document** doc, char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


