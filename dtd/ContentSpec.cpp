#include "ContentSpec.hpp"

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c) {
	return c->put(out);
}

namespace dtd {

	// ------------------------------------------------------ Class ContentSpec
	
	ContentSpec::~ContentSpec() {}
	
	// -------------------------------------------------------------- Class Any
	
	Any::~Any() {}
	
	std::ostream& Any::put(std::ostream& out) {
		out << "ANY";
		return out;
	}
	
	std::string Any::getRegex() {
		return "*";
	}
	
	// ------------------------------------------------------------ Class Empty
	
	Empty::~Empty() {}
	
	std::ostream& Empty::put(std::ostream& out) {
		out << "EMPTY";
		return out;
	}
	
	std::string Empty::getRegex() {
		return "";
	}
	
}
