#ifndef BASICS_H
#define BASICS_H

/**
* @file basics.h
* Ce fichier contient des typedef utilisés dans divers sources, notamment
* les fichiers flex et bison.
* @author Benjamin BOUVIER
*/

#include <list>
#include <utility>
#include <string>
using namespace std;

typedef pair<string,string> Attribut;
typedef list<Attribut> AttList;
typedef pair<string,string> ElementName;
typedef pair<string,string> Doctype;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif

#endif
