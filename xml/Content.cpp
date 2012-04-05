# include "Content.hpp"

ostream& operator<<(ostream& stream, xml::Content* content) {
	return content->toString(stream, 0);
}

void xml::Content::printTabs(ostream& stream, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		stream << "\t";	
	}
}
