# include "Comment.hpp"

/**
* @file Comment.cpp
* Implémentation de la classe Comment.
* @author Benjamin BOUVIER
*/

namespace xml
{
	ostream& Comment::toString(ostream& stream, int depth)
	{
		printTabs(stream, depth);
		stream << comment;
		return stream; 
	}
}
