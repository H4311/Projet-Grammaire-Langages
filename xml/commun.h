#ifndef COMMUN_H
#define COMMUN_H

using namespace std;
#include <list>
#include <utility>
#include <string>

typedef pair<string,string> Attribut;
typedef list<Attribut> AttList;

// The first element consists in the namespace,
// the second in the element name itself.
typedef pair<string,string> ElementName;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
