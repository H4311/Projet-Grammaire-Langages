#include<sstream>

#include "ChoiceSeq.hpp"

namespace dtd {

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
	
	std::string ChoiceSeq::getRegex() {
		std::stringstream oss;
		std::list<Children*>::iterator it;
		
		oss << "(";
		
		it=children.begin();
		oss << (*it)->getRegex();
		
		for(it++; it != children.end(); it++)
			oss << getRegexSep() << (*it)->getRegex();
    	
    	oss << ")" << card;
    	
    	return oss.str();
	}

}
