# include "Data.hpp"

/**
@file Data.cpp
Ce fichier contient l'implémentation de la classe xml::Data.
@author Benjamin BOUVIER
*/
using namespace std;

namespace xml
{
	ostream& Data::toString(ostream& stream, int depth)
	{
		printTabs(stream, depth);
		stream << data;
		return stream; 
	}
}
