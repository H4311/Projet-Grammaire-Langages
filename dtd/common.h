#ifndef DTD_COMMON_H
#define DTD_COMMON_H

/**
* Ce fichier contient les définitions utilisées à la fois dans le
* lexer (fichier flex dtd.l) et le parser (fichier bison dtd.y).
* @author Benjamin BOUVIER & Arnaud LAHACHE
*/

#include <string>
#include <utility>
#include <list>

#include "Document.hpp"
#include "Declaration.hpp"
#include "Attribute.hpp"
#include "Element.hpp"
#include "ContentSpec.hpp"
#include "Children.hpp"
#include "ChoiceSeq.hpp"
#include "Choice.hpp"
#include "Seq.hpp"
#include "Name.hpp"

using namespace std;
using namespace dtd;

typedef list<Declaration*> DeclarationList;
typedef list<Children*> ChildrenList;
typedef list<string> AttDefList;

#endif
