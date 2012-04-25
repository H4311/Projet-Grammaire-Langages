#include "AttributeList.hpp"

namespace dtd {

	// ---------------------------------------------------- Class AttributeList
	
	AttributeList::AttributeList(std::string _name, std::list<std::string> _attDefs)
		: name(_name), attDefs(_attDefs) {}
	
	AttributeList::~AttributeList() {}

	std::ostream& AttributeList::put(std::ostream& out) {
		std::list<std::string>::iterator it;
		out << "<!ATTLIST " << name;
		
		for(it=attDefs.begin(); it != attDefs.end(); it++) {
			out << std::endl << *it << " CDATA #IMPLIED";
		}
		
		out << ">";
		
		return out;
	}
}
