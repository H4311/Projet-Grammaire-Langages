#ifndef BASICS_H
#define BASICS_H

#include <list>
#include <utility>
#include <string>
using namespace std;

typedef pair<string,string> Attribut;
typedef list<Attribut> AttList;
typedef pair<string,string> ElementName;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
