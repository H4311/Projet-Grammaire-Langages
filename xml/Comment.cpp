# include "Comment.h"

namespace Xml
{

ostream& Comment::toString(ostream& stream)
{
	stream << "<!-- " << comment << " -->";
	return stream; 
}

}
