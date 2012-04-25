#include "AttributeList.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Attribute* a) {
	return a->put(out);
}

namespace dtd {

	// -------------------------------------------------------- Class Attribute
	
	Attribute::Attribute(std::string _name, std::list<std::string> _type, std::string _defaultDecl, std::string _attValue)
		: name(_name), type(_type), defaultDecl(_defaultDecl), attValue(_attValue) {}
	
	Attribute::~Attribute() {}

	std::ostream& Attribute::put(std::ostream& out) {
		std::list<std::string>::iterator it;
		out << name << " ";
		
		if(type.size() > 1) out << "(";
		
		it=type.begin();
		out << *it;
		
		for(it++; it != type.end(); it++) {
			out << "|" << *it;
		}
		
		if(type.size() > 1) out << ")";
		
		if(defaultDecl != "") out << " " << defaultDecl;
		if(attValue != "") out << " \"" << attValue << "\"";
		
		return out;
	}
}
