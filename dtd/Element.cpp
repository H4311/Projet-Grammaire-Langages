#include "Element.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Element* e) {
	return e->put(out);
}

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c) {
	return c->put(out);
}

namespace dtd {

	std::ostream& Element::put(std::ostream& out) {
		out << "<!ELEMENT " << name << " " << content << ">\n";
	}
	
	std::ostream& Choice::put(std::ostream& out) {
		std::list<Children*>::iterator it;
		
		out << "(";
		
		it=choices.begin();
		out << *it;
		
		for(it++; it != choices.end(); it++)
    		out << " | " << *it;
    	
    	out << ")" << card;
	}
	
	std::ostream& Seq::put(std::ostream& out) {
		std::list<Children*>::iterator it;
		
		out << "(";
		
		it=seq.begin();
		out << *it;
		
		for(it++; it != seq.end(); it++)
    		out << " , " << *it;
    	
    	out << ")" << card;
	}
	
	std::ostream& Name::put(std::ostream& out) {
		out << name << card;
	}
	
}
