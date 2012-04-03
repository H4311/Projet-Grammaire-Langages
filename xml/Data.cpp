# include "Data.h"

namespace Xml
{

ostream& Data::toString(ostream& stream)
{
	stream << data;
	return stream; 
}

}
