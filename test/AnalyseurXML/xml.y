%{

using namespace std;
#include "commun.h"

int xmlwrap(void);
void yyerror(char *msg);
int yylex(void);

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND

%%

document
 : declarations_opt xml_element misc_seq_opt 
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/
 ;
comment
 : COMMENT
 ;

declarations_opt
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE IDENT IDENT STRING CLOSE 
 ;

xml_element
 : start attribut_opt empty_or_content 
 ;

attribut_opt
 : attribut_opt IDENT EQ STRING
 | /*empty*/
 ;
 
start
 : START		
 | NSSTART	
 ;
empty_or_content
 : SLASH CLOSE	
 | close_content_and_end CLOSE 
 ;
close_content_and_end
 : CLOSE	content_opt END 
 ;
content_opt 
 : content_opt DATA		
 | content_opt comment        
 | content_opt xml_element      
 | /*empty*/         
 ;
%%

extern FILE *xmlin;

int parseXML(const char* file)
{
  int err;
  
  xmlin = fopen(file, "r");

  //yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  if (xmlin != NULL)
  {
    err = yyparse();
    if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with success\n", err);
    fclose(xmlin);
  }
  
  return 0;
}

int xmlwrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

