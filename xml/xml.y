%{

#include "common.h"
using namespace std;
using namespace xml;

int xmlwrap(void);
void xmlerror(Document** doc, const char *msg);
int yylex(void);

const char* ERR_DOCUMENT = "Erreur au niveau Document";
const char* ERR_CONTENU_APRES_RACINE = "Contenu interdit après la balise racine. Ce contenu sera ignoré.";
const char* ERR_COMMENTAIRE = "Commentaire mal formé";

%}

%locations

%union {
   char * s;
   ElementName * en;  			/* le nom d'un element avec son namespace */
   xml::Content * c; 			/* contenu xml */
   xml::EmptyElement * ee; 		/* element xml */
   list<xml::Content*> * lc;	 	/* liste d'éléments (enfants) */
   AttList *al;				/* liste d'attributs */
   Doctype *dt;				/* doctype */
   list<xml::Comment*> * ld;		/* liste de commentaires */
   xml::ProcessingInstruction* p;
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE END NSEND
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL 

%type <c> comment 
%type <ee> empty_or_content xml_element
%type <en> start
%type <lc> content_opt close_content_and_end
%type <al> attribut_opt
%type <dt> declaration declarations_opt
%type <ld> misc_seq_opt
%type <p> prolog_opt 

%parse-param { xml::Document** doc } 

%destructor { free($$); } <s>
%destructor { delete $$; } <en> <c> <ee> <dt> <at> <p> <al>
%destructor 
{ 
	list<xml::Comment*>::iterator it;
	for (it = $$->begin(); it != $$->end(); ++it)
	{
		delete *it;
	}
	delete $$;
} <ld>
%destructor 
{ 
	list<xml::Content*>::iterator it;
	for (it = $$->begin(); it != $$->end(); ++it)
	{
		delete *it;
	}
	delete $$;
} <lc>

%%

document
 : prolog_opt declarations_opt xml_element misc_seq_opt 
	{ 
		*doc  = new Document();

		if ($1 != NULL) {
			(*doc)->setXmlProlog($1);
		}

		if ($2 != NULL) {
			(*doc)->setDoctype(*$2);
			delete $2;
		}

		if ($4 != NULL) {
			(*doc)->setComments(*$4);
			delete $4;
		}

		(*doc)->setRoot($3);
	}
 | error
	{
		yyerror(doc, ERR_DOCUMENT);
	}
;

prolog_opt
 : STARTSPECIAL attribut_opt CLOSESPECIAL
	{
		$$ = new ProcessingInstruction(*$1);
		delete $1;
		$$->setAttList(*$2);	
		delete $2;
	}
 | /* empty */
	{
		$$ = NULL;
	}
 ;

misc_seq_opt
 : misc_seq_opt comment	
	{ 
		if ($2 != NULL) $1->push_back(static_cast<Comment*>($2));
		$$ = $1;
	}
 | /*empty*/		
	{ 
		$$ = new list<Comment*>; 
	}
 | error
	{
		yyerror(doc, ERR_CONTENU_APRES_RACINE);
		$$ = NULL;
	}
 ;

comment
 : COMMENT
	 { 
		$$ = new Comment($1);
	   	free($1);
	 }
 ;

declarations_opt
 : declaration		
	{ 
		$$ = $1;
	}
 | /*empty*/
	{
		$$ = NULL; 
	}
 ;
 
declaration
 : DOCTYPE IDENT IDENT STRING CLOSE 	
	{ 
		$$ = new Doctype($2, $4);
		free($2);
		free($3);
		free($4);
	}
 ;

xml_element
 : start attribut_opt empty_or_content 	
	{ 
		$3->setAttList(*$2);
		delete $2;
		$3->setName(*$1);
		delete $1;
		$$ = $3;
	}
 ;

attribut_opt
 : attribut_opt IDENT EQ STRING 
	{ 
		$1->push_back(Attribut($2, $4)); 
		$$ = $1; 
		free($2); 
		free($4);
	}
 | attribut_opt NSIDENT EQ STRING
	{
		$1->push_back(Attribut($2, $4)); 
		$$ = $1; 
		free($2); 
		free($4);
	}
 | /*empty*/ 			
	{ 
		$$ = new AttList; 
	}
 ;
 
start
 : START 	
	{ 
		$$ = $1; 
	}
 | NSSTART 	
	{ 
		$$ = $1; 
	}
 ;

empty_or_content
 : SLASH CLOSE 
	{ /* ex : <br/> */
		$$ = new EmptyElement();
	}	
 | close_content_and_end CLOSE 
	{ /* ex : <a>something</a> */
		$$ = new Element();
		((Element*)$$)->setChildren(*$1);
		delete $1;
	}
 ;

close_content_and_end
 : CLOSE	content_opt END 
	{ 
		$$ = $2; 
	} 
 |
   CLOSE	content_opt NSEND
	{
		$$ = $2;
	}
 ;

content_opt 
 : content_opt DATA	   	
	{ 
		$1->push_back(new Data($2)); 
		$$ = $1; 
		free($2);
	}
 | content_opt comment     	
	{ 
		$1->push_back($2); 
		$$ = $1; 
	}
 | content_opt xml_element 	
	{ 
		$1->push_back($2); 
		$$ = $1; 
	}      
 | /*empty*/ 			
	{ 
		$$ = new list<Content*>; 
	}        
 ;
%%

extern FILE *xmlin;
extern void xmllex_destroy();
extern int xmllineno;

xml::Document* parseXML(const char* file)
{
  int err;
  xml::Document* document = NULL;
  
  xmlin = fopen(file, "r");

  //xmldebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  if (xmlin != NULL)
  {
    err = yyparse(&document);
    if (err != 0) 
    {
	fprintf(stderr, "Parse ended with %d error(s)\n", err);
	document = NULL;
    }
    fclose(xmlin);
    xmllex_destroy();
  }
  
  return document;
}

int xmlwrap(void)
{
  return 1;
}

void xmlerror(xml::Document** doc, const char *msg)
{
  fprintf(stderr, "[XML Syntax] Error : %s, at line %d.\n", msg, xmllineno);
}

