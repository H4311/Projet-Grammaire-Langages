%option 8bit 

%{
#include <ctype.h>
#include <string.h>
#include "dtd.tab.h"

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return strdup(buf);
}
  
/* affecte la valeur de la chaine de caractère et renvoie le token */
#define stringreturn(tokenval) dtdlval.s=skipSpace(yytext);return(tokenval)

%}
%option noyywrap

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{nl}?"<"
close		">"{nl}?
openpar "("
closepar ")"
comma ","
pipe "|"
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
tokentype "ID"|"IDREF"|"IDREFS"|"ENTITY"|"ENTITIES"|"NMTOKEN"|"NMTOKENS"
name		{namestart}{namechar}*
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
element {open}"!ELEMENT"{ws}
attlist {open}"!ATTLIST"{ws}
declaration "#"("REQUIRED"|"IMPLIED"){ws}?
fixed "#FIXED"{ws}
pcdata "#PCDATA"{ws}?
cdata "CDATA"{ws}?
qmark "?"
ast "*"
plus "+"
empty "EMPTY"
any "ANY"

%s INSIDE

/* 
   INITIAL : en dehors d'un bloc ELEMENT ou ATTLIST
   INSIDE : dans un bloc ELEMENT ou ATTLIST
*/

%%

<INITIAL>{ws}		            { /* skip */}
<INITIAL>{element}            { BEGIN(INSIDE); return ELEMENT; }
<INITIAL>{attlist}            { BEGIN(INSIDE); return ATTLIST; }
<INSIDE>{ws}?{close}          { BEGIN(INITIAL); return CLOSE; }
<INSIDE>{openpar}             { return OPENPAR; }
<INSIDE>{closepar}		      { return CLOSEPAR; }
<INSIDE>{comma}{ws}?          { return COMMA; }
<INSIDE>{pipe}{ws}?           { return PIPE; }
<INSIDE>{declaration}         { stringreturn(DECLARATION); }
<INSIDE>{fixed}               { return FIXED; }
<INSIDE>{ast}                 { return AST ; }
<INSIDE>{qmark}               { return QMARK ; }
<INSIDE>{plus}                { return PLUS ; }
<INSIDE>{empty}               { return EMPTY; }
<INSIDE>{any}                 { return ANY; }
<INSIDE>{pcdata}              { return PCDATA; }
<INSIDE>{cdata}               { return CDATA; }
<INSIDE>{string}              { stringreturn(STRING); }
<INSIDE>{tokentype}{ws}?      { stringreturn(TOKENTYPE); }
<INSIDE>{name}{ws}?           { stringreturn(IDENT); }
{comment}		               { /* skip comments stringreturn(COMMENT); */ }

{nl}                    {printf("%s",yytext);/* skip, must be an extra one at EOF */;}
.			{ fprintf(stderr, "!ERROR(%c)\n", *yytext);}
