# include "Comment.hpp"

/**
* @file Comment.cpp
* Implémentation des méthodes de la classe Comment.
* @author Benjamin BOUVIER
*/
using namespace std;

namespace xml
{
	ostream& Comment::toString(ostream& stream, int depth)
	{
		printTabs(stream, depth);
		stream << comment;
		return stream; 
	}
}
