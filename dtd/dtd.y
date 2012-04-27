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

%locations

%union { 
	char *s;
	std::string *stds;
	AttDefList *adl;
	DeclarationList *dl;
	ChildrenList *cl;
	AttTypeList *atl;
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
%type <stds> ident item_enum default_declaration 
%type <adl> att_definition_opt
%type <cs> contentspec
%type <s> card_opt ast_opt
%type <dtdc> choice
%type <dtds> seq
%type <ch> children cp mixed
%type <cl> list_choice list_seq_opt list_mixed
%type <a> attribute
%type <atl> att_type enumerate enum_list enum_list_plus

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
		$1->push_back(new AttributeList(*$3, *$4));
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
		$1->push_back($2);
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
		$$ = new Attribute(*$1, *$2, *$3); // TODO 4ème argument ?
		delete $1;
		delete $2;
		delete $3;
	}
;

att_type
: CDATA    
	{
		$$ = new AttTypeList;
		$$->push_back("CDATA"); // TODO vérifier
	}
| TOKENTYPE
	{
		$$ = new AttTypeList;
		$$->push_back(string($1));
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
		$$ = $2;
	}
;

enum_list_plus
: enum_list PIPE item_enum
	{
		$1->push_back(*$3);
		delete $3;
		$$ = $1;
	}
;

enum_list
: item_enum               
	{
		$$ = new AttTypeList;
		$$->push_back(*$1);
		delete $1;
	}
| enum_list PIPE item_enum
	{
		$1->push_back(*$3);
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
		$$ = new string("#FIXED ");	
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
		$$ = $1;
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
		$$ = NULL;
	}
;

children
: choice card_opt
	{
		if ($2 != NULL)
		{
			$1->SetCard(*$2);
			delete $2;
		}
		$$ = $1;
	}
| seq card_opt
	{
		if ($2 != NULL)
		{
			$1->SetCard(*$2);
			delete $2;
		}
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
		$$ = new Name($1);
		if ($2 != NULL)
		{
			((Name*)$$)->SetCard(*$2);
			delete $2;
		}
		free($1);
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
	{
		// Une liste mixed est un choix pour lequel le premier
		// élément est PCDATA.
		$3->push_front(new Name("#PCDATA"));
		$$ = new Choice(*$3);
		((Choice*)$$)->SetCard('*');
		delete $3;
	}
| OPENPAR PCDATA CLOSEPAR ast_opt
	{
		$$ = new Name("(#PCDATA)");
		if ($4 != NULL) { ((Name*)$$)->SetCard(*$4); }
		delete $4;
	}
;

ast_opt
: AST
	{
		$$ = new char('*');
	}
| /* empty */
	{
		$$ = NULL;
	}
;

list_mixed
: list_mixed PIPE IDENT
	{
		$1->push_back(new Name($3));
		free($3);
		$$ = $1;
	}
| PIPE IDENT
	{
		$$ = new ChildrenList;
		$$->push_back(new Name($2));
		free($2);
	}
;

%%

extern FILE *dtdin;
extern void dtdlex_destroy();
extern int dtdlineno;

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
	fprintf(stderr, "Parse ended with %d error(s)\n", err);
	if (document != NULL) delete document;
    }
    fclose(dtdin);
    dtdlex_destroy();
  }
  
  return document;
}

int dtdwrap(void)
{
  return 1;
}

int dtderror(Document** doc, char *msg)
{
  fprintf(stderr, "[DTD Syntax] Error : %s, at line %d.\n", msg, dtdlineno);
}


