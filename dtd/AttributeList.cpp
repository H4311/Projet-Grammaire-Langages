#include "AttributeList.hpp"

namespace dtd {

	// ---------------------------------------------------- Class AttributeList
	
	AttributeList::AttributeList(std::string _name, std::list<Attribute*> _attDefs)
		: name(_name), attDefs(_attDefs) {}
	
	std::list<Attribute*> AttributeList::getAttributes() {
		return attDefs;
	}
	
	std::string AttributeList::getName() {
		return name;
	}
	
	AttributeList::~AttributeList() {
		std::list<Attribute*>::iterator it;
		for(it=attDefs.begin(); it!=attDefs.end(); it++) {
			delete *it;
		}
	}

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
