%option 8bit nodefault
%option noyywrap

%{
#include "commun.h"
#include "xmlincludes.h"
#include "xml.tab.h"

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return buf;
}

// enlève les " au début et à la fin
static char * getString(char *s) {
   s++;
   s[strlen(s)-1] = '\0';
   return s;
}

static char* word(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; isspace(s[k]) || s[k] == '<' || s[k] == '/' ; k++) ;
  for (i = k; s[i] && ! isspace(s[i]); i++) ;
  buf = (char *) malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}

static char * nameSpace(char *s)  /* extrait la première partie, l'espace de nom */
{
   char *name;
   int i,k;
   for (k = 0; isspace(s[k]) || s[k] == '<' || s[k] == '/' ; k++) ;
   for (i=k;s[i]!=':';i++) ;
   name = (char*) malloc((i-k+1)*sizeof(char));
   strncpy(name,s+k,i-k);
   name[i-k] = '\0';
   return name;
}

static char *split_namespace(char *s) { /* extrait la deuxième partie après l'espace de nom */
   char *name;
   int i,k;
   for (i=0;s[i]!=':';i++) ;
   i++;
   name = (char*) malloc((strlen(s+i)+1)*sizeof(char));
   strcpy(name,s+i);
   return name;
}

%}

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{ws}?"<"
close		">"{nl}?
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
name		{namestart}{namechar}*
nsname		{namestart}{namechar}*":"{namestart}{namechar}*
data		([^<\n&]|\n[^<&]|\n{esc}|{esc})+
pcdata		[^<]+
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
xmlversion   {ws}?"<?xml"{ws}"version="{string}{ws}"encoding="{string}"?>"{nl}?
doctype     {ws}?"<!DOCTYPE"{ws}
openspecial {ws}?"<?"
closespecial "?>"{nl}?

/*
 * Le mode CONTENT est utilse pour le contenu des elements, c a d
 *  entre le ">" et le "<" des balises 
 *  Le mode INITIAL est utlise en dehors de l'element RACINE 
 * et a l'interieur des balises
 */

%s CONTENT


%%

<INITIAL>{ws}		{ /* skip */}
<INITIAL>{xmlversion} { /* skip */}
<INITIAL>{doctype} { return DOCTYPE;}
<INITIAL>"/"		{ return SLASH;}
<INITIAL>"="		{ return EQ;}
<INITIAL>{close}	{ BEGIN(CONTENT); return CLOSE;}
<INITIAL>{closespecial}	{ return CLOSESPECIAL;}
<INITIAL>{name}		{ xmllval.s = strdup(yytext); return IDENT;}
<INITIAL>{nsname}		{ xmllval.s = strdup(yytext); return NSIDENT;}
<INITIAL>{string}	{ xmllval.s = strdup(getString(yytext)); return STRING;}

{openspecial}{ws}?{name}	{ BEGIN(INITIAL); char * tmp = word(yytext); xmllval.en = new ElementName("",tmp); free(tmp); return STARTSPECIAL;}
{open}{ws}?{name}	{ BEGIN(INITIAL); char * tmp = word(yytext); xmllval.en = new ElementName("",tmp); free(tmp); return START;}
{open}{ws}?{nsname}	{ BEGIN(INITIAL); char *tmp1 = nameSpace(yytext); char * tmp2 = split_namespace(yytext); xmllval.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return NSSTART;}
{open}"/"{name}		{BEGIN(INITIAL); char * tmp = word(yytext); xmllval.en = new ElementName("",tmp); free(tmp); return END;}
{open}"/"{nsname}		{BEGIN(INITIAL); char *tmp1 = nameSpace(yytext); char * tmp2 = split_namespace(yytext); xmllval.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return NSEND;}
{comment}		{ xmllval.s = strdup(yytext); return COMMENT;}

<CONTENT>{ws}?{pcdata}		{ xmllval.s = strdup(skipSpace(yytext)); return DATA;}

.			{ fprintf(stderr, "!ERROR(%c)\n", *yytext);}

