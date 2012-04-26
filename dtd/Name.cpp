#include<sstream>

#include "Name.hpp"

namespace dtd {

	// ------------------------------------------------------------- Class Name
	
	Name::Name(std::string _name)
		: name(_name) {}
	
	Name::~Name() {}
	
	std::ostream& Name::put(std::ostream& out) {
		out << name << card;
		return out;
	}
	
	std::string Name::getRegex() {
		std::stringstream oss;
		oss << "(" + name + ",)" << card;
		return oss.str();
	}

}
