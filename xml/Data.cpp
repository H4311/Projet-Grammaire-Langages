# include "Data.hpp"

namespace xml
{

ostream& Data::toString(ostream& stream, int depth)
{
	printTabs(stream, depth);
	stream << data;
	return stream; 
}

}
