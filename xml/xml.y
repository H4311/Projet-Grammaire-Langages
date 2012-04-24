%{

#include "common.h"
using namespace std;
using namespace xml;

int xmlwrap(void);
void xmlerror(Document** doc, char *msg);
int yylex(void);

%}

%union {
   char * s;
   ElementName * en;  		/* le nom d'un element avec son namespace */
   Content * c; 		/* contenu xml */
   EmptyElement * ee; 		/* element xml */
   list<Content*> * lc; 	/* liste d'éléments (enfants) */
   AttList *al;			/* liste d'attributs */
   Doctype *dt;			/* doctype */
   list<Comment*> * ld;	/* liste de commentaires */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND

%type <c> comment 
%type <ee> empty_or_content xml_element
%type <en> start
%type <lc> content_opt close_content_and_end
%type <al> attribut_opt
%type <dt> declaration declarations_opt
%type <ld> misc_seq_opt

%parse-param { xml::Document** doc } 

%%

document
 : declarations_opt xml_element misc_seq_opt 
	{ 
		*doc  = new Document();
		if ($1 != NULL) {
			(*doc)->setDoctype($1);
			delete $1;
		}
		(*doc)->setComments($3);
		delete $3;
		(*doc)->setRoot($2);
	}
 ;

misc_seq_opt
 : misc_seq_opt comment	
	{ 
		$1->push_back(static_cast<Comment*>($2));
		$$ = $1;
	}
 | /*empty*/		
	{ 
		$$ = new list<Comment*>; 
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
		$3->SetAttList($2);
		delete $2;
		$3->SetName($1);
		$$ = $3;
		delete $1;
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
		((Element*)$$)->SetChildren($1);
		delete $1;
	}
 ;

close_content_and_end
 : CLOSE	content_opt END 
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

xml::Document* parseXML(const char* file)
{
  int err;
  xml::Document* document = NULL;
  
  xmlin = fopen(file, "r");

  //yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  if (xmlin != NULL)
  {
    err = xmlparse(&document);
    if (err != 0) 
    {
	printf("Parse ended with %d error(s)\n", err);
	document = NULL;
    }
    else  printf("Parse ended with success\n");
    fclose(xmlin);
  }
  
  return document;
}

int xmlwrap(void)
{
  return 1;
}

void xmlerror(xml::Document** doc, char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

