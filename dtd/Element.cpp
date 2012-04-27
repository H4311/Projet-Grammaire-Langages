#include<sstream>

#include "Element.hpp"

namespace dtd {

	// ---------------------------------------------------------- Class Element

	Element::Element(std::string _name, ContentSpec* _content)
		: name(_name), content(_content) {}
	
	Element::~Element() {
		delete content;
	}

	std::ostream& Element::put(std::ostream& out) {
		out << "<!ELEMENT " << name << " " << content << ">" << std::endl;
		return out;
	}
	
	std::string Element::getRegex() {
		return content->getRegex();
	}
	
	std::string Element::getName() {
		return name;
	}

	ContentSpec* Element::getContentSpec() {
		return content;
	}
	
}
