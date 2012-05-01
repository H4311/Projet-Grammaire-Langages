# include "Content.hpp"

/**
@file Content.cpp
Implémentation des méthodes et fonctions de la classe Content.
@author Benjamin BOUVIER
*/
using namespace std;

ostream& operator<<(ostream& stream, xml::Content* content) {
	// la profondeur initiale est de 0. Ce sont les éléments appelés
	// récursivement qui augmentent la profondeur au fur et à mesure.
	return content->toString(stream, 0);
}

void xml::Content::printTabs(ostream& stream, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		stream << "\t";	
	}
}
