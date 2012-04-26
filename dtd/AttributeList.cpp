#include "AttributeList.hpp"

namespace dtd {

	// ---------------------------------------------------- Class AttributeList
	
	AttributeList::AttributeList(std::string _name, std::list<Attribute*> _attDefs)
		: name(_name), attDefs(_attDefs) {}
	
	AttributeList::~AttributeList() {}

	std::ostream& AttributeList::put(std::ostream& out) {
		std::list<Attribute*>::iterator it;
		out << "<!ATTLIST " << name;
		
		for(it=attDefs.begin(); it != attDefs.end(); it++) {
			out << std::endl << "\t" << *it;
		}
		
		out << ">";
		
		return out;
	}
}
