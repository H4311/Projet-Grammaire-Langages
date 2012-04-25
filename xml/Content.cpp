# include "Content.hpp"

/**
Implémentation des méthodes et fonctions de la classe Content.
@author Benjamin BOUVIER
*/

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
	/*// TODO voir si ce n'est pas possible avec fill et width.
	stream.flags(ios::right);
	stream.fill('\t');
	stream.width(depth);
	*/
}
