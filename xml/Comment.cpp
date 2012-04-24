# include "Comment.hpp"

namespace xml
{

ostream& Comment::toString(ostream& stream, int depth)
{
	printTabs(stream, depth);
	stream << "<!-- " << comment << " -->";
	return stream; 
}

}
