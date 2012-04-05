#include "Attribute.hpp"

namespace dtd {
	
	Attribute::Attribute(std::string _name, std::list<std::string> _attDefs)
		: name(_name), attDefs(_attDefs) {};

	std::ostream& Attribute::put(std::ostream& out) {
		std::list<std::string>::iterator it;
		out << "<!ATTLIST " << name;
		
		for(it=attDefs.begin(); it != attDefs.end(); it++) {
			out << std::endl << *it << " CDATA #IMPLIED";
		}
		
		out << ">";
		
		return out;
	}
}
