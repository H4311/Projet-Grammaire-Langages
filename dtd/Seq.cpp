#include "Seq.hpp"

namespace dtd {

	// -------------------------------------------------------------- Class Seq
		
	Seq::Seq(std::list<Children*> _children, char card)
		: ChoiceSeq(_children, card) {}
	
	Seq::~Seq() {}
	
	char Seq::getSep() {
		return ',';
	}
	
	char Seq::getRegexSep() {
		return 0;
	}

}
