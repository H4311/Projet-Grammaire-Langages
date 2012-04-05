#include "Element.hpp"

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c) {
	return c->put(out);
}

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
	
	// ------------------------------------------------------ Class ContentSpec
	
	ContentSpec::~ContentSpec() {}
	
	// --------------------------------------------------------- Class Children
	
	Children::Children(char _card)
		: card(_card) {}
	
	Children::~Children() {}
	
	// -------------------------------------------------------- Class ChoiceSeq
		
	ChoiceSeq::ChoiceSeq(std::list<Children*> _children)
		: children(_children) {}
	
	ChoiceSeq::~ChoiceSeq() {
		std::list<Children*>::iterator it;
		for(it=children.begin(); it!=children.end(); it++)
			delete *it;
	}
	
	std::ostream& ChoiceSeq::put(std::ostream& out) {
		std::list<Children*>::iterator it;
		
		out << "(";
		
		it=children.begin();
		out << *it;
		
		for(it++; it != children.end(); it++)
    		out << getSep() << *it;
    	
    	out << ")" << card;
    	
    	return out;
	}
	
	// ----------------------------------------------------------- Class Choice
	
	Choice::Choice(std::list<Children*> _children)
		: ChoiceSeq(_children) {}
	
	Choice::~Choice() {}
	
	char Choice::getSep() {
		return '|';
	}
	
	// -------------------------------------------------------------- Class Seq
		
	Seq::Seq(std::list<Children*> _children)
		: ChoiceSeq(_children) {}
	
	Seq::~Seq() {}
	
	char Seq::getSep() {
		return ',';
	}
	
	// ------------------------------------------------------------- Class Name
	
	Name::Name(std::string _name)
		: name(_name) {}
	
	Name::~Name() {}
	
	std::ostream& Name::put(std::ostream& out) {
		out << name << card;
		return out;
	}
	
}
